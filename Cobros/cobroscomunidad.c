#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define N_PLANTAS 5
#define N_PISOS 5

/**
Tenemos un pequeño programa para el cobro de los recibos de luz de una comunidad de propietarios.
La estructura de datos central del problema es una matriz bidimensional que almacena los registros
de cada uno de los propietarios de la comunidad.
*/

typedef struct registroAbonado {
    bool creado; // registro creado
    int tipoTarifa; // 0:familia numerosa, 1: jubilados, 2: general
    int numAbonado; //número abonado
    int lectAnt, lectAct; //Lectura Anterior, Le    ctura Actual kw/h
    char nombre[40];
    char nif[9];
} tAbonado;

/// tipo array con la informacion de los abonados
typedef tAbonado comunidad[N_PLANTAS][N_PISOS];


/**
tarifas del kw/h
posición 0: tarifa para familias numerosas
posición 1: tarifa para jubilados
posición 2: tarifa general
*/
const double tarifa[] = {0.01, 0.15, 0.02};


///--- Funciones (firmas) ---///
int verificar_piso(tAbonado t1, int planta, int piso, comunidad c1);
void numtipos_tarifa(int *numerosa, int *jubilado, int *general, comunidad c1);
void sustituir_abonados(tAbonado VA[], int T, tAbonado A);
double* calcular_importes(comunidad c1);


///--- Main ---///
int main(void) {
    srand(1234);
    int planta=0;
    int piso=0;

    //Creamos un tAbonado
    tAbonado t1 = {true, 0, 1245, 15, 16, "Manuel", "1X35V"};

    //Creamos una comunidad con valores aleatorios
    comunidad c1;
    for (int i = 0; i < N_PLANTAS; i++) {
        for (int j = 0; j < N_PISOS; j++) {
            c1[i][j].creado = rand() % 2;
            c1[i][j].tipoTarifa = rand() % 3;
            c1[i][j].numAbonado = rand() % 2001; // Limites aleatorios pero no muy grandes
            c1[i][j].lectAnt = rand() % (500 - 100 + 1) + 100;
            c1[i][j].lectAct = rand() % (1000 - c1[i][j].lectAnt + 1) + c1[i][j].lectAnt;
            strcpy(c1[i][j].nombre, t1.nombre); // Copiamos el mismo nombre y nif para todos
            strcpy(c1[i][j].nif, t1.nif);
        }
    }

    printf("\n---- Impresion de la comunidad ----\n");
    for (int i = 0; i < N_PLANTAS; i++) {
        for (int j = 0; j < N_PISOS; j++) {
            printf("\nPlanta %d --- Piso %d \n", i, j);

            if (c1[i][j].creado == false) {
                printf("Estado: Libre\n");
            } else {
                switch (c1[i][j].tipoTarifa) {
                    case 0:
                        printf("Tarifa: Familia numerosa\n");
                        break;

                    case 1:
                        printf("Tarifa: Jubilado\n");
                        break;

                    case 2:
                        printf("Tarifa: General\n");
                        break;
                    default: ;
                }
                printf("Numero Abonado: %d\n", c1[i][j].numAbonado);
                printf("Lectura anterior: %d\n", c1[i][j].lectAnt);
                printf("Lectura actual : %d\n", c1[i][j].lectAct);
                printf("Nombre: %s\n", c1[i][j].nombre);
                printf("NIF: %s\n", c1[i][j].nif);
            }
        }
    }


    printf("\n---- Prueba funcion verificar_piso ----\n");
    printf("Inserte el numero de planta(0-4): ");
    scanf("%d", &planta);
    printf("Inserte el numero de piso(0-4): ");
    scanf("%d", &piso);

    switch (verificar_piso(t1, planta, piso, c1)) {
        case 0:
            printf("Planta o piso no validos");
            break;

        case -1:
            printf("Piso ocupado");
            break;

        case 1:
            printf("Piso libre");

            printf("\n---Imprimimos el piso seleccionado para verificar---\n");
            printf("\nSi estaba libre, se insertan los datos de t1, si no imprime lo mismo que habia\n");

            switch (c1[piso][planta].tipoTarifa) {
                case 0:
                    printf("Tarifa: Familia numerosa\n");
                    break;

                case 1:
                    printf("Tarifa: Jubilado\n");
                    break;

                case 2:
                    printf("Tarifa: General\n");
                    break;
                default: ;
            }
            printf("Numero Abonado: %d\n", c1[piso][planta].numAbonado);
            printf("Lectura anterior: %d\n", c1[piso][planta].lectAnt);
            printf("Lectura actual : %d\n", c1[piso][planta].lectAct);
            printf("Nombre: %s\n", c1[piso][planta].nombre);
            printf("NIF: %s\n", c1[piso][planta].nif);
            break;

        default: ;
    }


    printf("\n\n---- Prueba funcion numtipos_tarifa ----\n\n");
    int num_numerosa = 0;
    int num_jubilado = 0;
    int num_general = 0;
    numtipos_tarifa(&num_numerosa, &num_jubilado, &num_general, c1);

    printf("Familia numerosa: %d\n",num_numerosa);
    printf("Jubilados: %d\n",num_jubilado);
    printf("General: %d\n",num_general);


    printf("\n\n---- Prueba funcion sustituir_abonados----\n\n");

    tAbonado VA[3] = {
        {true, 2, 104, 100, 150, "Juan Perez", "12345678A"},
        {false, 0, 0, 0, 0, "", ""},
        {true, 2, 205, 200, 280, "Maria Gomez", "87654321B"}
    };

    int T = 3;

    // Queremos actualizar a Juan Perez (ID 104) porque ahora es jubilado (tarifa 1)
    tAbonado A = {true, 1, 104, 150, 150, "Juan Perez (Actualizado)", "12345678A"};

    printf("--- ESTADO INICIAL DEL VECTOR ---\n");
    for (int i = 0; i < T; i++) {
        if (VA[i].creado) {
            printf("Posicion %d -> ID: %d, Nombre: %s, Tarifa: %d\n", i, VA[i].numAbonado, VA[i].nombre, VA[i].tipoTarifa);
        } else {
            printf("Posicion %d -> [Vacio]\n", i);
        }
    }

    sustituir_abonados(VA, T, A);

    printf("\n--- ESTADO FINAL (DESPUES DE LA FUNCION) ---\n");
    for (int i = 0; i < T; i++) {
        if (VA[i].creado) {
            printf("Posicion %d -> ID: %d, Nombre: %s, Tarifa: %d\n", i, VA[i].numAbonado, VA[i].nombre, VA[i].tipoTarifa);
        } else {
            printf("Posicion %d -> [Vacio]\n", i);
        }
    }



    printf("\n\n---- Prueba funcion calcular_importes----\n\n");
    // Uso de malloc y punteros (muy importante)
    double *importe = calcular_importes(c1);
    int k=0;
    for (int i = 0; i < N_PLANTAS; i++) {
        for (int j = 0; j < N_PISOS; j++) {
        printf("Planta %d, Piso %d: %.2lf euros\n",i, j, importe[k]);
        k++;
        }
    }
    free(importe); // Liberamos el espacio que habíamos reservado tras utilizar la matriz
    return 0;
}

