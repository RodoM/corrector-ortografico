#include "tablahash.h"

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }

  return hashval;
}

TablaHash tablahash_crear(unsigned capacidad) {
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;

  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].lista = NULL;
  }

  return tabla;
}

void tablahash_destruir(TablaHash tabla) {
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL) {
      free(tabla->elems[idx].dato);
      if (tabla->elems[idx].lista != NULL)
        slist_destruir(tabla->elems[idx].lista);
    }

  free(tabla->elems);
  free(tabla);
  return;
}

void tablahash_insertar(TablaHash tabla, char *dato) {
  if (tabla->numElems / tabla->capacidad > 0.7) {
    tablahash_redimensionar(tabla);
  }

  unsigned idx = KRHash(dato) % tabla->capacidad;

  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = malloc(sizeof(char) * strlen(dato) + 1);
    strcpy(tabla->elems[idx].dato, dato);
    return;
  } else {
    tabla->numElems++;
    tabla->elems[idx].lista =
        slist_agregar_inicio(tabla->elems[idx].lista, dato);
  }
}

int tablahash_contiene(TablaHash tabla, char *dato) {
  int bandera = 0;
  unsigned idx = KRHash(dato) % tabla->capacidad;

  if (tabla->elems[idx].dato == NULL)
    bandera = 0;

  else if (strcmp(tabla->elems[idx].dato, dato) == 0)
    bandera = 1;

  else if (strcmp(tabla->elems[idx].dato, dato) != 0) {
    bandera = slist_contiene(tabla->elems[idx].lista, dato);
    return bandera;
  }

  return bandera;
}

void tablahash_eliminar(TablaHash tabla, char *dato) {
  unsigned idx = KRHash(dato) % tabla->capacidad;

  if (tabla->elems[idx].dato == NULL)
    return;

  else if (strcmp(tabla->elems[idx].dato, dato) == 0) {
    tabla->numElems--;
    free(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }

  else {
    int i = 0;
    for (SNodo * nodo = tabla->elems[idx].lista; nodo != NULL; nodo = nodo->sig) {
      if (strcmp(nodo->dato, dato) == 0)
        slist_eliminar(tabla->elems[idx].lista, i);
      i++;
    }
  }
}

void tablahash_redimensionar(TablaHash tabla) {
  int viejaCapacidad = tabla->capacidad;
  tabla->numElems = 0;
  tabla->capacidad = viejaCapacidad * 2;
  CasillaHash *viejoElems = tabla->elems;
  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad);

  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].lista = NULL;
  }

  for (int i = 0; i < viejaCapacidad; i++) {
    if (viejoElems[i].dato != NULL) {
      tablahash_insertar(tabla, viejoElems[i].dato);
      if (viejoElems[i].lista != NULL) {
        for (SNodo * nodo = viejoElems[i].lista; nodo != NULL; nodo = nodo->sig)
          tablahash_insertar(tabla, nodo->dato);
      }
    }
    
    slist_destruir(viejoElems[i].lista);
    free(viejoElems[i].dato);
  }

  free(viejoElems);
}
