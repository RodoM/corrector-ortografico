#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SList slist_crear() { 
  return NULL; 
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return (lista == NULL);
}

SList slist_agregar_inicio(SList lista, char *dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = malloc(sizeof(char)*strlen(dato) + 1);
  strcpy(nuevoNodo->dato, dato);
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_eliminar(SList lista, int pos) {
  SList nodo1 = lista;
  SList nodo2 = lista;
  for(int i = 0;i<pos-1;nodo1=nodo1->sig, i++);
  for(int i = 0;i<pos;nodo2=nodo2->sig, i++);
  nodo1->sig = nodo2->sig;
}

void slist_imprimir(SList lista) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    printf("%s, ", nodo->dato);
  }
  puts("");
}

int slist_contiene(SList lista, char *dato) {
  int bandera = 0;
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    if (strcmp(nodo->dato, dato) == 0)
      bandera = 1;
  }
  return bandera;
}