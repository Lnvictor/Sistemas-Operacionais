/*
*    Projeto desenvolvido para a disciplina de Sistemas Operacionais
*    Programa que resolve o problema merge and sort
*
*    Desenvolvido por:
*       Breno Souza dos Reis                RA:232246
*       Bruno César de França               RA:167955
*       Victor Henrique Barbosa Pereira     RA:245055
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <math.h>

//Arquivo a ser compartilhado entre as threads
FILE *Arquivo;

//Variáveis compartilhadas
int *Vet; //Armazena os inteiros
int contador_Arquivos = 3;

int pos_vetor = 0; //Posição corrente do vetor
int contador_inteiros = 0;

//Declaração de semáforos
sem_t mutex;

//Conta Quantidade de números de um determinado arquivo
void ContaInteiros(char *fname)
{
    FILE *Arquivo;
    Arquivo = fopen(fname, "r");
    int auxiliar;

    while (fscanf(Arquivo, "%d", &auxiliar) != EOF)
    {
        contador_inteiros++;
    }

    fclose(Arquivo);
}

//Algoritmo de ordenação para o quickSort
int cmp(const void *x, const void *y)
{
    int *xa = (int *)x;
    int *ya = (int *)y;

    if (*xa == *ya)
        return 0;
    if (*xa > *ya)
        return 1;
    if (*xa < *ya)
        return -1;
}

//Função a ser executada pelas threads
void *sinc()
{
    int aux;

    while (fscanf(Arquivo, "%d", &aux) != EOF)
    {
        sem_wait(&mutex);
        Vet[pos_vetor] = aux;
        pos_vetor++;
        sem_post(&mutex);
    }
}

int main(int argc, char *argv[])
{
    pthread_t Threads[atoi(argv[1])]; // interpretando números como string

    //Contando quantidade de números de todos os arquivos
    for (int i = 2; i < argc; i++)
    {
        ContaInteiros(argv[i]);
    }

    Vet = (int *)malloc(contador_inteiros * sizeof(int));

    sem_init(&mutex, 0, 1);

    int j;
    for (int i = 3; i < argc; i++)
    {
        Arquivo = fopen(argv[i], "r");
        for (j = 0; j < atoi(argv[1]); j++)
        {
            pthread_create(&Threads[j], NULL, sinc, NULL);
        }
        for (int k = 0; k < j; k++)
        {
            pthread_join(Threads[k], NULL);
        }
        fclose(Arquivo);
    }

    //Ordenação do vetor
    qsort(Vet, pos_vetor, sizeof(int), cmp);

    FILE *filename;
    filename = fopen("saida.dat", "w");

    for (int i = 0; i < pos_vetor; i++)
    {
        fprintf(filename, "%d ", Vet[i]);
        if ((i + 1) % 5 == 0 && i % 10 != 0)
        {
            fprintf(filename, "\n");
        }
    }

    fclose(filename);
}
