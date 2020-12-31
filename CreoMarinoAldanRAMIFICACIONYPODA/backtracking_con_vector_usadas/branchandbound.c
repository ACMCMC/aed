#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

#define SIN_COGER -1

/////////////////////////////////////
//                                 //
//         INICIO FUNCIONES        //
//                                 //
/////////////////////////////////////

int getNumPersonas(asignacion s)
{
    return s->totalNiveles;
}


void calcularCI(tipoelem *e, int **matrizBeneficios)
{
    int ci = 0;
    int i;
    for (i = 0; i < e->nivel; i++)
    {
        ci += matrizBeneficios[e->nivel][((asignacion)(e->tupla))->valores[i]];
    }
}

int maximoMatrizBeneficios(int **matrizBeneficios, int numPersonas)
{
    int i, j;
    int max = 0;
    for (i = 0; i < numPersonas; i++)
    {
        for (j = 0; j < numPersonas; j++)
        {
            if (max < matrizBeneficios[i][j])
            {
                max = matrizBeneficios[i][j];
            }
        }
    }
    return max;
}

void calcularCS(tipoelem *e, int **matrizBeneficios)
{
    int cs;
    cs = e->CI;
    cs += maximoMatrizBeneficios(matrizBeneficios, getNumPersonas(e->tupla))*(getNumPersonas(e->tupla) - e->nivel);
    e->CS = cs;
}

void calcularBE(tipoelem *e)
{
    e->BE = (e->CS + e->CI) / 2.0;
}

void calcularParametros(tipoelem *e, int **matrizBeneficios)
{
    calcularCI(e, matrizBeneficios);
    calcularCS(e, matrizBeneficios);
    calcularBE(e);
}

tipoelem Seleccionar(lista* LNV) {
    tipoelem e;
    int beMAX = 0;
    posicion p = primero(*LNV);
    while (p != NULL) { // Primero buscamos el máximo beneficio de toda la lista
        recupera(*LNV, p, &e);
        if (e.BE > beMAX) {
            beMAX = e.BE;
        }
        p = siguiente(*LNV, p);
    }

    p = fin(LNV); // Después buscamos el primero nodo desde el final que tiene el máximo beneficio (LIFO)
    recupera(LNV, p, &e);
    while (e.BE != beMAX);
    {
        p = anterior(LNV, p);
        recupera(LNV, p, &e);
    }

    suprime(LNV, p);
    return e;
}

/*void Generar(int nivel, asignacion s, int **matrizBeneficios, int *bact, int *usada)
{
    if (s->valores[nivel] != -1)
    {
        usada[s->valores[nivel]]--;
    }
    s->valores[nivel] = s->valores[nivel] + 1;
    usada[s->valores[nivel]]++;
    if (s->valores[nivel] == 0)
    { // Es la primera tarea que pruebo
        *bact = *bact + matrizBeneficios[nivel][s->valores[nivel]];
    }
    else
    { // Si no es la primera tarea, resto lo que asigné en la prueba anterior
        *bact = *bact + matrizBeneficios[nivel][s->valores[nivel]] - matrizBeneficios[nivel][s->valores[nivel] - 1];
    }
}

void imprimirSolucion(tipoelem s);

int Criterio(int nivel, asignacion s, int *usada, int *numPasosCriterio)
{
    (*numPasosCriterio)++;
    return usada[s->valores[nivel]] == 1; // Ninguna tarea está repetida
}

int Solucion(int nivel, asignacion s, int *usada, int *numPasosSolucion)
{
    return (nivel == (getNumPersonas(s) - 1) && Criterio(nivel, s, usada, numPasosSolucion));
}

int MasHermanos(int nivel, asignacion s)
{
    return (s->valores[nivel] < (getNumPersonas(s) - 1));
}

void Retroceder(int *nivel, asignacion s, int **matrizBeneficios, int *bact, int *usada)
{
    *bact = *bact - matrizBeneficios[*nivel][s->valores[*nivel]];
    usada[s->valores[*nivel]]--;
    s->valores[*nivel] = SIN_COGER;
    (*nivel) = (*nivel) - 1;
}*/

void asignacionVacia(int totalNiveles, asignacion *s)
{
    int i;
    *s = (asig *)malloc(sizeof(asig));
    (*s)->totalNiveles = totalNiveles;
    (*s)->valores = (int *)malloc(sizeof(int) * totalNiveles);
    for (i = 0; i < totalNiveles; i++)
    {
        (*s)->valores[i] = SIN_COGER;
    }
}

void destruirAsignacion(asignacion *s)
{
    free(*s);
    *s = NULL;
}

void copiarAsignacion(asignacion *sdest, asignacion sorig)
{
    int i;
    if ((*sdest) != NULL)
    {
        destruirAsignacion(sdest);
    }
    *sdest = (asig *)malloc(sizeof(asig));
    (*sdest)->totalNiveles = sorig->totalNiveles;
    (*sdest)->valores = (int *)malloc(sizeof(int) * (sorig->totalNiveles));
    for (i = 0; i < sorig->totalNiveles; i++)
    {
        (*sdest)->valores[i] = sorig->valores[i];
    }
}

void imprimirSolucion(tipoelem s)
{
    int i;
    for (i = 0; i < getNumPersonas(s.tupla); i++)
    {
        printf("Persona %d: tarea %d\n", i + 1, ((asignacion) s.tupla)->valores[i] + 1);
    }
}

void reservarMemoriaUsadas(tipoelem* e) {
    e->usadas = (int *)malloc(sizeof(int) * getNumPersonas(e->tupla));
}

void generarNodoRaiz(int totalNiveles, tipoelem *e, int** matrizBeneficios)
{
    int i;
    e->bact = 0;
    e->nivel = 0;
    asignacion a;
    asignacionVacia(totalNiveles, &a);
    e->tupla = a;
    reservarMemoriaUsadas(e);
    for (i = 0; i < totalNiveles; i++)
    {
        e->usadas[i] = 0;
    }
    calcularParametros(e, matrizBeneficios);
}

void copiarNodo(tipoelem* ndest, tipoelem norig) {
    int i;
    ndest->bact = norig.bact;
    ndest->CS = norig.CS;
    ndest->CI = norig.CI;
    ndest->BE= norig.BE;
    ndest->nivel = norig.nivel;
    copiarAsignacion(&(ndest->tupla), norig.tupla);
    ndest->usadas = (int*) malloc(sizeof(int)*getNumPersonas(norig.tupla));
    for (i = 0; i < getNumPersonas(norig.tupla); i++) {
        ndest->usadas[i] = norig.usadas[i];
    }
}

void destruirNodo(tipoelem* n) {
    destruirAsignacion(&(n->tupla));
    free(n->usadas);
}
