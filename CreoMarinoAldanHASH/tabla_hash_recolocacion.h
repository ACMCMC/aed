/* 
 * File:   tablas_hash_recolocacion.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Tam 10000
/*DEFINIR NUMERO de entradas en la tabla.*/
#define VACIO '\0'
#define BORRADO ' '

typedef struct
{
    char nombre[15];
    char apellido1[15];
    char apellido2[15];
    char clave[20];
    char correo[60];
} tipo_jugador;

typedef tipo_jugador TablaHash[Tam];

void InicializarTablaHash(TablaHash t);
int Hash(char *cad);
int MiembroHash(TablaHash t, char *cad);
int Busqueda(TablaHash t, char *cad, tipo_jugador *e, int* pasosAdicionales);
int InsertarHash(TablaHash t, tipo_jugador e);
void BorrarHash(TablaHash t, char *cad);
