#include "tabla_hash_encadenamiento.h"

/* TABLA HASH CON ENCADENAMIENTO */

/* CREAR TABLA VACIA */
void InicializarTablaHash(TablaHash t)
{
   int i;
   for (i = 0; i < Tam; i++)
      crea(&t[i]);
}

/* DESTRUIR TABLA */
void DestruirTablaHash(TablaHash t)
{
   int i;
   for (i = 0; i < Tam; i++)
      destruye(&t[i]);
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

/* BUSCA UN ELEMENTO CON LA CLAVE INDICADA EN LA TABLA HASH, Y LO DEVUELVE, 
 * ADEMAS DE INDICAR CON 1 QUE EXISTE EL ELEMENTO, Y CON 0 QUE NO ESTA EN LA TABLA */
int Busqueda(TablaHash t, char *clavebuscar, tipoelem *e, int* colision, int* pasosAdicionales)
{
   posicion p;
   int enc;
   tipoelem ele;
   int pos = Hash(clavebuscar);

   p = primero(t[pos]);
   enc = 0;

   while (p != fin(t[pos]) && !enc)
   {
      recupera(t[pos], p, &ele);
      if (strcmp(ele.clave, clavebuscar) == 0)
      {
         enc = 1;
         *e = ele;
      }
      else
         p = siguiente(t[pos], p);
   }

   return enc;
}

/* DEVUELVE 1 SI EL ELEMENTO e ESTA EN LA TABLA Y 0 SI NO LO ESTA */
int MiembroHash(TablaHash t, char *clavebuscar)
{
   posicion p;
   int enc;
   tipoelem elemento;
   int pos = Hash(clavebuscar);
   p = primero(t[pos]);
   enc = 0;
   while (p != fin(t[pos]) && !enc)
   {
      recupera(t[pos], p, &elemento);
      if (strcmp(clavebuscar, elemento.clave) == 0)
         enc = 1;
      else
         p = siguiente(t[pos], p);
   }

   return enc;
}

/* INSERTA UN ELEMENTO EN LA TABLA HASH: AL PRINCIPIO DE LA LISTA EN LA 
 * POSICION INDICADA POR LA FUNCION HASH 
 * Devuelve 1 si hubo colisión, 0 en caso contrario*/
int InsertarHash(TablaHash *t, tipoelem elemento)
{
   int pos, colision;

   pos = Hash(elemento.clave);

   colision = esvacia((*t)[pos]);

   inserta(&(*t)[pos], primero((*t)[pos]), elemento);

   return colision;
}

/* Elimina de la tabla el elemento con la clave indicada */
void BorrarHash(TablaHash *t, char *claveborrar)
{
   posicion p;
   tipoelem elemento;
   int pos = Hash(claveborrar);

   p = primero((*t)[pos]);
   recupera((*t)[pos], p, &elemento);
   while (p != fin((*t)[pos]) && strcmp(claveborrar, elemento.clave))
   {
      p = siguiente((*t)[pos], p);
      recupera((*t)[pos], p, &elemento);
   }
   if (p != fin((*t)[pos]))
      suprime(&(*t)[pos], p);
}
