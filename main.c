#include <stdio.h>
#include <assert.h>
#include "sugerencias.h"

int main(int argc, char **argv) {
  assert(argc == 3);
  corregir_archivo(argv[1], argv[2]);

  return 0;
}