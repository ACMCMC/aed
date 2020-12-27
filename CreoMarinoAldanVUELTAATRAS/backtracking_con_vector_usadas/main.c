#include <stdio.h>
#include <stdlib.h>

#include "backtracking.h"

//#define NUM_TAREAS 6
#define NUM_TAREAS 3 //Descomentar para el problema con 3 tareas

asignacion backtracking(int** matrizBeneficios, int* numNodosGenerados);

int main() {
    asignacion solucion;
    /*int beneficiosP1[NUM_TAREAS] = {11, 17,  8, 16, 20, 14};
    int beneficiosP2[NUM_TAREAS] = { 9,  7,  6, 12, 15, 18};
    int beneficiosP3[NUM_TAREAS] = {13, 15, 16, 12, 16, 18};
    int beneficiosP4[NUM_TAREAS] = {21, 24, 28, 17, 26, 20};
    int beneficiosP5[NUM_TAREAS] = {10, 14, 12, 11, 15, 13};
    int beneficiosP6[NUM_TAREAS] = {12, 20, 19, 13, 22, 17};
    int* matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3, beneficiosP4, beneficiosP5, beneficiosP6};
    */
    
    //Descomentar para el problema con 3 tareas
    int beneficiosP1[NUM_TAREAS] = {4, 9, 1};
    int beneficiosP2[NUM_TAREAS] = {7, 2, 3};
    int beneficiosP3[NUM_TAREAS] = {6, 3, 5};
    int* matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3};
    
    int numNodosGenerados;

    solucion = backtracking(matrizBeneficios, &numNodosGenerados);

    printf("\n===SOLUCIÓN===\n");
    imprimirSolucion(solucion);
    printf("\nNúmero de nodos generados: %d\n", numNodosGenerados);

    destruirAsignacion(&solucion);
}

asignacion backtracking(int** matrizBeneficios, int* numNodosGenerados) {

    // Inicializamos los contadores
    *numNodosGenerados = 0; // No tengo en cuenta el nodo raíz, ya que no es un nodo que genere la función Generar

    int nivel = 0; // Empezamos en el nivel 0 (primera persona)
    asignacion soa; // La solución óptima actual
    asignacion s; // La asignación que estamos comprobando
    asignacionVacia(NUM_TAREAS, &soa);
    asignacionVacia(NUM_TAREAS, &s);

    int voa = 0; // El valor óptimo actual
    int bact = 0; // El beneficio actual

    int usada[NUM_TAREAS];
    int i;
    for (i = 0; i < NUM_TAREAS; i++) {
        usada[i] = 0;
    }

    do {
        Generar(nivel, s, matrizBeneficios, &bact, usada); // Generamos una nueva asignación en el nivel actual
        if (Solucion(nivel, s, usada)) { // Si esta asignación es solución
            (*numNodosGenerados)++; // Comentar esta línea para evitar contar también los nodos que cumplen el criterio, y son solución

            if (bact>voa) { // Y si esta solución es mejor que la mejor que teníamos guardada...
                voa = bact; // ...el valor óptimo actual es el del beneficio actual, y...
                copiarAsignacion(&soa, s); // ...nos quedamos con s como solución óptima actual
            }
        }
        if (Criterio(nivel, s, usada) && (nivel < (getNumPersonas(s)-1))) { // Si la asignación actual es viable...
            nivel++; // ...bajamos un nivel en el árbol
            (*numNodosGenerados)++;
        }
        while (!MasHermanos(nivel, s) && (nivel > -1)) { // Si no quedan más hermanos por probar en el nivel actual, subimos de nuevo
            Retroceder(&nivel, s, matrizBeneficios, &bact, usada);
        }
    } while (nivel!=-1);

    return (soa); // Devolvemos la mejor solución que hayamos encontrado
}

//Posibles mejoras -> vector de tareas usadas: (0, 0, 1), he usado la tarea 3

//Contar pasos en funciones
