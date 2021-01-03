#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "branchandbound.h"
#include "lista.h"

#define NUM_TAREAS 6
//#define NUM_TAREAS 3 //Descomentar para el problema con 3 tareas

tipoelem branchAndBound(int **matrizBeneficios, int *numNodosGenerados);

int main()
{
    tipoelem solucion;
    int beneficiosP1[NUM_TAREAS] = {11, 17, 8, 16, 20, 14};
    int beneficiosP2[NUM_TAREAS] = {9, 7, 6, 12, 15, 18};
    int beneficiosP3[NUM_TAREAS] = {13, 15, 16, 12, 16, 18};
    int beneficiosP4[NUM_TAREAS] = {21, 24, 28, 17, 26, 20};
    int beneficiosP5[NUM_TAREAS] = {10, 14, 12, 11, 15, 13};
    int beneficiosP6[NUM_TAREAS] = {12, 20, 19, 13, 22, 17};
    int *matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3, beneficiosP4, beneficiosP5, beneficiosP6};

    //Descomentar para el problema con 3 tareas
    /*int beneficiosP1[NUM_TAREAS] = {4, 9, 1};
    int beneficiosP2[NUM_TAREAS] = {7, 2, 3};
    int beneficiosP3[NUM_TAREAS] = {6, 3, 5};
    int *matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3};*/

    int numNodosGenerados;

    solucion = branchAndBound(matrizBeneficios, &numNodosGenerados);

    printf("\n===SOLUCIÓN===\n");
    imprimirSolucion(solucion);
    printf("\nNúmero de nodos generados: %d\n", numNodosGenerados);

    destruirNodo(&solucion);
}

tipoelem branchAndBound(int **matrizBeneficios, int *numNodosGenerados)
{

    // Inicializamos los contadores
    *numNodosGenerados = 0; // No tengo en cuenta el nodo raíz, ya que no es un nodo que genere la función Generar

    tipoelem soa;        // La solución óptima actual
    tipoelem nodoActual; // El nodo con el que estamos trabajando
    tipoelem nodoHijo;   // El nodo que es hijo del nodo con el que estamos trabajando
    tipoelem nodoAux;    // Un nodo auxiliar

    lista LNV;
    crea(&LNV);

    tipoelem nodoRaiz;
    generarNodoRaiz(NUM_TAREAS, &nodoRaiz, matrizBeneficios);

    soa = asignacionVoraz(nodoRaiz, matrizBeneficios); // Nuestra solución óptima en principio es la que nos devuelve una asignación voraz; el algoritmo tratará de buscar una mejor

    inserta(&LNV, primero(LNV), nodoRaiz);
    int C = soa.bact;
    while (!esvacia(LNV))
    {
        nodoActual = Seleccionar(&LNV);
        if (nodoActual.CS > C)
        {
            copiarNodo(&nodoHijo, nodoActual);
            nodoHijo.nivel++;
            while (siguienteHermano(&nodoHijo, matrizBeneficios)) // Si no quedan más hermanos, la función siguienteHermano devuelve falso, y se acaba el bucle
            {
                if (Solucion(nodoHijo))
                {
                    (*numNodosGenerados)++;
                    if (nodoHijo.bact > soa.bact)
                    {
                        destruirNodo(&soa);
                        copiarNodo(&soa, nodoHijo);
                        C = (C > soa.bact) ? C : soa.bact;
                    }
                }
                else if (!Solucion(nodoHijo) && (nodoHijo.CS > C))
                {
                    printf("dasdsadas, %f, %f\n", nodoHijo.CI, nodoHijo.CS);
                    (*numNodosGenerados)++;
                    if ((nodoHijo.CS - nodoHijo.CI) < 0.1) // No podemos usar == porque son floats, pueden darse errores de precisión
                    {
                        nodoAux = asignacionVoraz(nodoHijo, matrizBeneficios);
                        destruirNodo(&soa);
                        copiarNodo(&soa, nodoAux);
                        C = (C > soa.bact) ? C : soa.bact;
                    }
                    else
                    {
                        copiarNodo(&nodoAux, nodoHijo);
                        inserta(&LNV, fin(LNV), nodoAux);
                        C = (C > nodoHijo.bact) ? C : nodoHijo.bact;
                    }
                }
            }
        }
        destruirNodo(&nodoActual);
    }

    return (soa); // Devolvemos la mejor solución que hayamos encontrado
}
