#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _SNodo {
  char *dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, char *dato);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, char *dato);

/**
 * Elimina el elemento en la posicion dada.
 */
void slist_eliminar(SList lista, int pos);

/**
 * Chequea si un elemento dado esta en la lista o no.
 */
int slist_contiene(SList lista, char *dato);

#endif                          /* __SLIST_H__ */
