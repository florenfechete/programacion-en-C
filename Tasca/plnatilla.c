#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CAPACIDAD_MESAS 6 //Número máximo de plazas por mesa
#define MAX_MESAS 15 //Número máximo de mesas por tasca
#define MAX_TASCAS 20 // Número máximo de tascas de la asociación

typedef struct {
    int plazasDisponibles; // número de plazas libres en la mesa
    int ocupada; // 1 ocupada; 0 libre
    char nombreReserva[100];
} Mesa;

typedef struct {
    char nombre[20];
    Mesa mesas[MAX_MESAS];
    int numMesasOcupadas; // cuantas mesas ocupadas hay en la Tasca
} Tasca;

typedef struct {
    Tasca R[MAX_TASCAS];
    char nombreAtafe[20];
} Atafe;


// Inicializa una tasca con un número determinado de mesas de forma aleatoria.
// El argumento es el nombre de la tasca.
Tasca inicializaTasca(char  nombre[]) {
    Tasca t;
    strcpy(t.nombre, nombre);
    t.numMesasOcupadas = 0;


    for (int i = 0; i < MAX_MESAS; i++) {
        Mesa m;
        m.ocupada = rand() % 2; // genera true o false de forma aleatoria

        if (m.ocupada) {
            int plazasOcupadas = 1 + rand() % CAPACIDAD_MESAS;
            m.plazasDisponibles = CAPACIDAD_MESAS - plazasOcupadas;
            sprintf(m.nombreReserva, "Reserva%d", i + 1);
            t.numMesasOcupadas++;

        } else {
            m.plazasDisponibles = CAPACIDAD_MESAS;
            m.ocupada=0;
            strcpy(m.nombreReserva, "");
        }
        t.mesas[i]=m;
    }

    return t;
}

// Muestra toda la información de la asociación de tascas.
void mostrarAtafe(Atafe atafe) {
    printf("Nombre de la Atafe: %s\n", atafe.nombreAtafe);

    for (int r = 0; r < MAX_TASCAS; r++) {
        Tasca tasca = atafe.R[r];

        if (strlen(tasca.nombre)>0) {
            printf("\n%s:\n", tasca.nombre);
            printf("Mesas ocupadas: %d\n", tasca.numMesasOcupadas);

            for (int m = 0; m < MAX_MESAS; m++) {
                Mesa mesa = tasca.mesas[m];

                if (mesa.plazasDisponibles > 0 || mesa.ocupada) {
                    char mensaje1[20],mensaje2[20];
                    if(mesa.ocupada) {
                        strcpy(mensaje1,"Ocupada");
                        strcpy(mensaje2,mesa.nombreReserva);
                    }
                    else{
                        strcpy(mensaje1,"Libre");
                        strcpy(mensaje2,"Ninguno");
                    }
                    printf("Mesa %d: %s | Plazas disponibles: %d | Reserva: %s\n",
                           m + 1,
                           mensaje1,
                           mesa.plazasDisponibles,
                           mensaje2);
                }
            }
        }
    }
}



// SOLUCIÓN AL APARTADO 1.
bool buscarReserva(Atafe atafe, char nombreBuscado[100], int *totalMesas, int *totalPersonas){
    *totalMesas = 0;
    *totalPersonas = 0;

    for (int r = 0; r < MAX_TASCAS; r++) {
        Tasca tasca = atafe.R[r];
        if (strlen(tasca.nombre)>0) {
            for (int i = 0; i < MAX_MESAS; i++) {
                if (tasca.mesas[i].ocupada == 1 && strcmp(tasca.mesas[i].nombreReserva, nombreBuscado) == 0) {
                    *totalMesas += 1 ;
                    *totalPersonas += (CAPACIDAD_MESAS - tasca.mesas[i].plazasDisponibles);
                }
            }
        }

    }
    if (*totalMesas != 0) {
        return true;
    } return false;
}


// SOLUCIÓN AL APARTADO 2.
bool intentarReservar(Atafe atafe, int comensales, char nombreTasca[20]) {
    int plazasLibres=0;
    for (int r = 0; r < MAX_TASCAS; r++) {
        Tasca tasca = atafe.R[r];
        if (strcmp(tasca.nombre, nombreTasca) == 0) {
            for (int i = 0; i < MAX_MESAS; i++) {
                if (CAPACIDAD_MESAS == tasca.mesas[i].plazasDisponibles) {
                    plazasLibres += 6;
                }
            }
            if (comensales <= plazasLibres) {
                return true;
            }
        }
    }
    return false;
}



// PROGRAMA PRINCIPAL
int main() {
    
    srand(time(NULL));  // Semilla aleatoria
    Atafe miAtafe;
    strcpy(miAtafe.nombreAtafe, "ATAFE");

    //a. Inicializa una nueva tasca de nombre "Tasca A" y colócala en la posición 0 del vector de tascas.
    miAtafe.R[0]= inicializaTasca("Tasca A");

    //b. Inicializa una nueva tasca de nombre "Tasca B" y colócala en la posición 1 del vector de tascas.
    miAtafe.R[1]= inicializaTasca("Tasca B");

    //c. Pon vacías el resto de tascas del vector de tascas. Una tasca está vacía si su nombre es "".
    for (int i=2; i < MAX_TASCAS; i++) {
        miAtafe.R[i]= inicializaTasca("");
    }

    //d. Llama a la función que muestra en pantalla toda la información de la asociación de tascas.
    printf("-------- IMPRESION DEL ATAFE --------\n");
    mostrarAtafe(miAtafe);

    //e. Llama a la función que has creado en el apartado 1. para el nombre “Reserva2”
    //   y muestra en pantalla la información devuelta por la función, si “Reserva2” tiene alguna
    //   reserva. En caso contrario, se mostrará el mensaje “Reserva2 no tiene ninguna reserva”.

    printf("\n\n------| Prueba de la funcion buscarReserva |------\n");
    int totalMesas, totalPersonas;
    bool existe = buscarReserva(miAtafe,"Reserva2", &totalMesas, &totalPersonas);
    if (existe == true) {
        printf("\nReserva 2: \nMesas ocupadas - %d \nPersonas - %d", totalMesas,totalPersonas);
    } else printf("Reserva 2 no tiene ninguna resera\n");

    //f. Llama a la función que has creado en el apartado 2. para la “Tasca B” y 20 comensales.
    //   Muestra en pantalla un mensaje indicando si hay sitio o no lo hay.
    printf("\n\n------| Prueba de la funcion intentarReservar (caso exito) |------\n");
    int comensales = 20;
    char nombreTasca[20] = "Tasca B";
    if (intentarReservar(miAtafe,comensales,nombreTasca)) {
        printf("\n\nHay sitio para los %d comensales en la %s\n", comensales, nombreTasca);
    }
    else printf("\n\nNo hay sitio para los %d comensales en la %s\n", comensales, nombreTasca);


    //g.  Llama a la función que has creado en el apartado 2. para la “Tasca B” y 250 comensales.
    //    Muestra en pantalla un mensaje indicando si hay sitio o no lo hay.
    printf("\n\n------| Prueba de la funcion intentarReservar |------\n");
    int comensales2 = 250;
    char nombreTasca2[20] = "Tasca B";
    if (intentarReservar(miAtafe,comensales2,nombreTasca2)) {
        printf("\n\nHay sitio para los %d comensales en la %s\n\n", comensales2, nombreTasca2);
    }
    else printf("\n\nNo hay sitio para los %d comensales en la %s\n\n", comensales2, nombreTasca2);


    return 0;
}
