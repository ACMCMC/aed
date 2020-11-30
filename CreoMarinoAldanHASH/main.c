#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tabla_hash_recolocacion.h"

int main()
{
    clock_t inicio, fin;
    double tiempoconsumido;

    FILE * fid;
    fid = fopen("jugadores_amongETSE.txt", "r");

    tipo_jugador jugador;
    TablaHash tabla;
    InicializarTablaHash(&tabla);

    int colisiones = 0;
    int pasosAdicionales = 0;
    int sumaPasosAdicionales = 0;

    inicio = clock();
    /** aquí el código a medir **/

for (int i = 1; i <= 10000; i++) {
    fscanf(fid, "%s %s %s - %s - %s", jugador.nombre, jugador.apellido1, jugador.apellido2, jugador.clave, jugador.correo);
    pasosAdicionales = InsertarHash(tabla, jugador);
    sumaPasosAdicionales += pasosAdicionales;
    colisiones += pasosAdicionales > 0 ? 1 : 0;
    
    // Contar operaciones y colisiones
}

printf("%d colisiones.\n", colisiones);
printf("%d pasos adicionales.\n", sumaPasosAdicionales);

    fin = clock();
    tiempoconsumido = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("%lf", tiempoconsumido);

    //DestruirTablaHash(&tabla);
}
