#include <stdio.h>
#include <stdlib.h>

#include "backtracking.h"

#define NUM_TAREAS 6

asignacion backtracking();

int main() {
    asignacion solucion;
    int beneficiosP1[NUM_TAREAS] = {11, 17, 8, 16, 20, 14};
    int beneficiosP2[NUM_TAREAS] = {9, 7, 6, 12, 15, 18};
    int beneficiosP3[NUM_TAREAS] = {13, 15, 16, 12, 16, 18};
    int beneficiosP4[NUM_TAREAS] = {21, 24, 28, 17, 26, 20};
    int beneficiosP5[NUM_TAREAS] = {10, 14, 12, 11, 15, 13};
    int beneficiosP6[NUM_TAREAS] = {12, 20, 19, 13, 22, 17};
    int* matrizBeneficios[NUM_TAREAS] = {beneficiosP1, beneficiosP2, beneficiosP3, beneficiosP4, beneficiosP5, beneficiosP6};

    solucion = backtracking(matrizBeneficios);

    imprimirSolucion(solucion);

    destruirAsignacion(&solucion);
}

asignacion backtracking(int matrizBeneficios[][NUM_TAREAS]) {
    int nivel = 0;
    asignacion soa;
    asignacion s;
    asignacionVacia(NUM_TAREAS, &soa);
    asignacionVacia(NUM_TAREAS, &s);

    int voa = 0;
    int bact = 0;
    do {
        Generar(nivel, s, matrizBeneficios, &bact);
        if (Solucion(nivel, s) && (bact>voa)) {
            voa = bact;
            copiarAsignacion(&soa, s);
        }
        if (Criterio(nivel, s) && (nivel < (getNumPersonas(s)-1))) {
            nivel++;
        }
        while (!MasHermanos(nivel, s) && (nivel > -1)) {
            Retroceder(&nivel, s, matrizBeneficios, &bact);
        }
    } while (nivel!=-1);

    return (soa);
}

//Posibles mejoras -> vector de tareas usadas: (0, 0, 1), he usado la tarea 3

//Contar pasos en funciones