/**
Función 1
Dados un abonado, un número de planta y un número de piso(pasados como argumentos a la función)

Lo añada a la comunidad de vecinos (también pasada como argumento).

La función devolverá -1 si el piso que se quiere dar de alta ya está ocupado y 1 si está libre.*/

int verificar_piso(tAbonado t1, int planta, int piso, comunidad c1) {
    if (planta >= N_PLANTAS || planta < 0 || piso >= N_PISOS || piso < 0) {
        return 0; // Planta y piso erróneos
    }
    if (c1[planta][piso].creado == true) {
        return -1; // Piso Ocupado
    }
    // Piso libre por lo que añadimos t1 a la posición
    c1[planta][piso] = t1;
    return 1;
}



/**
Función 2

Función que devuelva usando los parámetros de la misma.

Cuantos abonados son familia numerosa, cuantos son jubilados y cuantos
pertenecen a la categoría restante.*/

void numtipos_tarifa(int *numerosa, int *jubilado, int *general, comunidad c1) {
    for (int i = 0; i < N_PLANTAS; i++) {
        for (int j = 0; j < N_PISOS; j++) {
            if (c1[i][j].creado == true) {
                switch (c1[i][j].tipoTarifa) {
                    case 0:
                        (*numerosa)++;
                        break;
                    case 1:
                        (*jubilado)++;
                        break;
                    case 2:
                        (*general)++;
                        break;
                    default: ;
                }
            }
        }
    }
}



/**
Función 3

Implementa una función que acepte como argumentos un vector de abonados (VA),
el tamaño del vector (T) y un abonado (A).

Sustituya todos los abonados del vector VA que pertenezcan a la matriz de abonados,
por el abonado A.

Dos abonados son el mismo, si el número de abonado es el mismo.

Sirve para ACTUALIZAR o MODIFICAR la información de un usuario de forma masiva y segura.*/

void sustituir_abonados(tAbonado VA[], int T, tAbonado A) {
    if (T > 0) {
        for (int i=0; i < T; i++) {
            if (VA[i].creado== true && VA[i].numAbonado == A.numAbonado) {
                VA[i]=A;
            }
        }
    }
}

/**
Función 4
Implementa una función que, a partir de la matriz de abonados, pasada como argumento.

Devuelva una matriz de doubles con el importe a pagar por cada abonado.
*/

double* calcular_importes(comunidad c1) {
    // Pedimos memoria para TODOS los pisos de golpe en una sola tira
    int total_pisos = N_PLANTAS * N_PISOS;
    double* importes = malloc(total_pisos * sizeof(double));

    int k = 0; // Contador de piso

    for (int i = 0; i < N_PLANTAS; i++) {
        for (int j = 0; j < N_PISOS; j++) {
            if (c1[i][j].creado == true) {
                int consumo = c1[i][j].lectAct - c1[i][j].lectAnt;
                int tipo = c1[i][j].tipoTarifa;

                // Lo guardamos en nuestra tira usando la "posicion" k.
                importes[k] = consumo * tarifa[tipo];

            } else {
                importes[k] = 0.0;
            }
            k++;
        }
    }
    return importes;
}