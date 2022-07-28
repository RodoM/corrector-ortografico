#ifndef __TECNICAS_H__
#define __TECNICAS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "tablahash.h"

/**
 * Toma una tabla de cambios y a cada palabra se le intercambian las letras
 * adyacentes para generar nuevas sugerencias.
 */
void tecnica_intercambiar(TablaHash diccionario, TablaHash cambiosActuales,
                          TablaHash * cambiosNuevos, SList * sugerencias,
                          int *cantSugerencias, int pasos);

/**
 * Toma una tabla de cambios y a cada palabra se le inserta una letra del
 * abecedario en cada posicion de la palabra (al principio, entre medio,
 * al final) para generar nuevas sugerencias.
 */
void tecnica_insertar(TablaHash diccionario, TablaHash cambiosActuales,
                      TablaHash * cambiosNuevos, SList * sugerencias,
                      int *cantSugerencias, int pasos);

/**
 * Toma una tabla de cambios y a cada palabra se le elimina una letra para
 * generar nuevas sugerencias.
 */
void tecnica_eliminar(TablaHash diccionario, TablaHash cambiosActuales,
                      TablaHash * cambiosNuevos, SList * sugerencias,
                      int *cantSugerencias, int pasos);

/**
 * Toma una tabla de cambios y a cada palabra se le reemplaza una letra por una
 * del abecedario para generar nuevas sugerencias.
 */
void tecnica_reemplazar(TablaHash diccionario, TablaHash cambiosActuales,
                        TablaHash * cambiosNuevos, SList * sugerencias,
                        int *cantSugerencias, int pasos);

/**
 * Toma una tabla de cambios y a cada palabra se la separa en dos para generar
 * nuevas sugerencias, no admite pasos posteriores, ambas sugerencias
 * pertenecen al diccionario y no fueron previamente agregadas, se agregan a la
 * lista de sugerencias validas como una nueva sugerencia separada por un
 * espacio.
 */
void tecnica_separar(TablaHash diccionario, TablaHash cambiosActuales,
                     SList * sugerencias, int *cantSugerencias);

#endif                          /* __TECNICAS_H__ */
