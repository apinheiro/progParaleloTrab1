#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprime_vetor(vetor v);
void bubble_sort_volta_2(vetor v);
void bubble_sort_volta_metade(struct vetor v);
void bubble_sort_tradicional(struct vetor v);
vetor gerar_aleatorio(int seed);

int max = 10;

typedef struct vetor{
    int items[10];
    int qtde;
} vetor;

int main(int argc, char *argv[]){
    clock_t start, end_2, end_metade, end_tradicional; 
    vetor vet = gerar_aleatorio(42);

    imprime_vetor(vet);
    start = clock();
    bubble_sort_volta_2(vet);
    end_2 = clock(); 

    vet = gerar_aleatorio(42);

    end_metade = clock();
    bubble_sort_tradicional(vet);
    end_tradicional = clock();

    double time_2 = (double)(end_2 - start) / (double)CLOCKS_PER_SEC;
    //double time_metade = (double)(end_metade - end_2) / (double)CLOCKS_PER_SEC;
    double time_trad = (double)(end_tradicional - end_metade) / (double)CLOCKS_PER_SEC;
    printf("Tempo da ordenação voltando 2 elementos: %f segundos\n",  time_2);
    //printf("Tempo da ordenação voltando metade: %f segundos\n",  time_metade);
    printf("Tempo da ordenação no modo tradicional:  %f segundos\n",  time_trad);
}

void bubble_sort_volta_2(vetor v){
    int tmp, loop = 0;
    do{
        loop = 0;
        for (int i = 1; i < v.qtde; i++){
            tmp = 0;
            if (v.items[i] < v.items[i-1]){
                tmp = v.items[i-1];
                v.items[i-1] = v.items[i];
                v.items[i] = tmp;
                loop++;
                i = i - 2;
            }
        }
    }while(loop > 0);
}

void bubble_sort_volta_metade(struct vetor v){
    int tmp, loop = 0;
    do{
        loop = 0;
        for (int i = 1; i < v.qtde; i++){
            tmp = 0;
            if (v.items[i] < v.items[i-1]){
                tmp = v.items[i-1];
                v.items[i-1] = v.items[i];
                v.items[i] = tmp;
                loop++;
                i = i / 2;
            }
        }
    }while(loop > 0);
}

void bubble_sort_tradicional(struct vetor v){
    int tmp, loop = 0;
    loop = 0;
    for(int j = v.qtde; j > 0; j--){
        for (int i = 1; i < j; i++){
            tmp = 0;
            if (v.items[i] < v.items[i-1]){
                tmp = v.items[i-1];
                v.items[i-1] = v.items[i];
                v.items[i] = tmp;
                loop++;
            }    
        }
    }
}


void imprime_vetor(vetor v){
    printf("Imprimindo o vetor: ");
    for (int i = 0; i < v.qtde;i++){
       printf("%d, ", v.items[i]);
    }
    printf("\n");
}

vetor gerar_aleatorio(int seed){
    vetor saida;
    saida.qtde = sizeof(saida.items);

    if (seed) seed = 42;

    srand(seed);
    for (int i =0; i < saida.qtde; i++){
        saida.items[i] = abs(rand()) % (max * 10);
    }
    return saida;
}