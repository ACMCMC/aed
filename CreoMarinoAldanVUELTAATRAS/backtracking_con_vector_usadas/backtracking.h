#ifndef BACKTRACKING_H
#define BACKTRACKING_H

/**
 * Representa un vector de asignación de tareas; p.ej, (0,1,2,3,4). No le llamo solución, porque sólo es solución si es una asignación completa y válida.
 */
typedef void* asignacion;

/**
 * Genera el siguiente nodo al actual (su hermano derecho)
 */
void Generar(int nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada);

/**
 * Indica si una asignación es solución
 */
int Solucion(int nivel, asignacion s, int* usada);

/**
 * Comprueba si una tarea está repetida comparándola con la del nivel especificado
 */
int Criterio(int nivel, asignacion s, int* usada);

/**
 * Indica si la asignación tiene más nodos hermanos en el nivel especificado
 */
int MasHermanos(int nivel, asignacion s);

/**
 * Realiza la función de retroceso de Backtracking
 */
void Retroceder(int* nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada);

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
 * Devuelve el tamaño del vector de asignaciones (que debería ser también el tamaño de la matriz de beneficios)
 */
int getNumPersonas(asignacion s);

/**
 * Imprime los valores de una asignación de tareas
 */
void imprimirSolucion(asignacion s);

#endif
