#ifndef __TECNICAS_H__
#define __TECNICAS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "tablahash.h"

void tecnica_intercambiar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias);

void tecnica_insertar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias);

void tecnica_eliminar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias);

void tecnica_reemplazar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias);

void tecnica_separar (TablaHash diccionario, SList cambiosActuales, SList *cambiosNuevos, SList *sugerencias, int *cantSugerencias);

#endif /* __TECNICAS_H__ */