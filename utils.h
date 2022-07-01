#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash (char *s);

/*
 * Lee un archivo y devuelve sus contenidos en un buffer obtenido con
 * malloc(). Debe ser liberado luego. En [*len] se guarda la longitud de
 * todo lo leído.
 */
char * readfile (const char *path, int *len);

/*
 * Escribe un archivo con los contenidos del buffer [buf], de longitud
 * [len].
 */
void writefile (const char *path, const char *buf, int len);

char **obtener_palabras(char *buf);

#endif /** __UTILS_H__ */