#include<stdio.h>
#include<stdlib.h>
#include<string.h>


///////////////////////////////////////////////////////////////
// Definicion de constantes utilizadas en el programa
///////////////////////////////////////////////////////////////
#define NLLANICOS  5  // Numero maximo de posiciones donde hay un llanico
#define MAXCAPTURAS 10  //Numero maximo de capturas para un  llanico.


/////////////////////////////////////////////////
//   Tipos definidos por el usuario
/////////////////////////////////////////////////
//Tipo enumerado que define la situacion del llanico
typedef enum {conseguido=1, buscaycaptura=2} SITUACION;

//Tipo enumerado que define la orientacion en una coordenada gps
typedef enum {norte=1, oeste=2}ORIENTACION;

//Tipo enumerado que define las diferentes tilos de llanicos
typedef enum {llanetes=1, llanote=2, llanicho=3, allanado=4}TLlanicos;

//Tipo struct que define una posicion gps 
typedef struct {
    int grado, min, seg;
    ORIENTACION orienta;
}TPosicion;

//Tipo struct que define uno de los llanicos colocados para su localizacion 
typedef struct {
    TPosicion pos;
    TLlanicos  tipo;
    int ndisponibles;
    int usucapt[MAXCAPTURAS];
} TEncaptura;


//Prototipos de todas las funciones creadas en el programa
void MuestraLlanicosUsuario(TEncaptura Servidor[NLLANICOS], SITUACION client[]);
void DarAlta(TEncaptura Servidor[NLLANICOS], int nll);
int EstaLlanico(TEncaptura Servidor[NLLANICOS], TPosicion pos);
void CapturaLlanico(TEncaptura Servidor[NLLANICOS],TPosicion pos,SITUACION client[],int njug);
void IniciaJugador(SITUACION client[]);
void PorDefecto(TEncaptura Servidor[NLLANICOS]);
void MuestraSituacion(TEncaptura Servidor[NLLANICOS]);

///////////////////////////////////////////////////////////////////////////
//
//  Funcion:  Main
//  Parametros:  --
//  Retorno: --
//  Tarea realizada: Funcion principal de nuestro programa 
//
////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    // Variable que representa los datos almacenados en el servidor con la
    //informacion de todos los llanicos a localizar durante un dia
    TEncaptura Servidor[NLLANICOS];
    // Variable que representa los datos almacenados en cada uno de los clientes
    // con la información de los llanicos capturados por ese jugador
    SITUACION Micliente[NLLANICOS];
    int  opc, nll=0;
    TPosicion pos;
    char c;
    IniciaJugador(Micliente);
    do {
      printf("1. Inicio de Juego diario.\n");
      printf("2. Inicio de Juego por defecto.\n");
      printf("3. Captura Llanico .\n");
      printf("4. Imprimir Situacion de jugador .\n");
      printf("5. Imprime Situacion del Juego.\n");
      printf("0. Salir.\n");
      scanf("%d%*c", &opc);
      switch (opc) {
         case 0: break;
         case 1: printf("Indica el numero de llanicos a dar de Alta:  ");
                 scanf("%d", &nll);
                 DarAlta(Servidor,nll);
                 break;
         case 2: PorDefecto(Servidor);
                 break;
         case 3: printf("Indica la posicion donde esta el llanico ");
                 scanf ("%d:%d:%d", &pos.grado, &pos.min, &pos.seg);
                 fflush(stdin);
                 printf (" y la orientacion: O/N ");
                 c=getchar();
                 if (c=='o' ||c=='O') pos.orienta=oeste;
                 else pos.orienta=norte;
                 CapturaLlanico(Servidor,pos,Micliente,1);
                 break;
          case 4: MuestraLlanicosUsuario(Servidor, Micliente);
                  break;
          case 5: MuestraSituacion(Servidor);
                  break;
         default: printf ("Opcion Incorrecta\n");
        }
    }while(opc!=0);
    printf("Bye, Bye. Hasta la proxima\n");
    return (EXIT_SUCCESS);
}


/////////////////////////////////////////////////////////////////
//
//  Funcion:  Aleatorio
//  Parametros: max.  Numero aleatorio maximo
//  Retorno: Numero generado
//  Tarea realizada: Devuelve un numero aleatorio comprendido entre 1 y max
//
/////////////////////////////////////////////////////////////////
int Aleatorio (int max){
    return rand()% max +1 ;
}


