#include <stdio.h>
#include <stdlib.h>

#include "branchandbound.h"
#include "lista.h"

#define NUM_TAREAS 6
//#define NUM_TAREAS 3 //Descomentar para el problema con 3 tareas

asignacion branchAndBound(int** matrizBeneficios, int* numNodosGenerados, int* numPasosCriterio, int* numPasosSolucion);

int main() {
    asignacion solucion;
    int beneficiosP1[NUM_TAREAS] = {11, 17,  8, 16, 20, 14};
    int beneficiosP2[NUM_TAREAS] = { 9,  7,  6, 12, 15, 18};
    int beneficiosP3[NUM_TAREAS] = {13, 15, 16, 12, 16, 18};
    int beneficiosP4[NUM_TAREAS] = {21, 24, 28, 17, 26, 20};
    int beneficiosP5[NUM_TAREAS] = {10, 14, 12, 11, 15, 13};
    int beneficiosP6[NUM_TAREAS] = {12, 20, 19, 13, 22, 17};
    int* matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3, beneficiosP4, beneficiosP5, beneficiosP6};
    
    //Descomentar para el problema con 3 tareas
    /*int beneficiosP1[NUM_TAREAS] = {4, 9, 1};
    int beneficiosP2[NUM_TAREAS] = {7, 2, 3};
    int beneficiosP3[NUM_TAREAS] = {6, 3, 5};
    int* matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3};*/
    
    int numNodosGenerados;
    int numPasosCriterio;
    int numPasosSolucion;

    solucion = branchAndBound(matrizBeneficios, &numNodosGenerados, &numPasosCriterio, &numPasosSolucion);

    printf("\n===SOLUCIÓN===\n");
    imprimirSolucion(solucion);
    printf("\nNúmero de nodos generados: %d\n", numNodosGenerados);
    printf("Número de pasos que ha hecho la función Criterio en total: %d\n", numPasosCriterio);
    printf("Número de pasos que ha hecho la función Solución en total: %d\n", numPasosSolucion);

    destruirAsignacion(&solucion);
}

asignacion branchAndBound(int** matrizBeneficios, int* numNodosGenerados, int* numPasosCriterio, int* numPasosSolucion) {

    // Inicializamos los contadores
    *numNodosGenerados = 0; // No tengo en cuenta el nodo raíz, ya que no es un nodo que genere la función Generar
    *numPasosCriterio = 0;
    *numPasosSolucion = 0;

    int nivel = 0; // Empezamos en el nivel 0 (primera persona)
    tipoelem soa; // La solución óptima actual
    tipoelem s; // La asignación que estamos comprobando

    lista l;
    crea(&l);

    tipoelem nodoRaiz;
    generarNodoRaiz(NUM_TAREAS, &nodoRaiz);

    inserta(&l, primero(l), nodoRaiz);

    int voa = 0; // El valor óptimo actual
    int bact = 0; // El beneficio actual

    do {
        Generar(nivel, s, matrizBeneficios, &bact, usada); // Generamos una nueva asignación en el nivel actual
        if (Solucion(nivel, s, usada, numPasosSolucion)) { // Si esta asignación es solución
            (*numNodosGenerados)++; // Comentar esta línea para evitar contar también los nodos que cumplen el criterio, y son solución

            if (bact>voa) { // Y si esta solución es mejor que la mejor que teníamos guardada...
                voa = bact; // ...el valor óptimo actual es el del beneficio actual, y...
                copiarAsignacion(&soa, s); // ...nos quedamos con s como solución óptima actual
            }
        }
        if (Criterio(nivel, s, usada, numPasosCriterio) && (nivel < (getNumPersonas(s)-1))) { // Si la asignación actual es viable...
            nivel++; // ...bajamos un nivel en el árbol
            (*numNodosGenerados)++;
        }
        while (!MasHermanos(nivel, s) && (nivel > -1)) { // Si no quedan más hermanos por probar en el nivel actual, subimos de nuevo
            Retroceder(&nivel, s, matrizBeneficios, &bact, usada);
        }
    } while (nivel!=-1);

    return (soa); // Devolvemos la mejor solución que hayamos encontrado
}
