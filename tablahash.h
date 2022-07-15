#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, char *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
int tablahash_buscar(TablaHash tabla, char *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, char *dato);

/**
 * Redimensiona el tamaño de la tabla * 2.
 */
void tablahash_redimensionar(TablaHash tabla);

void tablahash_imprimir(TablaHash tabla);

#endif /* __TABLAHASH_H__ */