/////////////////////////////////////////////////////////////////
//
//  Funcion:  PorDefecto 
//  Parametros: Servidor. Vector con los datos almacenados en el servidor
//  Retorno: --
//  Tarea realizada: Inicializa el vector del servidor con 5 llanicos
//                   Funcion Auxiliar Dada
//
/////////////////////////////////////////////////////////////////
void PorDefecto(TEncaptura Servidor[NLLANICOS]){
 Servidor[0].pos.grado=360;
 Servidor[0].pos.min=58; 
 Servidor[0].pos.seg=58; 
 Servidor[0].pos.orienta=oeste;
 Servidor[0].ndisponibles=2; 
 Servidor[0].tipo=llanetes;
 Servidor[1].pos.grado=180;
 Servidor[1].pos.min=40;
 Servidor[1].pos.seg=18,
 Servidor[1].pos.orienta=norte;
 Servidor[1].ndisponibles=3; 
 Servidor[1].tipo=llanote;
 Servidor[2].pos.grado=100;
 Servidor[2].pos.min=25,
 Servidor[2].pos.seg=20,
 Servidor[2].pos.orienta=norte;
 Servidor[2].ndisponibles=4; 
 Servidor[2].tipo=llanicho;
 Servidor[3].pos.grado=50;
 Servidor[3].pos.min=48,
 Servidor[3].pos.seg=48,
 Servidor[3].pos.orienta=oeste;
 Servidor[3].ndisponibles=2; 
 Servidor[3].tipo=allanado;
 Servidor[4].pos.grado=270;
 Servidor[4].pos.min= 0;
 Servidor[4].pos.seg=0;
 Servidor[4].pos.orienta=oeste;
 Servidor[4].ndisponibles=1; 
 Servidor[4].tipo=llanetes;
 }

/////////////////////////////////////////////////////////////////
//
//  Funcion:  MuestraLlanicosUsuario 
//  Parametros: Servidor. Vector con los datos almacenados en el servidor
//              client. Vector que representa la situacion del juego de
//                      uno de los jugadores
//  Retorno: --
//  Tarea realizada: Muestra por pantalla la posicion de los Llanicos capturados
//                   por el jugador que que pasa por paramentro.  
//                   Ejercicio pedido en examen escrito
//
/////////////////////////////////////////////////////////////////1
void MuestraLlanicosUsuario( TEncaptura Servidor[NLLANICOS],SITUACION client[]) {
    {
        int i;
        for (i=0;i<NLLANICOS;i++)
            if (client[i]== conseguido)
                printf("Capturado llanico tipo %d en posición %d, %d, %d, orientación %d \n", Servidor[i].tipo, Servidor[i].pos.grado, Servidor[i].pos.min, Servidor[i].pos.seg, Servidor[i].pos.orienta);
    }
}

/////////////////////////////////////////////////////////////////
//
//  Funcion:  DarAlta  
//  Parametros: Servidor. Vector con los datos almacenados en el servidor
//              nll. Numero de llanicos que deben darse de alta 
//  Retorno: --
//  Tarea realizada: Va introduccioen en el vector del servidor los datos de
//                   los nll llanicos que hay que dar de alta en el sistema.
//                   Pide al usuario la posicion y calcula de forma aleatiroa el
//                   el tipo y el numero disponible
//                   ejercicio 1 de laboratorio
//
/////////////////////////////////////////////////////////////////

//Define esta funcion como soluciona la ejercicio 1 planteado.

void DarAlta(TEncaptura Servidor[NLLANICOS], int nll) {
    int grados,minutos,segundos,orientacion;
    if (nll > 0) {
        for (int i = 0; i < nll ; i++) {
            printf("Introduce la posicion: \n");
            do {
                printf("Grados: ");
                scanf("%d",&grados);
            }while (grados < 0 || grados > 360);

            do {
                printf("\nMinutos: ");
                scanf("%d",&minutos);
            } while (minutos < 0 || minutos > 60);

            do {
                printf("\nSegundos: \n");
                scanf("%d",&segundos);
            } while (segundos < 0 || segundos > 60);

            do {
                printf("Orientacion(Norte 1, Oeste 2): ");
                scanf("%d",&orientacion);
            }while (orientacion < 0 || orientacion > 2);

            Servidor[i].pos.grado = grados;
            Servidor[i].pos.min = minutos;
            Servidor[i].pos.seg = segundos;
            Servidor[i].pos.orienta = orientacion;
            Servidor[i].tipo = Aleatorio(4);
            Servidor[i].ndisponibles = Aleatorio(25);

        }
    }
}


