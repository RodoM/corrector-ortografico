#include "tecnicas.h"

void validar_sugerencia(char *sugerencia, TablaHash diccionario, TablaHash *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  if (!tablahash_contiene(*cambiosNuevos, sugerencia)) {
    tablahash_insertar(*cambiosNuevos, sugerencia);
    if (tablahash_contiene(diccionario, sugerencia) && !slist_contiene(*sugerencias, sugerencia)) {
      *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
      *cantSugerencias += 1;
    }
  }
}

// n-1 sugerencias
/**
 * Toma una lista de cambios y a cada palabra se le intercambian las letras adyacentes
 * para generar nuevas sugerencias, cada una de estas nuevas sugerencias son agregadas
 * en una nueva lista que sera utilizada en el siguiente paso, si alguna de estas
 * sugerencias pertenece al diccionario y no fue previamente agregada, se agrega a la
 * lista de sugerencias validas.
 */
void tecnica_intercambiar (TablaHash diccionario, TablaHash cambiosActuales, TablaHash *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[60];

  for (unsigned int i = 0; i < cambiosActuales->capacidad && *cantSugerencias < 5; i++) {
    if (cambiosActuales->elems[i].dato != NULL) {
      lenSugerencia = strlen(cambiosActuales->elems[i].dato);
      strcpy(sugerencia, cambiosActuales->elems[i].dato);

      for (int j = 0; j < lenSugerencia - 1 && *cantSugerencias < 5; j++) {
        if (sugerencia[j] != sugerencia[j + 1]) {
          charSugerencia = sugerencia[j];
          sugerencia[j] = sugerencia[j + 1];
          sugerencia[j + 1] = charSugerencia;
          
          validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);

          sugerencia[j + 1] = sugerencia[j];
          sugerencia[j] = charSugerencia;
        }
      } 

      if (cambiosActuales->elems[i].lista != NULL) {
        for (SNodo *nodo = cambiosActuales->elems[i].lista; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
          lenSugerencia = strlen(nodo->dato);
          strcpy(sugerencia, nodo->dato);

          for (int j = 0; j < lenSugerencia - 1 && *cantSugerencias < 5; j++) {
            if (sugerencia[j] != sugerencia[j + 1]) {
              charSugerencia = sugerencia[j];
              sugerencia[j] = sugerencia[j + 1];
              sugerencia[j + 1] = charSugerencia;
              
              validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);

              sugerencia[j + 1] = sugerencia[j];
              sugerencia[j] = charSugerencia;
            }
          } 
        }
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
void tecnica_insertar (TablaHash diccionario, TablaHash cambiosActuales, TablaHash *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[60];
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (unsigned int i = 0; i < cambiosActuales->capacidad && *cantSugerencias < 5; i++) {
    if (cambiosActuales->elems[i].dato != NULL) {
      lenSugerencia = strlen(cambiosActuales->elems[i].dato);
      strcpy(sugerencia, cambiosActuales->elems[i].dato);

      for (int j = lenSugerencia + 1; j > 0; j--)
        sugerencia[j] = sugerencia[j - 1];

      for (int j = 0; j < lenSugerencia + 1 && *cantSugerencias < 5; j++) {
        for (int k = 0; k < 26 && *cantSugerencias < 5; k++) {
          sugerencia[j] = abecedario[k];
          validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
        }
        sugerencia[j] = sugerencia[j + 1];
      }

      if (cambiosActuales->elems[i].lista != NULL) {
        for (SNodo *nodo = cambiosActuales->elems[i].lista; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
          lenSugerencia = strlen(nodo->dato);
          strcpy(sugerencia, nodo->dato);

          for (int j = lenSugerencia + 1; j > 0; j--)
            sugerencia[j] = sugerencia[j - 1];
          
          for (int j = 0; j < lenSugerencia + 1 && *cantSugerencias < 5; j++) {
            for (int k = 0; k < 26 && *cantSugerencias < 5; k++) {
              sugerencia[j] = abecedario[k];
              validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
            }
            sugerencia[j] = sugerencia[j + 1];
          }
        }
      }
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
void tecnica_eliminar (TablaHash diccionario, TablaHash cambiosActuales, TablaHash *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[60];
  for (unsigned int i = 0; i < cambiosActuales->capacidad && *cantSugerencias < 5; i++) {
    if (cambiosActuales->elems[i].dato != NULL) {
      lenSugerencia = strlen(cambiosActuales->elems[i].dato);
      strcpy(sugerencia, cambiosActuales->elems[i].dato);
      for (int j = 0; j < lenSugerencia && *cantSugerencias < 5; j++) {
        for (int k = j; k < lenSugerencia && *cantSugerencias < 5; k++) {
          sugerencia[k] = sugerencia[k + 1];
        }
        validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
        strcpy(sugerencia, cambiosActuales->elems[i].dato);
      }

      if (cambiosActuales->elems[i].lista != NULL) {
        for (SNodo *nodo = cambiosActuales->elems[i].lista; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
          lenSugerencia = strlen(nodo->dato);
          strcpy(sugerencia, nodo->dato);
          for (int j = 0; j < lenSugerencia && *cantSugerencias < 5; j++) {
            for (int k = j; k < lenSugerencia && *cantSugerencias < 5; k++) {
              sugerencia[k] = sugerencia[k + 1];
            }
            validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
            strcpy(sugerencia, nodo->dato);
          }
        }
      }
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
void tecnica_reemplazar (TablaHash diccionario, TablaHash cambiosActuales, TablaHash *cambiosNuevos, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char charSugerencia, sugerencia[60];;
  char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

  for (unsigned int i = 0; i < cambiosActuales->capacidad && *cantSugerencias < 5; i++) {
    if (cambiosActuales->elems[i].dato != NULL) {
      lenSugerencia = strlen(cambiosActuales->elems[i].dato);
      strcpy(sugerencia, cambiosActuales->elems[i].dato);

      for (int j = 0; j < lenSugerencia && *cantSugerencias < 5; j++) {
        charSugerencia = sugerencia[j];
        for (int k = 0; k < 26 && *cantSugerencias < 5; k++) {
          if (sugerencia[j] != abecedario[k]) {
            sugerencia[j] = abecedario[k];
            validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
            sugerencia[j] = charSugerencia;
          }
        }
      }

      if (cambiosActuales->elems[i].lista != NULL) {
        for (SNodo *nodo = cambiosActuales->elems[i].lista; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
          lenSugerencia = strlen(nodo->dato);
          strcpy(sugerencia, nodo->dato);

          for (int j = 0; j < lenSugerencia && *cantSugerencias < 5; j++) {
            charSugerencia = sugerencia[j];
            for (int k = 0; k < 26 && *cantSugerencias < 5; k++) {
              if (sugerencia[j] != abecedario[k]) {
                sugerencia[j] = abecedario[k];
                validar_sugerencia(sugerencia, diccionario, cambiosNuevos, sugerencias, cantSugerencias);
                sugerencia[j] = charSugerencia;
              }
            }
          }
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
void tecnica_separar (TablaHash diccionario, TablaHash cambiosActuales, SList *sugerencias, int *cantSugerencias) {
  int lenSugerencia;
  char sugerencia[60], sugerencia2[30];

  for (unsigned int i = 0; i < cambiosActuales->capacidad && *cantSugerencias < 5; i++) {
    if (cambiosActuales->elems[i].dato != NULL) {
      lenSugerencia = strlen(cambiosActuales->elems[i].dato);

      for (int j = 1; j < lenSugerencia && *cantSugerencias < 5; j++) {
        strncpy(sugerencia, cambiosActuales->elems[i].dato, j);
        sugerencia[j] = '\0';
        strcpy(sugerencia2, cambiosActuales->elems[i].dato + j);
        
        if(tablahash_contiene(diccionario, sugerencia) && tablahash_contiene(diccionario, sugerencia2)) {
          sugerencia[j] = ' ';
          sugerencia[j + 1] = '\0';
          strcat(sugerencia, sugerencia2);
          *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
          *cantSugerencias += 1;
        }
      }

      if (cambiosActuales->elems[i].lista != NULL) {
        for (SNodo *nodo = cambiosActuales->elems[i].lista; nodo != NULL && *cantSugerencias < 5; nodo = nodo->sig) {
          lenSugerencia = strlen(nodo->dato);

          for (int j = 1; j < lenSugerencia && *cantSugerencias < 5; j++) {
            strncpy(sugerencia, nodo->dato, j);
            sugerencia[j] = '\0';
            strcpy(sugerencia2, nodo->dato + j);
            
            if(tablahash_contiene(diccionario, sugerencia) && tablahash_contiene(diccionario, sugerencia2)) {
              sugerencia[j] = ' ';
              sugerencia[j + 1] = '\0';
              strcat(sugerencia, sugerencia2);
              *sugerencias = slist_agregar_final(*sugerencias, sugerencia);
              *cantSugerencias += 1;
            }
          }
        }
      }
    }
  }
}