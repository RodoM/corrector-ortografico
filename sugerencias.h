#ifndef __SUGERENCIAS_H__
#define __SUGERENCIAS_H__

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "slist.h"
#include "tablahash.h"
#include "tecnicas.h"

/**
 * Se lee el archivo de entrada donde se chequea cada palabra y las que no pertenecen
 * al diccionario son manejadas por la funcion generar_sugerencias.
 */
void corregir_archivo(char *nombreArchivoEntrada, char *nombreArchivoSalida);

#endif /** __SUGERENCIAS_H__ */