/////////////////////////////////////////////////////////////////
//
//  Funcion:  EstaLlanico 
//  Parametros: Servidor. Vector con los datos almacenados en el servidor
//              pos. Elemento del tipo TPosicion que representa la posicion en la
//                   que se debe comprobar si hay un llanico o no
//  Retorno:  Devuelve el indice de la posicion en la que está almacenado el llanico.
//            y -1 si no hay ningun llanico en esa posicion
//  Tarea realizada: Comrpueba si en la posicion dada hay un llanico o no
//                   Ejercicio 2 del examen de laboratorio
//
/////////////////////////////////////////////////////////////////
int EstaLlanico(TEncaptura Servidor[NLLANICOS],TPosicion pos) {
    int indicePosicion = -1;
    if (pos.grado < 0 || pos.grado > 360||
        pos.min < 0 || pos.min > 60 ||
        pos.seg < 0 || pos.seg > 60 ||
        pos.orienta < 1 || pos.orienta > 2) {
        return -1; // posicion no valida
    }
    for (int i = 0; i < NLLANICOS ; i++) {
        // Comprobamos si coincide nuestra posicion con la del servidor
        if (Servidor[i].pos.grado == pos.grado &&
            Servidor[i].pos.min == pos.min &&
            Servidor[i].pos.seg == pos.seg &&
            Servidor[i].pos.orienta == pos.orienta){
            if (Servidor[i].ndisponibles != 0 ) { // Y además si coincide vemos si está disponible, si lo está guardamos el indice
                indicePosicion = i;
                break;
            }
        }
    }
    return indicePosicion;

}

/////////////////////////////////////////////////////////////////
//
//  Funcion:  CapturaLlanico 
//  Parametros: Servidor. Vector con los datos almacenados en el servidor
//              client. Vector que representa la situacion del juego de
//                      uno de los jugadores
//              pos. Posicionen la que se ha capturado un llanico
//  Retorno: --
//  Tarea realizada: Actualiza los datos tras la captura de un llanico.
//                   En el vector del servidor decrementa en 1 el numero de 
//                   disponibles y en el cliente pone el llanico como capturado.  
//                   Ejercicio 3 del laboratorio
//
/////////////////////////////////////////////////////////////////
void CapturaLlanico(TEncaptura Servidor[NLLANICOS],TPosicion pos,SITUACION client[],int njug) {
    if (pos.grado < 0 || pos.grado > 360||
            pos.min < 0 || pos.min > 60 ||
            pos.seg < 0 || pos.seg > 60 ||
            pos.orienta < 1 || pos.orienta > 2) {
        printf("Posicion no valida");
    }
    int indice = EstaLlanico(Servidor, pos);
    if (indice != -1) {
        Servidor[indice].ndisponibles--;  // Decrementar disponibles
        client[indice] = conseguido;      // Marcar como capturado
        for (int j = 0; j < MAXCAPTURAS; j++) {
            if (Servidor[indice].usucapt[j] == 0) {  // Si está vacío
                Servidor[indice].usucapt[j] = njug;  // Guardar el jugador
                break;
            }
        }
        printf("Capturado con exito!");
    } else printf("Error al intentar capturar");

}

/////////////////////////////////////////////////////////////////
//
//  Funcion:  MuestraSituación 
//  Parametros: Servidor. Vector con los datos almacenados en el servidor 
//  Retorno: --
//  Tarea realizada: Muestra por pantalla los datos de todos los llanicos del 
//                   sistema, posicion, tipo y ndisponibles  
//                   Ejercicio 4 de laboratorio
//
/////////////////////////////////////////////////////////////////

void MuestraSituacion(TEncaptura Servidor[NLLANICOS]) { // IA
    char tipoLlanico[20];
    char orientacion[10];

    printf("\n====== SITUACION ACTUAL DEL JUEGO ======\n\n");

    for (int i = 0; i < NLLANICOS; i++) {
        // Convertir tipo de Llanico a string
        switch(Servidor[i].tipo) {
            case llanetes:
                strcpy(tipoLlanico, "Llanetes");
                break;
            case llanote:
                strcpy(tipoLlanico, "Llanote");
                break;
            case llanicho:
                strcpy(tipoLlanico, "Llanicho");
                break;
            case allanado:
                strcpy(tipoLlanico, "Allanado");
                break;
            default:
                strcpy(tipoLlanico, "Desconocido");
        }

        // Convertir orientacion a string
        if (Servidor[i].pos.orienta == norte)
            strcpy(orientacion, "Norte");
        else
            strcpy(orientacion, "Oeste");

        // Mostrar informacion del Llanico
        printf("Posicion %d:\n", i + 1);
        printf("  Coordenadas: %d grados, %d minutos %d segundos %s\n",
               Servidor[i].pos.grado, Servidor[i].pos.min,
               Servidor[i].pos.seg, orientacion);
        printf("  Tipo de Llanico: %s\n", tipoLlanico);
        printf("  Unidades disponibles para capturar: %d\n\n", Servidor[i].ndisponibles);
    }
    printf("======================================\n\n");
}

/////////////////////////////////////////////////////////////////
//
//  Funcion:  IniciaJugador 
//  Parametros: client. Vector de situacion de uno de los jugadores
//  Retorno: --
//  Tarea realizada: Inicia el vector del jugador como que no se ha capturado ningun
//                   Llanico
//                   Funcion auxiliar proporcionada
//
/////////////////////////////////////////////////////////////////
void IniciaJugador(SITUACION client[])
{
 int i;
 for (i=0;i<NLLANICOS;i++) client[i]=buscaycaptura;
}