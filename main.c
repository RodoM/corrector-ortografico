#include <stdio.h>
#include <assert.h>
#include "slist.h"
#include "tablahash.h"
#include "tecnicas.h"
#include "sugerencias.h"

// armar main para que tome los argumentos correspondientes
int main(int argc, char **argv) {
  assert(argc == 3);
  TablaHash diccionario = cargar_diccionario("diccionario.txt");
  // printf("El numero de casilleros es de: %d\n", tablahash_capacidad(diccionario));
  // printf("El numero de elementos es de: %d\n", tablahash_nelems(diccionario)); //El numero de palabras en el diccionario es de: 620891

  corregir_archivo(argv[1], argv[2], diccionario);

  tablahash_destruir(diccionario);
  return 0;
}