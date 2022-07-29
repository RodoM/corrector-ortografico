#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

SList slist_agregar_inicio(SList lista, char *dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = malloc(sizeof(char) * strlen(dato) + 1);
  strcpy(nuevoNodo->dato, dato);
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

SList slist_agregar_final(SList lista, char *dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = malloc(sizeof(char) * strlen(dato) + 1);
  strcpy(nuevoNodo->dato, dato);
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (; nodo->sig != NULL; nodo = nodo->sig);

  nodo->sig = nuevoNodo;
  return lista;
}

void slist_eliminar(SList lista, int pos) {
  SList nodo1 = lista;
  SList nodo2 = lista;
  for (int i = 0; i < pos - 1; nodo1 = nodo1->sig, i++);
  for (int i = 0; i < pos; nodo2 = nodo2->sig, i++);
  nodo1->sig = nodo2->sig;
}

int slist_contiene(SList lista, char *dato) {
  int bandera = 0;
  for (SNodo * nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (strcmp(nodo->dato, dato) == 0) {
      bandera = 1;
      return bandera;
    }
  }
  
  return bandera;
}
