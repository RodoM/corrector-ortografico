#include <stdio.h>
#include <assert.h>
#include "slist.h"
#include "tablahash.h"
#include "tecnicas.h"
#include "sugerencias.h"

int main() {
  TablaHash diccionario = cargar_diccionario("diccionario.txt");
  printf("El numero de casilleros es de: %d\n", tablahash_capacidad(diccionario));
  printf("El numero de elementos es de: %d\n", tablahash_nelems(diccionario)); //El numero de palabras en el diccionario es de: 620891

  corregir_archivo("entrada", "salida", diccionario);

  tablahash_destruir(diccionario);
  return 0;
}