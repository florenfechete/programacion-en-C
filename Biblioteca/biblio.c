#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#define NUM_BOOKS 10 // número máximo de libros
#define MAX_LOANS 100 // número máximo de prestamos
#define MAX_BOOKS_PER_LOAN 4 // número máximo libros distintos por prestamo
#define MAX_USERS 50 // número máximo de usuarios

// Estructura para almacenar la información de un libro en el inventario
typedef struct {
    char titulo[50]; // Título del libro
    char autor[50]; // Autor del libro
    int cantidad; // Cantidad de copias del libro disponibles en el inventario
    int codigo; // Código único del libro
} LibroStock;

// Estructura para almacenar una fecha
typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

// Estructura para almacenar la información de un libro en un préstamo
typedef struct {
    int codigo; // Código único del libro
    int cantidad; // Cantidad de copias del libro en el préstamo
} LibroPrestamo;



// Estructura para almacenar la información de un usuario
typedef struct {
    char nombre[50]; // Nombre del usuario
    char nif[10];
    int codigo; //1000,1001,....
} Usuario;

// Estructura para almacenar la información de prestamo de libros

typedef struct {
    int num_prestamo; // Número del préstamo
    Fecha fecha_prestamo; // Fecha en que se realizó el préstamo
    int usuario_prestamo; // código usuario al que se le realiza el prestamo
    int num_libros; // Número de libros en el préstamo
    int duracion ; // duración del pestamo
    LibroPrestamo libros[MAX_BOOKS_PER_LOAN]; // Array de libros prestados

} Prestamo;

LibroStock inventario[NUM_BOOKS] = {
        {"El Quijote", "Miguel de Cervantes", 10, 1},
        {"Cien años de soledad", "Gabriel García Márquez", 8, 2},
        {"La sombra del viento", "Carlos Ruiz Zafón", 5, 3},
        {"1984", "George Orwell", 3, 4},
        {"La Odisea", "Homero", 12, 5},
        {"Orgullo y prejuicio", "Jane Austen", 7, 6},
        {"Moby Dick", "Herman Melville", 2, 7},
        {"Hamlet", "William Shakespeare", 9, 8},
        {"El principito", "Antoine de Saint-Exupéry", 4, 9},
        {"Don Juan Tenorio", "José Zorrilla", 6, 10}

};

int cuantos(int codigo);
void imprime_inventario();

Prestamo alta_prestamo(int num_prestamo);
int lee_libros_prestamo(LibroPrestamo libros_prestamo[]);

char* dame_nombre(int codigoLibro);
void actualiza_inventario(Prestamo prestamo);
void muestra_prestamo(Prestamo prestamo);
void amplia_plazo();

 // Función que devuelve la cantidad de libros de un código determinado en el inventario.

int cuantos(int codigo) {
    // Recorre el inventario buscando el libro
    for (int i = 0; i < NUM_BOOKS; i++) {
        if (inventario[i].codigo == codigo) {
            // Si encuentra el libro, devuelve su cantidad
            return inventario[i].cantidad;
        }
    }
    // Si no encuentra el libro, devuelve -1
    return -1;
}

// Función para leer los libros que se dan de un préstamo
// Parámetros: libros_prestamo[] - array de libros del préstamo
// Retorno: int - número de libros en el préstamo

int lee_libros_prestamo(LibroPrestamo libros_prestamo[]) {
    int cod, i = 0;
    int can,max;
    printf("Introduce el listado de libros del préstamo. \nPara terminar introduce codigo 0\n");
    do {
        printf("Codigo Libro: ");
        scanf("%d", &cod);
        if (cod != 0) {
            max = cuantos(cod);
            do {
                printf("Cantidad (max:%d): ", max);
                scanf("%d", &can);
            }while (can > max);
            libros_prestamo[i].cantidad = can;
            libros_prestamo[i].codigo = cod;
            i++;
        }
    } while (cod != 0);
    return i;
}

// Función para dar de alta un préstamo
// Parámetros: num_prestamo - número del préstamo
// Retorno: Prestamo - estructura de préstamo


Prestamo alta_prestamo(int num_prestamo) {
    Prestamo prest;
    prest.num_prestamo = num_prestamo;
    // Obnetenemos la fecha del sistema
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    prest.fecha_prestamo.dia = tm.tm_mday;
    prest.fecha_prestamo.mes = tm.tm_mon + 1; // En esta estructura, los meses van de 0 (enero) a 11 (diciembre)
    prest.fecha_prestamo.anio = tm.tm_year + 1900; // Los años se cuentan desde 1900
    printf("Indica el código del usuario: ");
    scanf("%d", &prest.usuario_prestamo);
    prest.num_libros = lee_libros_prestamo(prest.libros);
    return prest;
}


 // Función: Imprime el inventario completo de libros, excluyendo los registros sin datos

