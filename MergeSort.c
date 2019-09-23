#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

typedef struct info{
    char** fname;
    int numero_de_arquivos;
}info;

FILE* Arquivo;

int *Vet;
int contador_Arquivos = 2;
int pos_vetor=0;
int contador_palavras = 0;

sem_t first;
sem_t mutex;
sem_t vazio;

void ContaPalavras(char *fname){
    FILE* Arquivo;
    Arquivo = fopen(fname, "r");
    int auxiliar;

    while(fscanf(Arquivo, "%d", &auxiliar)!= EOF){
       contador_palavras++;
    }

    fclose(Arquivo);
}


int cmp(const void *x, const void *y){
    int *xa = (int*) x;
    int *ya = (int*) y;

    if(*xa == *ya)
        return 0;
    if (*xa > *ya)
        return 1;
    if (*xa < *ya)
        return -1;
}

void* functoon(){
    int contador = 0; int aux;


    while (fscanf(Arquivo, "%d", &aux) != EOF){
        sem_wait(&mutex);
        Vet[pos_vetor] = aux;
        pos_vetor++;
        contador++;
        sem_post(&mutex);
    }

}

int main(int argc, char *argv[]){
    pthread_t Threads[atoi(argv[1])];

    for (int i = 2; i < argc; i++){
        ContaPalavras(argv[i]);
    }
    printf("%d\n", contador_palavras);
    Vet = (int*) malloc (contador_palavras*sizeof(int));

    sem_init(&mutex, 0, 1);
    sem_init(&vazio, 0, 1);
    sem_init(&first, 0, 1);

    int j;
    for(int i = 2; i <  argc; i++){
        Arquivo = fopen(argv[i], "r");
        for (j = 0; j < atoi(argv[1]); j++){
            pthread_create(&Threads[j], NULL, functoon, NULL);
        }
        for(int k =0; k < j; k++){
            pthread_join(Threads[k], NULL);
        }
        fclose(Arquivo);
    }

    qsort(Vet, pos_vetor, sizeof(int), cmp);

    FILE* filename;
    filename = fopen("saida.txt", "w");

    for(int  i = 0; i < pos_vetor; i++){
        fprintf(filename, "%d ", Vet[i]);
        if ((i+1) % 5 == 0 && i != 0){
            fprintf(filename, "\n");
        }
    }

    ContaPalavras("saida.txt");
    printf("%d\n", contador_palavras);
    fclose(filename);

}
