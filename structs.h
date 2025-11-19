#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

#define SIZECATEGORYANDGEM 20
#define SIZECOLOR 15
#define SIZEMETAL 8

#define SIZEDATE 11
#define SIZETIME 9
#define MAXITENSORDER 26

#define BLOCKSIZE 4096

typedef struct
{
    int numeroRegistros;
    int numeroInsercoes;
    int numeroExclusoes;
    unsigned long int deslocUltimoBloco;
}HEADER;

typedef struct
{
    unsigned long int id;
    double price;
    char mainMetal[SIZEMETAL];
    char mainColor[SIZECOLOR];
    char productGender;
    char category[SIZECATEGORYANDGEM];
    char mainGem[SIZECATEGORYANDGEM];
    bool excluido;
}JOIA;
typedef struct
{
    unsigned long int items[MAXITENSORDER];
    unsigned long int id;
    char date[SIZEDATE];
    char time[SIZETIME];
    int countItems;
    bool excluido;
}ORDER;

typedef struct
{
    unsigned long int ultimoDoBloco;
    unsigned long int deslocamento;
    int numeroRegistrosNoBloco;
}INDICE;

typedef struct bplusnodo
{
    int numeroValores;
    int maxChaves;
    unsigned long int *chaves;
    unsigned long int *desloc;
    struct bplusnodo **filhos;
    struct bplusnodo *prox;
    struct bplusnodo *pai;
    bool folha;
}BPLUSNODO;

typedef struct nodoTabelaHash
{
    ORDER order;
    struct nodoTabelaHash *prox;
}NODOTABELAHASH;

typedef struct 
{
    int numeroPosicoes;
    NODOTABELAHASH **vetorPosicoes;
}TABELAHASH;


#endif