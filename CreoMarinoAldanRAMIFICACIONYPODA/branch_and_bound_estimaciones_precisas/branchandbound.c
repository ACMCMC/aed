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

/**
 * Devuelve el número de personas (el total de niveles) de una asignación. También se corresponde con el número de tareas, porque hay tantas personas como tareas
 */
int getNumPersonas(asignacion s)
{
    return s->totalNiveles;
}

tipoelem asignacionVoraz(tipoelem n, int **matrizBeneficios);
tipoelem _maximosTareas(tipoelem n, int **matrizBeneficios);
void destruirNodo(tipoelem *n);

/**
 * Calcula bact
 */
void _calcularBact(tipoelem *e, int **matrizBeneficios)
{
    int bact = 0;
    int i;
    for (i = 0; i <= e->nivel; i++)
    {
        bact += matrizBeneficios[i][((asignacion)(e->tupla))->valores[i]];
    }
    e->bact = bact;
}

/**
 * Calcula el máximo de la matriz de beneficios
 */
int _maximoMatrizBeneficios(int **matrizBeneficios, int numPersonas)
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

/**
 * Calcula CS
 */
void _calcularCS(tipoelem *e, int **matrizBeneficios)
{
    tipoelem nodoMaxTareas = _maximosTareas(*e, matrizBeneficios);
    e->CS = nodoMaxTareas.bact;
    destruirNodo(&nodoMaxTareas);
}

/**
 * Calcula BE
 */
void _calcularBE(tipoelem *e)
{
    e->BE = (e->CS + e->CI) / 2.0;
}

/**
 * Calcula CI
 */
void _calcularCI(tipoelem *e, int **matrizBeneficios)
{
    tipoelem nodoAsignacionVoraz = asignacionVoraz(*e, matrizBeneficios);
    e->CI = nodoAsignacionVoraz.bact;
    destruirNodo(&nodoAsignacionVoraz);
}

/**
 * Función auxiliar que calcula bact, CI, CS y BE
 */
void _calcularParametros(tipoelem *e, int **matrizBeneficios)
{
    _calcularBact(e, matrizBeneficios);
    _calcularCI(e, matrizBeneficios);
    _calcularCS(e, matrizBeneficios);
    _calcularBE(e);
}

/**
 * Imprime los valores de una asignación de tareas
 */
void imprimirSolucion(tipoelem s)
{
    int i;
    for (i = 0; i < getNumPersonas(s.tupla); i++)
    {
        printf("Persona %d: tarea %d\n", i + 1, ((asignacion)s.tupla)->valores[i] + 1);
    }
}

/**
 * Función auxiliar que imprime un nodo concreto
 */
void _imprimirNodo(tipoelem n)
{
    printf("\n");
    imprimirSolucion(n);
    printf("CS: %f\n", n.CS);
    printf("BE: %f\n", n.BE);
    printf("CI: %f\n", n.CI);
    printf("bact: %d\n", n.bact);
    printf("nivel: %d\n", n.nivel);
    printf("VECTOR: ( ");
    for (int i = 0; i < getNumPersonas(n.tupla); i++)
    {
        printf("%d, ", n.usadas[i]);
    }
    printf(")\n");
}

/**
 * Función auxiliar que imprime todos los nodos de la LNV
 */
void _imprimirLNV(lista LNV)
{
    tipoelem e;
    posicion p;
    p = primero(LNV);
    printf("\nLISTA__________\n");
    while (p != fin(LNV))
    {
        recupera(LNV, p, &e);
        _imprimirNodo(e);
        p = siguiente(LNV, p);
    }
    printf("\nFIN------------\n");
}

/**
 * Selecciona el nodo más prometedor de la LNV, con estrategia MB-LIFO
 */
