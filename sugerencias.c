#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tablahash.h"

TablaHash cargar_diccionario(char *nombreDiccionario) {
  FILE *archivo = fopen(nombreDiccionario, "r");
  assert(archivo != NULL);

  int capacidadad = 5; //Ver de que capacidad hacer la tabla
  TablaHash diccionario = tablahash_crear(capacidadad);

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