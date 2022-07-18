#include "tecnicas.h"

void tecnica_intercambiar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia - 1 && *cantSugerencias < 5; i++) {
      if (sugerencia[i] != sugerencia[i + 1]) {
        charSugerencia = sugerencia[i];
        sugerencia[i] = sugerencia[i + 1];
        sugerencia[i + 1] = charSugerencia;
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
        if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
          *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = lenSugerencia + 1; i > 0; i--) {
      sugerencia[i] = sugerencia[i - 1];
    }

    for (int i = 0; i < lenSugerencia + 1 && *cantSugerencias < 5; i++) {
      for (int j = 0; j < 26 && *cantSugerencias < 5; j++) {
        sugerencia[i] = abecedario[j];
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
        if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
          *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia && *cantSugerencias < 5; i++) {
      for (int j = i; j < lenSugerencia; j++) {
        sugerencia[j] = sugerencia[j + 1];
      }
      *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
      if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
        *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    // sugerencia = malloc(sizeof(char)*lenSugerencia);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia; i++) {
      charSugerencia = sugerencia[i];
      for (int j = 0; j < 26 && *cantSugerencias < 5; j++) {
        if (sugerencia[i] != abecedario[j]) {
          sugerencia[i] = abecedario[j];
          *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
          if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
            *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
            *cantSugerencias += 1;
          }
          sugerencia[i] = charSugerencia;
        }
      }
    }
  }
}

void tecnica_separar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[80], sugerencia2[40];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);

    for (int i = 1; i < lenSugerencia; i++) {
      strncpy(sugerencia, nodo->dato, i);
      sugerencia[i] = '\0';
      strcpy(sugerencia2, nodo->dato + i);
      // solo se aplica si al separar la palabra conseguimos dos palabras que ya estan en el diccionario, y no admite pasos posteriores.
      *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia);
      *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, sugerencia2);
      // ver cuando agregar a sugerencias
      if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
        *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
        *cantSugerencias += 1;
      }
    }
  }
}