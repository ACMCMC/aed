#ifndef BACKTRACKING_H
#define BACKTRACKING_H

typedef void* asignacion;

/**
 * Genera el siguiente nodo al actual (su hermano derecho)
 */
void Generar(int nivel, asignacion s, int** matrizBeneficios, int* bact);

/**
 * Indica si una asignación es solución
 */
int Solucion(int nivel, asignacion s);

/**
 * Comprueba si una tarea está repetida comparándola con la del nivel especificado
 */
int Criterio(int nivel, asignacion s);

/**
 * Indica si la asignación tiene más nodos hermanos en el nivel especificado
 */
int MasHermanos(int nivel, asignacion s);
void Retroceder(int* nivel, asignacion s, int** matrizBeneficios, int* bact);
void asignacionVacia(int totalNiveles, asignacion* s);
void destruirAsignacion(asignacion* s);
void copiarAsignacion(asignacion*sdest, asignacion sorig);
int getNumPersonas(asignacion s);
void imprimirSolucion(asignacion s);

#endif
