#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double algoritmo1(double c1,double c2);
bool algoritmo2(int s1,int s2,int s3);
double algoritmo3(double n1,double n2,double n3,double n4,double n5);
int algoritmo4(int f1);
void algoritmo5(int nfibo);
bool algoritmo6(int p1);

int main(void) {

    int s1,s2,s3,f1,nfibo,p1;
    double c1, c2, n1, n2, n3, n4, n5;

    printf("\nALGORITMO 1 -> TEOREMA DE PITAGORAS\n");
    printf("Introduce el primer cateto: ");
    scanf ("%lf",&c1);
    printf("Introduce el segundo cateto: ");
    scanf("%lf", &c2);

    printf("Hipotenusa: %.2f" , algoritmo1(c1,c2));

    printf("\n");

    printf("\nALGORITMO 2 -> ES SUMA?\n");

    printf("Introduce el primer numero: ");
    scanf ("%d",&s1);
    printf("Introduce el segundo numero: ");
    scanf("%d", &s2);
    printf("Introduce el tercer numero: ");
    scanf ("%d",&s3);

    printf("Es la suma?(1 verdadero, 0 falso): %d ", algoritmo2(s1,s2,s3));


    printf("\n");

    printf("\nALGORITMO 3 -> NOTA MEDIA EXPEDIENTE\n");

    printf("Introduce primera nota: ");
    scanf ("%lf",&n1);
    printf("Introduce segunda nota: ");
    scanf ("%lf",&n2);
    printf("Introduce tercera nota: ");
    scanf ("%lf",&n3);
    printf("Introduce cuarta nota: ");
    scanf ("%lf",&n4);
    printf("Introduce quinta nota: ");
    scanf ("%lf",&n5);

    printf("Nota expediente: %.2lf ", algoritmo3(n1,n2,n3,n4,n5));

    printf("\n");

    printf("\nALGORITMO 4 -> FACTORIAL DE UN NUMERO\n");

    printf("Ingrese un numero para factorizar: ");
    scanf("%d", &f1);
    printf("El factorial de %d es : %d ",f1, algoritmo4(f1));

    printf("\n");

    printf("\nALGORITMO 5 -> FIBONACCI \n");

    printf("Ingrese un numero para calcular la sucesion: ");
    scanf("%d", &nfibo);
    printf("La sucesion es la siguiente :  ");
    algoritmo5(nfibo);

    printf("\n");

    printf("\nALGORITMO 6 -> ES PRIM0? \n");

    do {
        printf("Ingrese un numero para calcular SI ES PRIMO: ");
        scanf("%d", &p1);
    } while (p1<=0);

    printf("El numero %d = %d (1 primo, 0 no primo)", p1, algoritmo6(p1));




    return 0;

}

double algoritmo1(double c1, double c2) {
    return sqrt((c1*c1)+(c2*c2));
}

bool algoritmo2(int s1,int s2, int s3) {
    if (s3 == s1+s2) {
        return true;
    } return false;

}

double algoritmo3(double n1,double n2,double n3,double n4,double n5){
    return (n1+n2+n3+n4+n5)/5;
}

int algoritmo4(int f1) {
    int facto= 1;
    for (int i=1; i <= f1; i++) {
        facto*=i ;
    }
    return facto;
}

void algoritmo5(int nfibo) {

    int primero = 0;
    int segundo = 1;
    printf("%d %d ", primero, segundo);
    int siguiente= 0;

    for (int i=1 ; i <= nfibo ; i++) {
        siguiente = primero + segundo;
        primero = segundo;
        segundo = siguiente;
        printf("%d ",segundo);
    }
}

bool algoritmo6(int p1) {
    if (p1 % p1 == 0 && p1 % 1 == 0) {
        return true;
    } return false;
}