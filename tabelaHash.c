#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"


int calculaHash(char *data, char *horario, int posicoesTabelaHash)
{
    int somaDataHorario = 0, i;
    for (i = 0; i < SIZEDATE; i++)
    {
        somaDataHorario += data[i]*i;
    }
    for (i = 0; i < SIZETIME; i++)
    {
        somaDataHorario += horario[i]*i;
    }
    return somaDataHorario%posicoesTabelaHash;
}

ORDER pesquisaTabelaHash(FILE *f,char *data, char *horario, TABELAHASH tabelaHash, clock_t *t)
{
    *t = clock();
    int pos = calculaHash(data,horario,tabelaHash.numeroPosicoes);
    NODOTABELAHASH *aux = tabelaHash.vetorPosicoes[pos];
    while(aux)
    {
        ORDER orderAux;
        fseek(f,aux->desloc,SEEK_SET);
        fread(&orderAux,sizeof(ORDER),1,f);
        if(!strcmp(data,orderAux.date) && !strcmp(horario,orderAux.time) && !orderAux.excluido)
        {
            *t = clock() - *t;
            return orderAux;
        }
        aux = aux->prox;
    }
    *t = clock() - *t;
    printf("Pedido nao encontrado!\n");
}

void remocaoTabelaHash(FILE *f,char *data, char *horario, TABELAHASH tabelaHash, clock_t *t)
{
    *t = clock();
    int pos = calculaHash(data,horario,tabelaHash.numeroPosicoes);
    NODOTABELAHASH *aux = tabelaHash.vetorPosicoes[pos];
    while(aux)
    {
        ORDER orderAux;
        fseek(f,aux->desloc,SEEK_SET);
        fread(&orderAux,sizeof(ORDER),1,f);
        if(!strcmp(data,orderAux.date) && !strcmp(horario,orderAux.time) && !orderAux.excluido)
        {
            orderAux.excluido = 1;
            fseek(f,-sizeof(ORDER),SEEK_CUR);
            fwrite(&orderAux,sizeof(ORDER),1,f);
            printf("Pedido removido com sucesso!\n");
            *t = clock() - *t;
            return;
        }
        aux = aux->prox;
    }
    *t = clock() - *t;
    printf("Pedido nao encontrado!\n");
}

NODOTABELAHASH *criarNodoTabelaHash(unsigned long int desloc)
{
    NODOTABELAHASH *novoNodo = (NODOTABELAHASH *)malloc(sizeof(NODOTABELAHASH));

    novoNodo->desloc = desloc;
    novoNodo->prox = NULL;

    return novoNodo;
}

TABELAHASH criarTabelaHashArquivoCompras(FILE *f, clock_t *t)
{
    *t = clock();

    fseek(f,0,SEEK_SET);

    HEADER header;
    fread(&header,sizeof(HEADER),1,f);  

    int bfrDataFile = (int)floor(BLOCKSIZE/sizeof(ORDER));
    int nblocos = (int)(ceil((float)header.numeroRegistros/bfrDataFile));

    TABELAHASH tabelaHash;

    tabelaHash.numeroPosicoes = nblocos;
    tabelaHash.vetorPosicoes = (NODOTABELAHASH **)malloc(nblocos*sizeof(NODOTABELAHASH *));

    int i;
    for (i = 0; i < nblocos; i++)
    {
        tabelaHash.vetorPosicoes[i] = NULL;
    }
    
    ORDER auxOrder;
    unsigned long int desloc = sizeof(HEADER);
    while(fread(&auxOrder,sizeof(ORDER),1,f))
    {
        NODOTABELAHASH *nodo = criarNodoTabelaHash(desloc);
        int pos = calculaHash(auxOrder.date,auxOrder.time,nblocos);
        if(tabelaHash.vetorPosicoes[pos])
        {   
            nodo->prox = tabelaHash.vetorPosicoes[pos];
            tabelaHash.vetorPosicoes[pos] = nodo;
        }
        else
        {
            tabelaHash.vetorPosicoes[pos] = nodo;
        }
        desloc += sizeof(ORDER);
    }

    *t = clock() - *t;
    return tabelaHash;
}