tipoelem Seleccionar(lista *LNV)
{
    tipoelem e;
    float beMAX = 0.0;

    posicion p = primero(*LNV);
    while (p != fin(*LNV))
    { // Primero buscamos el máximo beneficio de toda la lista
        recupera(*LNV, p, &e);
        if (e.BE > beMAX)
        {
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

/**
 * Indica si un nodo es solución
 */
int Solucion(tipoelem n)
{
    return (n.nivel == (getNumPersonas(n.tupla) - 1));
}

/**
 * Genera una asignación vacía
 */
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

/**
 * Destruye la memoria empleada por una asignación
 */
void destruirAsignacion(asignacion *s)
{
    free(*s);
    *s = NULL;
}

/**
 * Copia una asignación en otra
 */
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

/**
 * Reserva la memoria para el vector de tareas usadas
 */
void _reservarMemoriaUsadas(tipoelem *e)
{
    e->usadas = (int *)malloc(sizeof(int) * getNumPersonas(e->tupla));
}

/**
 * Genera el nodo raíz
 */
void generarNodoRaiz(int totalNiveles, tipoelem *e, int **matrizBeneficios)
{
    int i;
    e->bact = 0;
    e->nivel = -1;
    asignacion a;
    asignacionVacia(totalNiveles, &a);
    e->tupla = a;
    _reservarMemoriaUsadas(e);
    for (i = 0; i < totalNiveles; i++)
    {
        e->usadas[i] = 0;
    }
    _calcularParametros(e, matrizBeneficios);
}

/**
 * Destruye un nodo
 */
void destruirNodo(tipoelem *n)
{
    destruirAsignacion(&(n->tupla));
    n->tupla = NULL;
    free(n->usadas);
    n->usadas = NULL;
}

/**
 * Copia un nodo en otro
 */
void copiarNodo(tipoelem *ndest, tipoelem norig)
{
    int i;
    ndest->bact = norig.bact;
    ndest->CS = norig.CS;
    ndest->CI = norig.CI;
    ndest->BE = norig.BE;
    ndest->nivel = norig.nivel;
    copiarAsignacion(&(ndest->tupla), norig.tupla);
    _reservarMemoriaUsadas(ndest);
    for (i = 0; i < getNumPersonas(norig.tupla); i++)
    {
        ndest->usadas[i] = norig.usadas[i];
    }
}

/**
 * Genera un nodo con sus campos vacíos
 */
void nodoVacio(tipoelem *n, int totalNiveles)
{
    int i;
    asignacion a;
    asignacionVacia(totalNiveles, &a);
    n->tupla = a;
    n->nivel = 0;
    _reservarMemoriaUsadas(n);
    for (i = 0; i < totalNiveles; i++)
    {
        n->usadas[i] = 0;
    }
    n->bact = 0;
    n->BE = 0;
    n->CS = 0;
    n->CI = 0;
}

/**
 * Función de iteración. Devuelve el siguiente hermano viable en el mismo nivel del nodo.
 */
int siguienteHermano(tipoelem *n, int **matrizBeneficios)
{
    int numSiguienteTarea;
    if (n->usadas[n->tupla->valores[n->nivel]] == 1)
    {
        n->usadas[n->tupla->valores[n->nivel]]--;
    }
    for (numSiguienteTarea = n->tupla->valores[n->nivel] + 1; numSiguienteTarea < getNumPersonas(n->tupla); numSiguienteTarea++)
    {
        if (n->usadas[numSiguienteTarea] == 0)
        {
            n->usadas[numSiguienteTarea]++;
            n->tupla->valores[n->nivel] = numSiguienteTarea;
            _calcularParametros(n, matrizBeneficios);
            return 1;
        }
    }
    return 0;
}

/**
 * Realiza una asignación voraz a partir de un nodo concreto
 */
tipoelem asignacionVoraz(tipoelem n, int **matrizBeneficios)
{
    tipoelem nuevoNodo;
    int maxTareasLibresPersona, indiceMaxTareasLibresPersona;
    int i, j;

    copiarNodo(&nuevoNodo, n);

    for (i = nuevoNodo.nivel + 1; i < getNumPersonas(nuevoNodo.tupla); i++)
    {
        for ((maxTareasLibresPersona = 0, j = 0); j < getNumPersonas(nuevoNodo.tupla); j++)
        {
            if (nuevoNodo.usadas[j] == 0 && matrizBeneficios[i][j] > maxTareasLibresPersona)
            {
                maxTareasLibresPersona = matrizBeneficios[i][j];
                indiceMaxTareasLibresPersona = j;
            }
        }
        nuevoNodo.usadas[indiceMaxTareasLibresPersona]++;
        nuevoNodo.tupla->valores[i] = indiceMaxTareasLibresPersona;
        nuevoNodo.nivel++;
    }
    _calcularBact(&nuevoNodo, matrizBeneficios);
    nuevoNodo.CI = nuevoNodo.bact;
    nuevoNodo.CS = nuevoNodo.bact;
    nuevoNodo.BE = nuevoNodo.bact;
    return nuevoNodo;
}

/**
 * Realiza una asignación con el máximo beneficio (aunque se repitan tareas) para cada persona a partir de un nodo
 */
tipoelem _maximosTareas(tipoelem n, int **matrizBeneficios)
{
    tipoelem nuevoNodo;
    int maxTareasLibresPersona, indiceMaxTareasLibresPersona;
    int i, j;

    copiarNodo(&nuevoNodo, n);

    for (i = nuevoNodo.nivel + 1; i < getNumPersonas(nuevoNodo.tupla); i++)
    {
        for ((maxTareasLibresPersona = 0, j = 0); j < getNumPersonas(nuevoNodo.tupla); j++)
        {
            if (n.usadas[j] == 0 && matrizBeneficios[i][j] > maxTareasLibresPersona)
            {
                maxTareasLibresPersona = matrizBeneficios[i][j];
                indiceMaxTareasLibresPersona = j;
            }
        }
        nuevoNodo.usadas[indiceMaxTareasLibresPersona]++;
        nuevoNodo.tupla->valores[i] = indiceMaxTareasLibresPersona;
        nuevoNodo.nivel++;
    }
    _calcularBact(&nuevoNodo, matrizBeneficios);
    nuevoNodo.CI = nuevoNodo.bact;
    nuevoNodo.CS = nuevoNodo.bact;
    nuevoNodo.BE = nuevoNodo.bact;
    return nuevoNodo;
}
