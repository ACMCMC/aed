/* 
 * Tabla hash con encadenamiento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define Tam 20000
/*DEFINIR NUMERO de entradas en la tabla.*/

typedef lista TablaHash[Tam];

void InicializarTablaHash(TablaHash t);
void DestruirTablaHash(TablaHash t);
int Hash(char *cad);
int Busqueda(TablaHash t, char *clavebuscar, tipoelem *e, int *pasosAdicionales);
int MiembroHash(TablaHash t, char *clavebuscar);
int InsertarHash(TablaHash *t, tipoelem elemento);
void BorrarHash(TablaHash *t, char *claveborrar);
