#include <stdio.h>
#include <stdlib.h>

#define N_FILAS 10
#define N_COLUMNAS 7

/**

EJERCICIO PROPUESTO:
En el puerto de Valencia, acaban de contratar a un encargado para controlar el
peso de los contenedores que descargan los barcos de mercancías. Este individuo tiene
cierta obsesión hacia los números primos, no permitiendo que el peso en toneladas de
los contenedores de carga de los barcos no sea un número primo (únicamente la parte
entera, por ejemplo: 29’64553 toneladas, se acepta porque 29 es primo)

Los contenedores que no cumplan esa condición, los devuelve a su barco de origen

 **/


// Información relativa al contenedor
typedef struct {
    int identificador;
    int peso;
    char descripcion[101];
    char empresa_orig[21];
    char empresa_dest[21];

}Contenedor;

typedef Contenedor hub[N_FILAS][N_COLUMNAS];



int compruebaPeso(int peso);
int apilaContenedor(hub h1, Contenedor c1);
int quitaContenedor(int columna,hub h1, int *identificador);


int main(void) {
    srand(2454);
    double p_contenedor;
    Contenedor c1 = {12345,17.567,"Textiles de la India","Oso SL","Lari SA"};
    Contenedor c2 = {61543,33.117,"Repuestos de Bankok","Ban SA","Maeyt SA"};
    Contenedor c3 = {98643,10.641,"Paqueteria de China","Poew SL","Vase SA"};

    hub h1;
    for (int i=0 ; i < N_FILAS)

    printf("\n----- BIENVENIDO AL PROGRAMA DE CONTROL DE MERCANCIAS -----\n");

    do {
        printf("Por favor introduzca el peso exacto del contenedor: ");
        scanf("%lf",&p_contenedor);

        if (p_contenedor > 0) {
            switch (compruebaPeso((int) p_contenedor)) {
                case 0:
                    printf("-> Rechace la descarga <-\n");
                    break;
                case 1:
                    printf("-> Acepte la descarga <-\n");
                    break;
                default:;
            }
        }
    }while (p_contenedor != 0);

    int opcion;
    if (compruebaPeso((int) p_contenedor) == 1) {
        do {
            printf("1 - Apilar Contenedor\n2- Quitar Contenedor\n3- Volver");
            scanf("%d", &opcion);
        } while (opcion < 1 || opcion >3);
    }

    return 0;
}



/**

FUNCIÓN 1
Devuelve:
a. Si un peso pasado como parámetro es un número primo -> 1
b. Si un peso pasado como parámetro no es un número primo -> 0
Esta función sólo aceptará números enteros positivos, si se le pasa un número
negativo devolverá 0. Además, el peso máximo de un contenedor es 32
toneladas, por lo que devolverá 0 si el peso es mayor.

*/
int compruebaPeso(int peso) {
    if (peso <= 1 || peso > 32) return 0;
    if (peso == 2) return 1;
    if (peso % 2 == 0) return 0;

    for (int i = 3; i < peso ; i++) {
        if (peso % i == 0) {
            return 0;
        }
    }
    return 1;
}


/**

FUNCIÓN 2
Se le pasa como argumento la matriz de contenedores (estructuras) y apila un
contenedor, empezando por la última columna de la matriz. Si la última
columna está llena, pasará a comprobar la anterior, y así sucesivamente
hasta encontrar un hueco o hasta comprobar que la matriz está llena. Si se
encontró un hueco, se devolverá usando la sentencia return un 1, y si no se
encontró hueco, se devolverá un 0.

*/
int apilaContenedor(hub h1, Contenedor c1) {
    for (int j=N_COLUMNAS-1; j >= 0; j--){
         for (int i=N_FILAS-1; i >= 0;i--){
            if (h1[i][j].identificador == -1){
                h1[i][j]=c1;
                return 1; // Hueco libre
            }
        }
    }
    return 0;
}



/**

FUNCIÓN 3
Acepta como argumento de qué columna queremos quitar un contenedor, y quita un
contenedor de esa columna (para eliminar un contenedor de una columna
pondremos su número de identificación a -1). La función también devolverá
por referencia el número de identificación del contenedor eliminado. Si la
columna está vacía, devolverá por referencia el valor -1

*/
int quitaContenedor(int columna,hub h1, int *identificador) {
    if (columna > N_COLUMNAS-1 || columna < 0) return 0; // Columna no valida
    for (int i = 0; i < N_FILAS;i++) {
        if (h1[i][columna].identificador >= 0) {
            *identificador= h1[i][columna].identificador; // Pasamos por referencia el identificador
            h1[i][columna].identificador = -1; // Quitamos contenedor
            return 1;
        }
    }
    *identificador = -1;   // No encuentro. Columna vacia
    return 0;
}






















