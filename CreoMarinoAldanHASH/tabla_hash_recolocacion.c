#include "tabla_hash_recolocacion.h"

/* TABLA HASH CON RECOLOCACION */

void InicializarTablaHash(TablaHash t)
{
    int i;

    for (i = 0; i < Tam; i++)
        t[i].clave[0] = VACIO;
}

/******* FUNCIONES HASH *******/

/* FUNCION HASH 1 */
/*
int Hash(char *cad) {
    int valor;
    unsigned char *c;

    for (c = cad, valor = 0; *c; c++)
        valor += (int) *c;

    return (valor % Tam);
}
*/

/* FUNCION HASH 2 */
int Hash(char *cad)
{
    int i, suma = 0;
    for (i = strlen(cad) - 1; i >= 0; i--)
    {
        suma = (suma * 256 + cad[i]) % Tam;
    }
    return suma;
}

/* FUNCION HASH 3: Probad al menos dos valores para la constante K */
/*
  int Hash (char *cad){
     int i,suma=0;
     int K=500;
     for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*K+cad[i])%Tam;
     }
     return suma;
 }
*/

/* RECOLOCACION LINEAL: depende del valor de la constante a*/

/* Funci�n que localiza la posici�n del elemento cuando buscamos*/
int _PosicionBuscar(TablaHash t, char *cad)
{
    /* Devuelve el sitio donde est� la clave cad, o donde deber�a estar. */
    /* No tiene en cuenta los borrados para avanzar.                     */

    int ini, i, aux, a;
    /* Hay que dar valor a la variable de recolocaci�n a */

    ini = Hash(cad);

    for (i = 0; i < Tam; i++)
    {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}

/*Funci�n que localiza la posicion para insertar un elemento */
int _PosicionInsertar(TablaHash t, char *cad, int *pasosAdicionales)
{
    // Devuelve el sitio donde podriamos poner el elemento de clave cad

    int ini, aux, i, a;

    *pasosAdicionales = 0; // Cuenta el número de intentos fallidos de ubicar el dato

    /* Hay que dar un valor a la variable de recolocaci�n a */
    a = 1;

    ini = Hash(cad);

    for (i = 0; i < Tam; i++)
    {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO)
        {
            return aux;
        }
        if (!strcmp(t[aux].clave, cad))
        {
            return aux;
        }
        (*pasosAdicionales)++;
    }
    return ini;
}

/* RECOLOCACION CUADRATICA */

/*
int _PosicionBuscar(TablaHash t, char *cad) {
    // Devuelve el sitio donde esta cad  o donde deberia  estar. 
    // No tiene en cuenta los borrados.

    int ini, i, aux;
 
    ini = Hash(cad);
 
    for (i = 0; i < Tam; i++) {
        aux = (ini + i*i) % Tam;
        if (t[aux].clave[0aux = (ini + i*i) % Tam] == VACIO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}

int _PosicionInsertar(TablaHash t, char *cad) {
   //Devuelve el sitio donde podriamos poner cad (recolocacion cuadratica)
    int ini, i, aux;

    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + i*i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}
*/

/* Funcion que indica si un elemento est� o no en la tabla */
/* Devuelve 1 si el elemento de clave cad est� en la tabla, 0 si no est� */
int MiembroHash(TablaHash t, char *cad)
{

    int nCol, colision;
    int pos = _PosicionBuscar(t, cad);

    if (t[pos].clave[0] == VACIO)
        return 0;
    else
        return (!strcmp(t[pos].clave, cad));
}

/* BUSCA UN ELEMENTO CON LA CLAVE INDICADA EN LA TABLA HASH, Y LO DEVUELVE, 
 * ADEMAS DE INDICAR CON 1 QUE EXISTE EL ELEMENTO, Y CON 0 QUE NO ESTA EN LA TABLA */
int Busqueda(TablaHash t, char *clavebuscar, tipo_jugador *e)
{

    int pos = _PosicionBuscar(t, clavebuscar);

    if (t[pos].clave[0] == VACIO)
        return 0;
    else
    {
        if (strcmp(t[pos].clave, clavebuscar) == 0)
        {
            *e = t[pos];
            return 1;
        }
        else
            return 0;
    }
}

/* Funci�n que inserta un elemento en la tabla
 * Devuelve o si no hubo colisión; en caso contrario un número positivo que indica el número de pasos adicionales
*/
int InsertarHash(TablaHash t, tipo_jugador e)
{
    int pos;

    int numPasosAdicionales; // Parámetro de salida de _PosicionInsertar

    pos = _PosicionInsertar(t, e.clave, &numPasosAdicionales);

    if (t[pos].clave[0] == VACIO || t[pos].clave[0] == BORRADO)
    {
        t[pos] = e;
    }
    else if (strcmp(t[pos].clave, e.clave))
    {
        printf("No se encuentra posicion libre.\n");
    }
    return numPasosAdicionales;
}

/* Funci�n que elimina un elemento de la tabla */
void BorrarHash(TablaHash t, char *cad)
{

    int pos = _PosicionBuscar(t, cad);

    if (t[pos].clave[0] != VACIO && t[pos].clave[0] != BORRADO)
    {
        if (!strcmp(t[pos].clave, cad))
        {
            t[pos].clave[0] = BORRADO;
            t[pos].clave[1] = VACIO;
        }
    }
}
