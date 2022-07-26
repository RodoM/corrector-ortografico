#include "tecnicas.h"

// n-1 sugerencias
/**
 * Toma una lista de cambios y a cada palabra se le intercambian las letras adyacentes
 * para generar nuevas sugerencias, cada una de estas nuevas sugerencias son agregadas
 * en una nueva lista que sera utilizada en el siguiente paso, si alguna de estas
 * sugerencias pertenece al diccionario y no fue previamente agregada, se agrega a la
 * lista de sugerencias validas.
 */
void tecnica_intercambiar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia;

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    char sugerencia[lenSugerencia];
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

// (n+1)*26 sugerencias
/**
 * Toma una lista de cambios y a cada palabra se le inserta una letra del abecedario en 
 * cada posicion de la palabra (al principio, entre medio, al final) para generar nuevas
 * sugerencias, cada una de estas nuevas sugerencias son agregadas en una nueva lista que
 * sera utilizada en el siguiente paso, si alguna de estas sugerencias pertenece al
 * diccionario y no fue previamente agregada, se agrega a la lista de sugerencias validas.
 */
void tecnica_insertar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    char sugerencia[lenSugerencia];
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

// n sugerencias
/**
 * Toma una lista de cambios y a cada palabra se le elimina una letra para generar
 * nuevas sugerencias, cada una de estas nuevas sugerencias son agregadas en una
 * nueva lista que sera utilizada en el siguiente paso, si alguna de estas
 * sugerencias pertenece al diccionario y no fue previamente agregada, se agrega a la
 * lista de sugerencias validas.
 */
void tecnica_eliminar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    char sugerencia[lenSugerencia];
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

// n*26 sugerencias
/**
 * Toma una lista de cambios y a cada palabra se le reemplaza una letra por una del 
 * abecedario para generar nuevas sugerencias, cada una de estas nuevas sugerencias
 * son agregadas en una nueva lista que sera utilizada en el siguiente paso, si
 * alguna de estas sugerencias pertenece al diccionario y no fue previamente agregada,
 * se agrega a la lista de sugerencias validas.
 */
void tecnica_reemplazar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia;
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    char sugerencia[lenSugerencia];
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

// n-1 sugerencias
/**
 * Toma una lista de cambios y a cada palabra se la separa en dos para generar
 * nuevas sugerencias, no admite pasos posteriores, si alguna de estas sugerencias
 * pertenece al diccionario y no fue previamente agregada, se agrega a la lista de
 * sugerencias validas.
 */
void tecnica_separar (TablaHash diccionario, SList cambiosActuales, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;

  for (SNodo *nodo = cambiosActuales; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
    lenSugerencia = strlen(nodo->dato);
    char sugerencia[lenSugerencia];
    char sugerencia2[lenSugerencia / 2];

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