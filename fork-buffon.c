#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

float pot (float base, float expoente){
    int i=1, p=1;

    while(i<=expoente){
        p=p*base;
        i++;
    }

    return p;
}

int main(int argc, const char *argv[]){
    
    FILE *arq;

    arq = fopen("DadosSimulaBuffon.txt", "wt");


    float a1, a2, Xmax, N, d, x, teta, L, n, PI, PIest, erro, Pg, incPIest, k;
    int i;

    /* atribui valor às variáveis */
    N=15;
    d=1.0; /* Definiu-se L=d=1 para facilitar */
    L=0.0;
    n=0;
    PI=3.14159265359; /* Valor verdadeiro de PI */
    i=1;

     /* Utiliza a contagem de tempo do computador como semente para srand gerar um aleatório */
    srand((unsigned) time(NULL));
while (L<=1){
    while (i<=N){

        if (fork() == 0)
        {

            PIest=(2*N)/n; /* A cada lançamento, calcula um valor estimado para PI */

            erro=PIest-PI;

            Pg=(2*L)/(d*PI);

            k=((2*n)/PI)*(1-(2/PI)); /* Variável auxiliar para calcular incPIest */

            incPIest=PIest*((pot(k, 0.5) )/((2*n)/PI));

            fprintf(arq, "%.0f %3.6f %3.6f %3.6f %3.6f\n ", n, PIest, erro, Pg, incPIest);
            
        }else{

            a1=rand()%51; /* gera um aleatório inteiro entre 0 e 50*/
            a2=rand()%101; /* gera um aleatório inteiro entre 0 e 100*/

            /* usa a1 e a2 para definir, respectivamente, x (entre 0 e (d/2)=0.5) e teta (entre 0 e PI) */
            x = (a1/100);

            teta= (a2/100)*PI;

            Xmax=(L*(sin(teta)))/2; /* calcula o valor de Xmax */

            if(x<=Xmax){
                n=n+1;
            } /* Se x é menor ou igual a Xmax, então a agulha cruzou a reta */
            
            //fprintf(arqN, "%.0f\n", N);
            //fprintf(arqteta, "%3.6f\n", teta);
            //fprintf(arqx, "%3.6f\n", x);
        }

        i=i+1;
    }  

    L=L+0.05;
}

   

}