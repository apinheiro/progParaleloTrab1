#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"


int max = 10000;
/**
 * @brief Programa para ordenação de um vetor usando a técnica de volta 2.
 * 
 * @author André Pinheiro
 * 
 * @param argc 
 * @param argv 
 */


int main(int argc, char *argv[]){
    int numprocs, myid;
    
    /**
     * @brief Gerando o vetor a ser ordenado.
     */
    int vetor[max];
    
    MPI_Init(&argc, &argv);
    double inicio = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (myid == 0){
        srand(42);
        for (int i =0; i < max; i++){
            vetor[i] = abs(rand()) % (max * 10);
        }
    }
    int batch = max / numprocs;
    int tmp, mychange, changes = 0;
    //for (int k = 0; k <= (int)sqrt(max); k++){
    do{
        int retorno[max];
        changes = 0;
        if(myid == 0){
            for (int i = 1; i < numprocs; i++){
                MPI_Send(&vetor,max,MPI_INT, i, 10, MPI_COMM_WORLD);
            }
        }else{
            MPI_Recv(&vetor, max, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_SUCCESS);
        }

        for(int j = 1; j < batch; j++){
            tmp = 0;
            if (vetor[myid * batch + j] < vetor[myid * batch + j-1]){
                tmp = vetor[myid * batch + j-1];
                vetor[myid * batch + j-1] = vetor[myid * batch + j];
                vetor[myid * batch + j] = tmp;
                j -= 2;
                if (j < 0) j =0;
            }    
        }

        if (myid == 0){
            for(int i = 1; i < numprocs; i++){
                MPI_Recv(&retorno, max, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_SUCCESS);
                for(int j = 0; j < batch; j++){
                    vetor[i * batch + j] = retorno[i * batch + j];
                }
            }
            for (int i = 1; i < numprocs; i++){
                MPI_Send(&vetor, max, MPI_INT, i, 5, MPI_COMM_WORLD);
            }
        }
        else
        {
            MPI_Send(&vetor,max,MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Recv(&vetor, max, MPI_INT, 0, 5, MPI_COMM_WORLD, MPI_SUCCESS);
        }
        
        if (myid != 0){
            int q = batch * myid - (batch / 2);
            for (int i = 1; i < batch; i++){
                tmp = 0; 
                if (vetor[q + i ] < vetor[q + i -1]){
                    tmp = vetor[q + i -1];
                    vetor[q + i-1] = vetor[q + i];
                    vetor[q + i] = tmp;
                    i -= 2;
                    if (i < 0) i =0;
                }    
            }
            MPI_Send(&vetor, max, MPI_INT, 0, 20, MPI_COMM_WORLD);
            mychange = 0;
            for (int i = 0; i < batch; i++){
                if (vetor[batch * myid + i] < vetor[batch * myid + i - 1]){
                    mychange = 1; 
                    break;
                }
            }
            MPI_Send(&mychange, 1, MPI_INT, 0, 30, MPI_COMM_WORLD);
            MPI_Recv(&changes, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_SUCCESS);
        }else{
            for (int i = 1; i < numprocs; i++){
                MPI_Recv(&retorno, max, MPI_INT, i, 20, MPI_COMM_WORLD, MPI_SUCCESS);
                for(int j=0; j < batch; j++){
                    int a = (-1 * batch)/2 + j;
                    vetor[i * batch + a] = retorno[i * batch + a];
                }
            }

            changes = 0;
            for (int i = 1; i < batch -1; i++){
                if (vetor[i] < vetor[i - 1]){
                    changes = 1;
                    break;
                }
            }
            for (int i = 1; i < numprocs; i++){
                int a = 0;
                MPI_Recv(&a, 1, MPI_INT, i, 30, MPI_COMM_WORLD, MPI_SUCCESS);
                changes += a;
            }

            // for (int i = 0; i < max; i++)
            //   printf("%d, ", vetor[i]);
            // printf("\n");
            
            for (int i = 1; i < numprocs; i++){
               MPI_Send(&changes, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
            }
        }
        
    //}
    }while(changes > 0);

    double fim= MPI_Wtime();


    if (myid == 0){
        double time_2 = fim - inicio;
        printf("Tempo da ordenação modo tradicional: %f segundos\n",  time_2);
    }
    printf("Processo %d finalizado\n", myid);
    MPI_Finalize();
    return 0;
}