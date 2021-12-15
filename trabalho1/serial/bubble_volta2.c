#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max = 50000;
/**
 * @brief Programa para ordenação de um vetor usando a técnica de volta 2.
 * 
 * @author André Pinheiro
 * 
 * @param argc 
 * @param argv 
 */
int main(int argc, char *argv[]){
    clock_t start, end;
    
    /**
     * @brief Gerando o vetor a ser ordenado.
     */
    int vetor[max];
    srand(42);
    for (int i =0; i < max; i++){
        vetor[i] = abs(rand()) % (max * 100);
    }
    start = clock();
   
    /**
     * @brief Algoritmo Volta 2. 
     * Este algoritmo consiste no problema de ordenação por Bubble Sort 
     * no qual, ao se encontrar um valor maior que o anterior, o algoritmo volta 
     * dois números. 
     * 
     * O algoritmo termina quando 
     * 
     */
    int tmp, loop = 0;
    do{
        loop = 0;
        for (int i = 1; i < max; i++){
            tmp = 0;
            if (vetor[i] < vetor[i-1]){
                tmp = vetor[i-1];
                vetor[i-1] = vetor[i];
                vetor[i] = tmp;
                loop++;
                i = i - 2;
            }
        }
    }while(loop > 0);

    end = clock();

    double time_2 = (double)(end - start) / (double)CLOCKS_PER_SEC;
    printf("Tempo da ordenação voltando 2 elementos: %f segundos\n",  time_2);
    return 0;
}