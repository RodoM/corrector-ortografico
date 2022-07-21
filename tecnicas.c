#include "tecnicas.h"

void tecnica_intercambiar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia - 1 && *cantSugerencias < 5; i++) {
      if (sugerencia[i] != sugerencia[i + 1]) {
        charSugerencia = sugerencia[i];
        sugerencia[i] = sugerencia[i + 1];
        sugerencia[i + 1] = charSugerencia;
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    strcpy(sugerencia, nodo->dato);

    for (int i = lenSugerencia + 1; i > 0; i--) {
      sugerencia[i] = sugerencia[i - 1];
    }

    for (int i = 0; i < lenSugerencia + 1 && *cantSugerencias < 5; i++) {
      for (int j = 0; j < 26 && *cantSugerencias < 5; j++) {
        sugerencia[i] = abecedario[j];
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia && *cantSugerencias < 5; i++) {
      for (int j = i; j < lenSugerencia && *cantSugerencias < 5; j++) {
        sugerencia[j] = sugerencia[j + 1];
      }
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    strcpy(sugerencia, nodo->dato);

    for (int i = 0; i < lenSugerencia && *cantSugerencias < 5; i++) {
      charSugerencia = sugerencia[i];
      for (int j = 0; j < 26 && *cantSugerencias < 5; j++) {
        if (sugerencia[i] != abecedario[j]) {
          sugerencia[i] = abecedario[j];
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

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);

    for (int i = 1; i < lenSugerencia && *cantSugerencias < 5; i++) {
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