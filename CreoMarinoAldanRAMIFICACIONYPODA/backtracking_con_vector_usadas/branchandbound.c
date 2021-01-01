#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void calcularBact(tipoelem *e, int **matrizBeneficios)
{
    int bact = 0;
    int i;
    for (i = 0; i < e->nivel; i++)
    {
        bact += matrizBeneficios[e->nivel][((asignacion)(e->tupla))->valores[i]];
    }
    e->bact = bact;
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

void calcularCI(tipoelem *e)
{
    e->CI = e->bact;
}

void calcularParametros(tipoelem *e, int **matrizBeneficios)
{
    calcularBact(e, matrizBeneficios);
    calcularCI(e);
    calcularCS(e, matrizBeneficios);
    calcularBE(e);
}

void imprimirSolucion(tipoelem s)
{
    int i;
    for (i = 0; i < getNumPersonas(s.tupla); i++)
    {
        printf("Persona %d: tarea %d\n", i + 1, ((asignacion) s.tupla)->valores[i] + 1);
    }
}

void _imprimirNodo(tipoelem n) {
        printf("\n" );
    imprimirSolucion(n);
    printf("CS: %f\n", n.CS);
    printf("BE: %f\n", n.BE);
    printf("CI: %f\n", n.CI);
    printf("bact: %d\n", n.bact);
    printf("nivel: %d\n", n.nivel);
        printf("VECTOR: ( " );
    for (int i = 0; i < getNumPersonas(n.tupla); i++) {
        printf("%d, ", n.usadas[i]);
    }
        printf(")\n" );
}

void _imprimirLista(lista LNV) {
    tipoelem e;
    posicion p;
    p = primero(LNV);
    printf("\nLISTA__________\n");
    while (p != fin(LNV)) {
    recupera(LNV, p, &e);
    _imprimirNodo(e);
    p = siguiente(LNV, p);
    }
    printf("\nFIN------------\n");
}

tipoelem Seleccionar(lista* LNV) {
    tipoelem e;
    float beMAX = 0.0;
    
    posicion p = primero(*LNV);
    while (p != fin(*LNV)) { // Primero buscamos el máximo beneficio de toda la lista
        recupera(*LNV, p, &e);
        if (e.BE > beMAX) {
            beMAX = e.BE;
        }
        p = siguiente(*LNV, p);
    }
    p = fin(*LNV); // Después buscamos el primero nodo desde el final que tiene el máximo beneficio (LIFO)
    do
    {
        p = anterior(*LNV, p);
        recupera(*LNV, p, &e);
    } while (fabs(e.BE - beMAX) > 0.1);

    suprime(LNV, p);

    return e;
}

int Solucion(tipoelem n)
{
    return (n.nivel == (getNumPersonas(n.tupla) - 1));
}

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
    *sdest = (asig *)malloc(sizeof(asig));
    (*sdest)->totalNiveles = sorig->totalNiveles;
    (*sdest)->valores = (int *)malloc(sizeof(int) * (sorig->totalNiveles));
    for (i = 0; i < sorig->totalNiveles; i++)
    {
        (*sdest)->valores[i] = sorig->valores[i];
    }
}

void reservarMemoriaUsadas(tipoelem* e) {
    e->usadas = (int *)malloc(sizeof(int) * getNumPersonas(e->tupla));
}

void generarNodoRaiz(int totalNiveles, tipoelem *e, int** matrizBeneficios)
{
    int i;
    e->bact = 0;
    e->nivel = -1;
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

void destruirNodo(tipoelem* n) {
    destruirAsignacion(&(n->tupla));
    n->tupla = NULL;
    free(n->usadas);
    n->usadas = NULL;
}

void copiarNodo(tipoelem* ndest, tipoelem norig) {
    int i;
    ndest->bact = norig.bact;
    ndest->CS = norig.CS;
    ndest->CI = norig.CI;
    ndest->BE= norig.BE;
    ndest->nivel = norig.nivel;
    copiarAsignacion(&(ndest->tupla), norig.tupla);
    reservarMemoriaUsadas(ndest);
    for (i = 0; i < getNumPersonas(norig.tupla); i++) {
        ndest->usadas[i] = norig.usadas[i];
    }
}

void nodoVacio(tipoelem* n, int totalNiveles) {
    int i;
    asignacion a;
    asignacionVacia(totalNiveles, &a);
    n->tupla = a;
    n->nivel = 0;
    reservarMemoriaUsadas(n);
    for (i = 0; i < totalNiveles; i++)
    {
        n->usadas[i] = 0;
    }
    n->bact = 0;
    n->BE = 0;
    n->CS = 0;
    n->CI = 0;
}

int siguienteHermano(tipoelem* n, int** matrizBeneficios) {
    int numSiguienteTarea;
    if (n->usadas[n->tupla->valores[n->nivel]]==1) {
        n->usadas[n->tupla->valores[n->nivel]]--;
    }
    for (numSiguienteTarea = n->tupla->valores[n->nivel] + 1; numSiguienteTarea < getNumPersonas(n->tupla); numSiguienteTarea++) {
        if (n->usadas[numSiguienteTarea] == 0) {
            n->usadas[numSiguienteTarea]++;
            n->tupla->valores[n->nivel] = numSiguienteTarea;
            calcularParametros(n, matrizBeneficios);
            return 1;
        }
    }
    return 0;
}
