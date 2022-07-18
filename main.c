#include <stdio.h>
#include <assert.h>
#include "slist.h"
#include "tablahash.h"
#include "tecnicas.h"
#include "sugerencias.h"

int main() {
  // TablaHash diccionario = cargar_diccionario("diccionario.txt");
  // printf("El numero de casilleros es de: %d\n", tablahash_capacidad(diccionario));
  // printf("El numero de elementos es de: %d\n", tablahash_nelems(diccionario)); //El numero de palabras en el diccionario es de: 620891
  // tablahash_imprimir(diccionario);

  // corregir_archivo("prueba", diccionario);

  SList cambiosActuales = slist_crear();
  SList cambiosNuevos = slist_crear();
  int cantSugerencias = 0;

  cambiosActuales = slist_agregar_inicio(cambiosActuales, "abc");

  tecnica_eliminar(cambiosActuales, &cambiosNuevos, cantSugerencias);

  slist_imprimir(cambiosNuevos);

  // tablahash_destruir(diccionario);
  return 0;
}