#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

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

static inline void quit(const char *s) {
	perror(s);
	exit(1);
}

char * readfile(const char *path, int *len) {
	int sz = 1024;
	char *buf = malloc(sz);
	FILE *f = fopen(path, "rb");
	int c, i = 0;

	if (f == NULL)
		quit("readfile.fopen");

	while ((c = getc(f)) != EOF) {
		if (i == sz) {
			sz = sz * 2;
			buf = realloc(buf, sz);
		}
		buf[i++] = c;
	}

	fclose(f);

	*len = i;
	return buf;
}

void writefile(const char *path, const char *buf, int len) {
	FILE *f = fopen(path, "wb");
	int i;

	if (f == NULL)
		quit("writefile.fopen");

	for (i = 0; i < len; i++)
		fputc(buf[i], f);

	fclose(f);
}

void obtener_palabras (const char *path) {
  //leo el archivo
  int len = 0;
  char *res = readfile(path, &len);

  //paso todas las mayusculas a minusculas (ver si se puede hacer a la par de strtok)
  for (int i = 0; i < len; i++) {
    res[i] = tolower(res[i]);
  }
  
  //obtengo cada palabra sin caracteres especiales
  //falta guardarlas en un arr o tabla hash (VER)
  char* token = strtok(res, " :;,.?!\n");
  while (token != NULL) {
    printf("-> %s\n", token);
    token = strtok(NULL, " :;,.?!\n");
  }
}