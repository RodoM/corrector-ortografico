#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "slist.h"
#include "tablahash.h"
#include "tecnicas.h"

TablaHash cargar_diccionario(char *nombreDiccionario) {
  FILE *archivo = fopen(nombreDiccionario, "r");
  assert(archivo != NULL);

  int capacidadadInicial = 20000;
  TablaHash diccionario = tablahash_crear(capacidadadInicial);

  char buff[25];
  int lenBuff;

  while (fgets(buff, 25, archivo) != NULL) {
    lenBuff = strlen(buff);
    //Borro el salto de linea
    if (buff[lenBuff - 1] == '\n') {
      buff[lenBuff - 1] = '\0';
      lenBuff--;
    }
    tablahash_insertar(diccionario, buff);
  }

  fclose(archivo);

  return diccionario;
}

// void generar_sugerencias(char *palabra, int linea, TablaHash diccionario, char *nombreArchivoSalida)
void generar_sugerencias(char *palabra, int linea, TablaHash diccionario) {
  int cantSugerencias = 0;
  int pasos = 0;

  SList sugerencias = slist_crear();
  SList cambiosActuales = slist_crear();
  SList cambiosNuevos = slist_crear();

  cambiosActuales = slist_agregar_inicio(cambiosActuales, palabra);

  while (cantSugerencias < 5 && pasos < 2) {
    tecnica_intercambiar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias);
    tecnica_insertar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias);
    tecnica_eliminar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias);
    tecnica_reemplazar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias);
    // tecnica_separar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias);

    pasos++;
    slist_destruir(cambiosActuales);
    cambiosActuales = cambiosNuevos;
    cambiosNuevos = slist_crear();
  }

  slist_destruir(cambiosActuales);
  slist_destruir(cambiosNuevos);

  printf("LINEA %d, PALABRA '%s', QUISISTE DECIR?:\n", linea, palabra);
  slist_imprimir(sugerencias);

  //generar archivo de salida

  if (sugerencias != NULL)
    slist_destruir(sugerencias);

}

void corregir_archivo (char *nombreArchivoEntrada, TablaHash diccionario) {
  FILE *archivoEntrada = fopen(nombreArchivoEntrada, "r");
  assert(archivoEntrada != NULL);

  char charBuff, palabra[80];
  for (int i = 0, linea = 1; (charBuff = fgetc(archivoEntrada)) != EOF;) {
    if (charBuff != ' ' && charBuff != '\n') {
      if (charBuff != ':' && charBuff != ';' && charBuff != ',' && charBuff != '.' && charBuff != '?' && charBuff != '!') {
        palabra[i] = tolower(charBuff);
        i++;
      }
    }
    else if (i > 0) { //Verifico que i sea mayor a 0, es decir, que contenga una palabra para agregarle \0 al final
      palabra[i] = '\0';
      i = 0;
      //Chequeo si la palabra esta en el diccionario
      printf("palabra: %s | linea: %d | ", palabra, linea);
      if (tablahash_contiene(diccionario, palabra) != 1) {
        //Si la palabra no esta busco sugerencias
        printf("No se encuentra en el diccionario\n");
      }
      else 
        printf("Se encuentra en el diccionario\n");
    }
    if (charBuff == '\n')
      linea++;
  }
  
  fclose(archivoEntrada);
}