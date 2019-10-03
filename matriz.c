#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 2000

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

void calculaMatriz(int, int, int);
void imprimeMatriz(int, int, int);

int main() {

    int tam;

    int filho1, filho2;
    int status = 0;

    scanf("%d", &tam);

    // Preenche a primeira tabela
    for(int i = 0; i < tam; i++ ) {
        for(int j = 0; j < tam; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Preenche a segunda tabela
    for(int i = 0; i < tam; i++ ) {
        for(int j = 0; j < tam; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Processos filhos calculam o produto das matrizes
    if(!(filho1 = fork())) {
        //Filho1
        calculaMatriz(tam, 0, tam/2);
        imprimeMatriz(tam, 0, tam/2);

        if(!(filho2 = fork())) {
            //Filho2
            calculaMatriz(tam, tam/2, tam);
            imprimeMatriz(tam, tam/2, tam);
        } else {
            waitpid(filho2,&status,0);
            exit(0);
        }
    } else {
        waitpid(filho1,&status,0);
        exit(0);
    }
     // calculaMatriz(tam, 0, tam/2);
     // calculaMatriz(tam, tam/2, tam);

    /*
    // Printa o resultado
        for(int i = 0; i < tam; i++) {
            for(int j = 0; j < tam; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    */

    return 0;
}

void calculaMatriz(int tamanho, int inicio, int fim) {
    // Multiplica matrizes
    for(int i = inicio; i < fim; i++) {
        for(int j = 0; j < tamanho; j++) {
            for(int k = 0; k < tamanho; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    usleep(3);
}

void imprimeMatriz(int tamanho, int inicio, int fim) {
    for(int i = inicio; i < fim; i++) {
        for(int j = 0; j < tamanho; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}