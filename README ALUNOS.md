
Relatório de Projeto



Merge and Sort






Preparada por:
     
                                                                   Breno Souza dos Reis		232246
                                                                   Bruno França				167955
        Victor Henrique Barbosa Pereira	245055
                                                                  

		















				        Campinas
					2019


Descrição do Projeto

	O problema que o grupo ficou responsável de resolver é referente ao projeto 1, Merge and Sort. Que consiste em construir um programa em linguagem C usando a biblioteca Posix Threads de modo que leia no mínimo 5 arquivos de entrada com no mínimo 1000 números inteiros e, armazene todos ordenadamente em um único arquivo de saída. Este programa deve ser testado para 2, 4, 6, 8 e 16 threads e posteriormente devem ser tiradas em relação ao desempenho do programa à medida que o número de  multithreads que o programa utiliza varia.


Solução


Variáveis : 
Arquivo -> FILE pointer compartilhado entre as threads
argc -> número de variáveis inseridas pela linha de comando
argv -> vetor de strings com os nomes das entradas inseridas pela linha de comando
contador_inteiros -> conta número total de inteiros em todos as entradas
contador_arquivos -> conta o número de arquivos
pos_vet -> posição corrente de Vet
Vet ->  Vetor que armazenará todos os inteiros dos arquivos de entrada
mutex -> semáforo usado para sincronização de leitura de arquivos


Funções

Sinc -> Função a ser executada pelas threads. Se o semáforo  mutex estiver liberado a thread irá ler o inteiro da posição corrente de Arquivo e armazenará em Vet[pos_vet], após isso pos_vet é incrementado e é dado um  up em mutex.

ContaInteiros -> Conta a quantidade de números inteiros de um determinado arquivo 

cmp -> Algoritmo de ordenação para o quicksort de Vet





Main

Cria um vetor de Threads com argv[1] posições alocadas

Enquanto Contador_arquivos < argc:
Faça: ContaInteiros(argv[Contador_arquivos)
contador_arquivos = contador_arquivos + 1

Enquanto i < argc:
Faça: 
Enquanto j  <  argv[1]:
Threads[ j ] executa Functoon
j = j+1
i = i+1

Ordene o vetor Vet
Escreve os elementos de Vet no arquivo Saida.dat



Instruções para a execução do programa

Link do Projeto: https://github.com/Lnvictor/Sistemas-Operacionais
Link do vídeo explicando o funcionamento do projeto: https://youtu.be/ZY_afeystxM

Para compilar o programa utilize:

gcc -pthread mergesort.c -o <nome do arquivo executável>

Para executar:

time ./<nome do arquivo executável> <número de threads a ser utilizado> <Arquivo1.dat> …. <ArquivoN.dat> 

Obs: Para que o programa funcione é necessário que o comando time seja utilizado no momento da execução do arquivo executável




Análise de desempenho

Para analisar o desempenho do programa consideramos a seguinte situação:


Entradas:

Como entradas utilizamos 5 arquivos com 2000 números inteiros gerados aleatoriamente, tal que são pertencentes ao conjunto:

[x  Z | 0  x 1000] 
Saída:

Como saída o programa escreveu todos os inteiros presentes nos arquivos de entrada ordenadamente no arquivo “saida.dat”.


Tempo de Execução

Threads | Users | System | Real (segundos)
--------|-------|--------|----------------
2       | 0,02  | 0,00   | 0,015
4       | 0,01  | 0,00   | 0,013
6       | 0,02  | 0,01   | 0,010
8       | 0,03  | 0,02   | 0,017
16      | 0,01  | 0,03   | 0,017

Gráfico de Tempo de Execução

![grafico](https://user-images.githubusercontent.com/47432337/69198438-6f6e3880-0b13-11ea-8c71-dd47daf09b2d.png)
