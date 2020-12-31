#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "lista.h"

/**
 * Genera el siguiente nodo al actual (su hermano derecho)
 */
//void Generar(int nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada);

/**
 * Indica si una asignación es solución
 */
//int Solucion(int nivel, asignacion s, int* usada, int* numPasosSolucion);

/**
 * Comprueba si una tarea está repetida comparándola con la del nivel especificado
 */
//int Criterio(int nivel, asignacion s, int* usada, int* numPasosCriterio);

/**
 * Indica si el nodo tiene más nodos hermanos en el nivel especificado
 */
int MasHermanos(tipoelem n);

tipoelem siguienteHermano(tipoelem n);

/**
 * Realiza la función de retroceso de Backtracking
 */
//void Retroceder(int* nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada);

/**
 * Selecciona el nodo más prometedor de la LNV
 */
tipoelem Seleccionar(lista* LNV);

/**
 * Genera una asignación vacía
 */
void asignacionVacia(int totalNiveles, asignacion* s);

/**
 * Destruye la memoria empleada por una asignación
 */
void destruirAsignacion(asignacion* s);

/**
 * Copia una asignación en otra
 */
void copiarAsignacion(asignacion*sdest, asignacion sorig);

/**
 * Copia una asignación en otra
 */
void copiarNodo(tipoelem* ndest, tipoelem norig);

/**
 * Copia una asignación en otra
 */
void destruirNodo(tipoelem* n);

/**
 * Devuelve el tamaño del vector de asignaciones (que debería ser también el tamaño de la matriz de beneficios)
 */
//int getNumPersonas(asignacion s);

/**
 * Imprime los valores de una asignación de tareas
 */
void imprimirSolucion(tipoelem s);

/**
 * Genera el nodo raíz
 */
void generarNodoRaiz(int totalNiveles, tipoelem* e, int** matrizBeneficios);

#endif