void imprime_inventario() {
    int i;
    printf("\nInventario completo de libros:\n\n");
    for (i = 0; i < NUM_BOOKS; i++) {
        // Comprueba si el registro tiene datos (por ejemplo, si el título no está vacío)
        if (strlen(inventario[i].titulo) > 0) {
            printf("Título: %s, Autor: %s, Cantidad: %d, Código: %d\n", inventario[i].titulo,
                   inventario[i].autor, inventario[i].cantidad, inventario[i].codigo);
        }
    }
}


// Función: actualiza_inventario

void actualiza_inventario(Prestamo prestamo){
    int librosParaActualizar = prestamo.num_libros;

    printf("\n--- Actualizando inventario ---\n");

    for (int i = 0; i < NUM_BOOKS; i++){
        for (int j=0; j< librosParaActualizar;j++){
        if (prestamo.libros[j].codigo == inventario[i].codigo){
            inventario[i].cantidad -= prestamo.libros[j].cantidad;
        }
    }
    }
    printf("\n--- Inventario actualizado con exito ---\n");

}



char* dame_nombre(int codigoLibro){
    for (int i = 0; i < NUM_BOOKS; i++) {
        if (codigoLibro == inventario[i].codigo){
            return inventario[i].titulo;
        }
    }
    return NULL;
}

// Función para acceder a un usuario por su ID

Usuario* obtenerUsuarioPorId(int id, Usuario usuarios[]) {
    int posicion = id - 1000; // Calcula la posición en el array a partir del ID
    if (posicion >= 0 && posicion < MAX_USERS) {
        return &usuarios[posicion]; // Devuelve el usuario en la posición calculada
    } else {
        return NULL; // Devuelve NULL si el ID no es válido
    }
}


 // Función muestra_prestamo

//
//
//
//
//


 // Función amplia_plazo

//
//
//
//

int main() {

    SetConsoleOutputCP(CP_UTF8);
    // Array para almacenar los usuarios
    Usuario usuarios[MAX_USERS] = {
            {"Juan Perez", "12345678A", 1000},
            {"Maria Lopez", "87654321B",1001},
            {"Carlos Garcia", "23456789C",1002}
    };

    Prestamo prestamos[MAX_LOANS] = {
            {0, {7, 2, 2024}, 1000, 2, 30,{{1,3}, {2,1}}},
            {1, {8, 3, 2024}, 1002, 1, 30,{{3,1}}}
    };
    int num_prestamos = 2; // Ya hay dos préstamos creados
    int num_usuarios = 3; // hay tres usuarios predefinidos
    int opcion;

    do {printf("\nMenu de opciones:\n");
        printf("1. Imprimir inventario \n");
        printf("2. Dar de alta un préstamo\n");
        printf("3. Mostrar un préstamo\n");
        printf("4. Actualizar inventario\n");
        printf("5. Ampliar plazo de  un préstamo\n");
        printf("0. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                imprime_inventario();
                break;

            case 2:
                if (num_prestamos < MAX_LOANS) {
                    prestamos[num_prestamos] = alta_prestamo(num_prestamos + 1);
                    //muestra_prestamo(prestamos[num_prestamos], usuarios);
                    num_prestamos++;
                } else {
                    printf("No se pueden registrar más préstamos.\n");
                }
                break;
            case 3:
                if (num_prestamos > 0) {
                    int index;
                    printf("Introduce el índice del préstamo a mostrar (0 a %d): ", num_prestamos - 1);
                    scanf("%d", &index);
                    if (index >= 0 && index < num_prestamos) {
                        //muestra_prestamo(prestamos[index],usuarios);
                    } else {
                        printf("Índice inválido.\n");
                    }
                } else {
                    printf("No hay préstamos registrados.\n");
                }
                break;
            case 4:
                actualiza_inventario(prestamos[num_prestamos-1]);
                printf("Inventario actualizado.\n");
                break;

            case 5:
                if (num_prestamos > 0) {
                    int index;
                    printf("Introduce el índice del préstamo a ampliar (0 a %d): ", num_prestamos - 1);
                    scanf("%d", &index);
                    if (index >= 0 && index < num_prestamos) {
                        // amplia_plazo(&prestamos[index]);
                    } else {
                        printf("Índice inválido.\n");
                    }
                } else {
                    printf("No hay préstamos registrados.\n");
                }
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Intentalo de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}

