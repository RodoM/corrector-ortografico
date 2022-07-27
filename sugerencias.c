#include "sugerencias.h"

/**
 * Carga el diccionaro provisto por la catedra en una tabla hash.
 */
TablaHash cargar_diccionario(char *nombreDiccionario) {
  FILE *archivo = fopen(nombreDiccionario, "r");
  assert(archivo != NULL);

  int capacidadadInicial = 20000;
  TablaHash diccionario = tablahash_crear(capacidadadInicial);

  char buff[25];
  int lenBuff;

  while (fgets(buff, 25, archivo) != NULL) {
    lenBuff = strlen(buff);
    if (buff[lenBuff - 1] == '\n') {
      buff[lenBuff - 1] = '\0';
      lenBuff--;
    }
    tablahash_insertar(diccionario, buff);
  }

  fclose(archivo);

  return diccionario;
}

/**
 * Escribe el archivo de salida con la palabra no perteneciente al diccionario, su linea
 * y las 5 sugerencias.
 */
void generar_salida (char *palabra, int linea, SList sugerencias, FILE *archivoSalida) {
  fprintf(archivoSalida, "LINEA %d, '%s' no esta en el diccionario.\nQuizas quiso decir: ", linea, palabra);
  for (SNodo *nodo = sugerencias; nodo != NULL; nodo = nodo->sig){
    if (nodo->sig == NULL)
      fprintf(archivoSalida, "%s.\n\n", nodo->dato);
    else
      fprintf(archivoSalida, "%s, ", nodo->dato);
  }
}

/**
 * Genera sugerencias con las 5 tecnicas dadas para las palabras que no pertenecen al
 * diccionario, con un maximo de 3 pasos y 5 sugerencias por palabra.
 */
void generar_sugerencias(char *palabra, int linea, TablaHash diccionario, FILE *archivoSalida) {
  int cantSugerencias = 0;
  int pasos = 0;

  SList sugerencias = slist_crear();
  TablaHash cambiosActuales = tablahash_crear(1);
  TablaHash cambiosNuevos = tablahash_crear(10);

  tablahash_insertar(cambiosActuales, palabra);
  printf("PALABRA: %s\n", palabra);
  while (pasos < 3 && cantSugerencias < 5) {
    printf("PASO %d CAMBIOS ACTUALES = %d\n", pasos, tablahash_nelems(cambiosActuales));
    
    tecnica_intercambiar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias, pasos);
    tecnica_insertar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias, pasos);
    tecnica_eliminar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias, pasos);
    tecnica_reemplazar(diccionario, cambiosActuales, &cambiosNuevos, &sugerencias, &cantSugerencias, pasos);
    tecnica_separar(diccionario, cambiosActuales, &sugerencias, &cantSugerencias);

    printf("PASO %d CAMBIOS NUEVOS = %d\n", pasos, tablahash_nelems(cambiosNuevos));

    pasos++;
    tablahash_destruir(cambiosActuales);
    cambiosActuales = cambiosNuevos;
    cambiosNuevos = tablahash_crear(10);
  }

  tablahash_destruir(cambiosActuales);
  tablahash_destruir(cambiosNuevos);

  // Ver si se deben manejar las palabras sin sugerencias.
  if (cantSugerencias == 5)
    generar_salida(palabra, linea, sugerencias, archivoSalida);

  if (sugerencias != NULL)
    slist_destruir(sugerencias);
}

/**
 * Se lee el archivo de entrada donde se chequea cada palabra y las que no pertenecen
 * al diccionario son manejadas por la funcion generar_sugerencias.
 */
void corregir_archivo (char *nombreArchivoEntrada, char *nombreArchivoSalida) {
  FILE *archivoEntrada = fopen(nombreArchivoEntrada, "r");
  FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
  assert(archivoEntrada != NULL && archivoSalida != NULL);

  TablaHash diccionario = cargar_diccionario("diccionario.txt");

  char charBuff, palabra[80];
  for (int i = 0, linea = 1; (charBuff = fgetc(archivoEntrada)) != EOF;) {
    if (charBuff != ' ' && charBuff != '\n') {
      if (charBuff != ':' && charBuff != ';' && charBuff != ',' && charBuff != '.' && charBuff != '?' && charBuff != '!') {
        palabra[i] = tolower(charBuff);
        i++;
      }
    }
    else if (i > 0) {
      palabra[i] = '\0';
      i = 0;
      if (tablahash_contiene(diccionario, palabra) != 1) {
        generar_sugerencias(palabra, linea, diccionario, archivoSalida);
      }
    }
    if (charBuff == '\n')
      linea++;
  }
  
  fclose(archivoEntrada);
  fclose(archivoSalida);
  tablahash_destruir(diccionario);
}