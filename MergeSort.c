#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int Vet[500];
int contador_Arquivos = 1;
int pos_vetor=0;

typedef struct file{
    char nome[30];
}file;

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

void* functoon(void* fname){
    char* file_name = (char*) fname;
    FILE* Arquivo;
    Arquivo = fopen(file_name, "r");
    while(fscanf(Arquivo, "%d", &Vet[pos_vetor])!=EOF){
        pos_vetor++;
    }

    fclose(Arquivo);

    qsort(Vet, pos_vetor, sizeof(int), cmp);
    contador_Arquivos++;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t Threads[2];
    // file* filename;
    // pthread_create(&Threads[0], NULL, functoon, argv[contador_Arquivos]);

    while(contador_Arquivos <= argc){
        pthread_create(&Threads[0], NULL, functoon, argv[contador_Arquivos]);
        pthread_create(&Threads[1], NULL, functoon, argv[contador_Arquivos]);
        pthread_join(Threads[1], NULL);
        pthread_join(Threads[0], NULL);
    }

    // pthread_join(Threads[0], NULL);
    for(int  i = 0; i < pos_vetor; i++){
        printf("%d ", Vet[i]);
    }

}
