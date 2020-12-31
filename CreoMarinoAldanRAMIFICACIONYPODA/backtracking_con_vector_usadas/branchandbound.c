#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

#define SIN_COGER -1

/**
 * Internamente, un vector de asignación de tareas se representa con un vector de enteros.
 */
typedef struct {
    int* valores;
    int totalNiveles;
} asig;

typedef asig* asignacion;

/////////////////////////////////////
//                                 //
//         INICIO FUNCIONES        //
//                                 //
/////////////////////////////////////

int getNumPersonas(asignacion s) {
    return s->totalNiveles;
}

void calcularParametros(tipoelem* e, int** matrizBeneficios) {
    calcularCI(e, matrizBeneficios);
    calcularCS(e, matrizBeneficios);
    calcularBE(e);
}

void calcularCI(tipoelem* e, int** matrizBeneficios) {
    int ci = 0;
    int i;
    for (i = 0; i < e->nivel; i++) {
        ci += matrizBeneficios[e->nivel][((asignacion)(e->tupla))->valores[i]];
    }
}

void calcularCS(tipoelem* e, int** matrizBeneficios) {

}

void calcularBE(tipoelem* e) {
    e->BE = (e->CS + e->CI) / 2.0;
}

void Generar(int nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada) {
    if (s->valores[nivel]!=-1) {
        usada[s->valores[nivel]]--;
    }
    s->valores[nivel] = s->valores[nivel] + 1;
    usada[s->valores[nivel]]++;
    if (s->valores[nivel]==0) { // Es la primera tarea que pruebo
        *bact = *bact + matrizBeneficios[nivel][s->valores[nivel]];
    } else { // Si no es la primera tarea, resto lo que asigné en la prueba anterior
        *bact = *bact + matrizBeneficios[nivel][s->valores[nivel]] - matrizBeneficios[nivel][s->valores[nivel]-1];
    }
}

void imprimirSolucion(asignacion s);
int Criterio(int nivel, asignacion s, int* usada, int* numPasosCriterio) {
    (*numPasosCriterio)++;
    return usada[s->valores[nivel]]==1; // Ninguna tarea está repetida
}

int Solucion(int nivel, asignacion s, int* usada, int* numPasosSolucion) {
    return (nivel==(getNumPersonas(s)-1) && Criterio(nivel, s, usada, numPasosSolucion));
}

int MasHermanos(int nivel, asignacion s) {
    return (s->valores[nivel]<(getNumPersonas(s)-1));
}

void Retroceder(int* nivel, asignacion s, int** matrizBeneficios, int* bact, int* usada) {
    *bact = *bact - matrizBeneficios[*nivel][s->valores[*nivel]];
    usada[s->valores[*nivel]]--;
    s->valores[*nivel] = SIN_COGER;
    (*nivel) = (*nivel) - 1;
}

void asignacionVacia(int totalNiveles, asignacion* s) {
    int i;
    *s = (asig*) malloc(sizeof(asig));
    (*s)->totalNiveles = totalNiveles;
    (*s)->valores = (int*) malloc(sizeof(int)*totalNiveles);
    for (i = 0; i < totalNiveles; i++) {
        (*s)->valores[i] = SIN_COGER;
    }
}

void destruirAsignacion(asignacion* s) {
    free(*s);
    *s = NULL;
}

void copiarAsignacion(asignacion*sdest, asignacion sorig) {
    int i;
    if ((*sdest)!=NULL) {
        destruirAsignacion(sdest);
    }
    *sdest = (asig*) malloc(sizeof(asig));
    (*sdest)->totalNiveles = sorig->totalNiveles;
    (*sdest)->valores = (int*) malloc(sizeof(int)*(sorig->totalNiveles));
    for (i = 0; i < sorig->totalNiveles; i++) {
        (*sdest)->valores[i] = sorig->valores[i];
    }
}

void imprimirSolucion(asignacion s) {
    int i;
    for (i = 0; i < getNumPersonas(s); i++) {
        printf("Persona %d: tarea %d\n", i+1, s->valores[i]+1);
    }
}

void generarNodoRaiz(int totalNiveles, tipoelem* e) {
    int i;

    e->bact = 0;
    e->nivel = 0;
    asignacion a;
    asignacionVacia(totalNiveles, &a);
    e->tupla = a;
    e->usadas = (int*) malloc(sizeof(int)*totalNiveles);
    for (i = 0; i < totalNiveles; i++) {
        e->usadas[i] = 0;
    }

    calcularParametros(e);
}
