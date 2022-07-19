#ifndef __SUGERENCIAS_H__
#define __SUGERENCIAS_H__

TablaHash cargar_diccionario(char *nombreDiccionario);

void corregir_archivo (char *nombreArchivoEntrada, TablaHash diccionario);

// despues borrar
void generar_sugerencias(char *palabra, int linea, TablaHash diccionario);

#endif /** __SUGERENCIAS_H__ */