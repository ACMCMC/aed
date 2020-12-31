#ifndef LISTA_H
#define LISTA_H

/**
 * Representa un vector de asignación de tareas; p.ej, (0,1,2,3,4). No le llamo solución, porque sólo es solución si es una asignación completa y válida.
 */
typedef struct
{
    int *valores;
    int totalNiveles;
} asig;

typedef asig *asignacion;

typedef struct
{
    asignacion tupla;
    int nivel, bact;
    float CI, BE, CS;
    int* usadas;
} tipoListaNodosVivos;

typedef tipoListaNodosVivos tipoelem;

struct celda
{
    tipoelem elemento;
    struct celda *sig;
};

typedef struct celda *posicion;

struct l
{
    posicion inicio;
    unsigned longitud;
    posicion fin;
};

typedef struct l *lista;

void crea(lista *l);
void destruye(lista *l);
posicion primero(lista l);
posicion siguiente(lista l, posicion p);
posicion fin(lista l);
posicion anterior(lista l, posicion p);
unsigned existe(lista l);
unsigned esvacia(lista l);
void recupera(lista l, posicion p, tipoelem *e);
unsigned longitud(lista l);
void inserta(lista *l, posicion p, tipoelem e);
void suprime(lista *l, posicion p);
void modifica(lista *l, posicion p, tipoelem e);
posicion posinser(lista l, tipoelem e);

#endif