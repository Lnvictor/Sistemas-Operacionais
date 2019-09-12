#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Matriz{
    int li, co, **m;
}Matriz;

Matriz* criaMatriz(int li, int co){
    Matriz* Matrix = (Matriz*) malloc (sizeof(Matriz));
    Matrix->li = li;
    Matrix->co = co;
    Matrix->m = (int**) malloc (li * sizeof(int*));

    for(int i = 0; i < li; i++){
        Matrix->m[i] = (int*) malloc (co * sizeof(int));
    }

    for(int i = 0; i < li; i++){
        for(int j = 0; j < co; j++){
            Matrix->m[i][j] = 0;
        }
    }

    return Matrix;
}

void freeMatriz(Matriz* ma){
    for (int i = 0; i < ma->li; i++){
        free(ma->m[i]);
    }

    free(ma->m);
    free(ma);
    printf("Matriz destruída com sucesso!\n");
}

void imprime(Matriz* m){
    printf("Número de Linhas: %d\n", m->li);
    printf("Número de colunas: %d\n", m->co);

    for(int i = 0; i < m->li; i++){
        for(int j = 0; j < m->co; j++){
            printf("%d ", m->m[i][j]);
        }
        printf("\n");
    }
}

Matriz* multiplica(Matriz* a, Matriz* b){
    int aux = 0, j, i;
    Matriz* Res;
    Res = criaMatriz(a->li, b->co);

    if(a->li == b->co){
        for(i = 0; i < Res->li; i++){
            for (j = 0; j < Res->co; j++){
                Res->m[i][j] = a->m[i][j]* b->m[j][i] + b->m[i][j]* a->m[j][i];
            }
        }
        return Res;
    }
    else{
        printf("Dimensões incompatíveis\n");
        exit(1);
    }
}

Matriz* criaMatrizUns(int linha, int coluna){
    //Cria matriz preenchida de uns
    Matriz* Matrix = criaMatriz(linha, coluna);

    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            Matrix->m[i][j] = 1;
        }
    }
    return Matrix;
}

void persiste(Matriz* m, char* fname){
    //Grava o registro em um arquivo
    FILE* Arquivo;
    Arquivo = fopen(fname, "w");

    fprintf(Arquivo, "%d %d\n", m->li, m->co);
    for (int i = 0; i < m->li; i++){
        for (int j = 0; j < m->co; j++){
            fprintf(Arquivo, "%d ", m->m[i][j]);
        }
        fprintf(Arquivo, "\n");
    }

    fclose(Arquivo);
}

Matriz* carrega(char* fname){
    //Lê um registro do arquivo
    Matriz* Matrix;
    FILE* Arquivo;
    Arquivo = fopen(fname, "r");

    fscanf(Arquivo, "%d %d", &Matrix->li, &Matrix->co);
    Matrix = criaMatriz(Matrix->li, Matrix->co);

    // fscanf(Arquivo,"%c");
    for(int i = 0; i < Matrix->li; i++){
        for(int j = 0; j < Matrix->co; j++){
            fscanf(Arquivo, "%d", &Matrix->m[i][j]);
        }
    }

    fclose(Arquivo);
    return Matrix;
}

int main(){
    Matriz *m = criaMatriz(4,2);
    m->m[0][0]=7;
    m->m[1][0]=m->m[2][0]=m->m[3][0]=5;
    printf("--m--\n");
    imprime(m);
    freeMatriz(m);

    Matriz *a = criaMatrizUns(3,3);
    Matriz *b = criaMatrizUns(3,3);
    a->m[0][1]=7;
    a->m[0][2]=5;
    printf("--a--\n");
    imprime(a);
    printf("--b--\n");
    imprime(b);
    freeMatriz(b);
    printf("--a*a--\n");
    imprime(multiplica(a,a));
    persiste(a,"a.txt");
    freeMatriz(a);
    printf("--a.txt--\n");
    imprime(carrega("a.txt"));
}
