#include "tecnicas.h"

void tecnica_intercambiar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia - 1; i++) {
      if (sugerencia[i] != sugerencia[i + 1]) {
        charSugerencia = sugerencia[i];
        sugerencia[i] = sugerencia[i + 1];
        sugerencia[i + 1] = charSugerencia;
        // VER SI NO HACE FALTA CHEQUEAR SI LA SUGERENCIA YA ESTA EN LA LISTA
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
        if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
          *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
          *cantSugerencias += 1;
        }
        sugerencia[i + 1] = sugerencia[i];
        sugerencia[i] = charSugerencia;
      }
    } 
  }
}

void tecnica_insertar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[80];
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = lenSugerencia + 1; i > 0; i--) {
      sugerencia[i] = sugerencia[i - 1];
    }

    for (int i = 0; i < lenSugerencia + 1; i++) {
      for (int j = 0; j < 26; j++) {
        sugerencia[i] = abecedario[j];
        // VER SI NO HACE FALTA CHEQUEAR SI LA SUGERENCIA YA ESTA EN LA LISTA
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
        if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
          *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
          *cantSugerencias += 1;
        }
      }
      sugerencia[i] = sugerencia[i + 1];
    }
    
    
  }
}

void tecnica_eliminar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia; i++) {
      for (int j = i; j < lenSugerencia; j++) {
        sugerencia[j] = sugerencia[j + 1];
      }
      // VER SI NO HACE FALTA CHEQUEAR SI LA SUGERENCIA YA ESTA EN LA LISTA
      *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
      if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
        *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
        *cantSugerencias += 1;
      }
      strcpy(sugerencia, nodo->dato);
    }
  }
}

void tecnica_reemplazar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[80];
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia; i++) {
      charSugerencia = sugerencia[i];
      for (int j = 0; j < 26; j++) {
        if (sugerencia[i] != abecedario[j]) {
          sugerencia[i] = abecedario[j];
          // VER SI NO HACE FALTA CHEQUEAR SI LA SUGERENCIA YA ESTA EN LA LISTA
          *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
          if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
            *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
            *cantSugerencias += 1;
          }
          sugerencia[i] = charSugerencia;
        }
      }
    }
  }
}

void tecnica_separar (TablaHash diccionario, SList cambiosActuales, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[80], sugerencia2[40];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);

    for (int i = 1; i < lenSugerencia; i++) {
      strncpy(sugerencia, nodo->dato, i);
      sugerencia[i] = '\0';
      strcpy(sugerencia2, nodo->dato + i);
      if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia) && tablahash_contiene(diccionario, sugerencia2) && !slist_contiene(*sugerencias, sugerencia2)) {
        *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
        *sugerencias = slist_agregar_final(*sugerencias, sugerencia2);
        *cantSugerencias += 2;
      }
    }
  }
}