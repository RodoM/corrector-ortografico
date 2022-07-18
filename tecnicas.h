#ifndef __TECNICAS_H__
#define __TECNICAS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "tablahash.h"

void tecnica_intercambiar (SList cambiosActuales, SList *cambiosNuevos, int cantSugerencias);

void tecnica_insertar (SList cambiosActuales, SList *cambiosNuevos, int cantSugerencias);

void tecnica_eliminar (SList cambiosActuales, SList *cambiosNuevos, int cantSugerencias);

void tecnica_reemplazar (SList cambiosActuales, SList *cambiosNuevos, int cantSugerencias);

void tecnica_separar (SList cambiosActuales, SList *cambiosNuevos, int cantSugerencias);

#endif /* __TECNICAS_H__ */