#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "lista.h"

/**
 * Indica si un nodo es solución
 */
int Solucion(tipoelem n);

/**
 * Genera un nodo con sus campos vacíos
 */
void nodoVacio(tipoelem *n, int totalNiveles);

/**
 * Función de iteración. Devuelve el siguiente hermano viable en el mismo nivel del nodo.
 */
int siguienteHermano(tipoelem *n, int **matrizBeneficios);

/**
 * Selecciona el nodo más prometedor de la LNV, con estrategia MB-LIFO
 */
tipoelem Seleccionar(lista *LNV);

/**
 * Genera una asignación vacía
 */
void asignacionVacia(int totalNiveles, asignacion *s);

/**
 * Destruye la memoria empleada por una asignación
 */
void destruirAsignacion(asignacion *s);

/**
 * Copia una asignación en otra
 */
void copiarAsignacion(asignacion *sdest, asignacion sorig);

/**
 * Copia un nodo en otro
 */
void copiarNodo(tipoelem *ndest, tipoelem norig);

/**
 * Copia una asignación en otra
 */
void destruirNodo(tipoelem *n);

/**
 * Imprime los valores de una asignación de tareas
 */
void imprimirSolucion(tipoelem s);

/**
 * Genera el nodo raíz
 */
void generarNodoRaiz(int totalNiveles, tipoelem *e, int **matrizBeneficios);

#endif
