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
		buf[i++] = tolower(c);
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

char **obtener_palabras(char *buf) {
	char **palabras = malloc(sizeof(char)*1024);
	int index = 0;
	//obtengo cada palabra sin caracteres especiales
  //falta guardarlas en un arr o tabla hash (VER)
  char* token = strtok(buf, " :;,.?!\n");
  while (token != NULL) {
		int lenPalabra = strlen(token);
		palabras[index] = malloc(sizeof(char)*lenPalabra);
		memcpy(palabras[index], token, lenPalabra);
		index += 1;
    token = strtok(NULL, " :;,.?!\n");
  }

	return palabras;
}