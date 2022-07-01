#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>


int main() {
  int len = 0;
  char *buf = readfile("prueba", &len);
  char **palabras = obtener_palabras(buf);

  int i = 0;
  while (palabras[i] != NULL)
    printf("-> %s\n", palabras[i++]);
  
  return 0;
}