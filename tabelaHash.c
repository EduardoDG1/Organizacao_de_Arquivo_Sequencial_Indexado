#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

ORDER pesquisaTabelaHash(char *data, char *horario, TABELAHASH tabelaHash)
{
    int pos = calculaHash(data,horario,tabelaHash.numeroPosicoes);
    NODOTABELAHASH *aux = tabelaHash.vetorPosicoes[pos];
    while(aux)
    {
        if(!strcmp(data,aux->order.date) && !strcmp(horario,aux->order.time) && !aux->order.excluido)
        {
            return aux->order;
        }
        aux = aux->prox;
    }
    printf("Pedido nao encontrado!\n");
}

NODOTABELAHASH *criarNodoTabelaHash(ORDER order)
{
    NODOTABELAHASH *novoNodo = (NODOTABELAHASH *)malloc(sizeof(NODOTABELAHASH));

    novoNodo->order = order;
    novoNodo->prox = NULL;

    return novoNodo;
}

TABELAHASH criarTabelaHashArquivoCompras(FILE *f)
{
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
    while(fread(&auxOrder,sizeof(ORDER),1,f))
    {
        NODOTABELAHASH *nodo = criarNodoTabelaHash(auxOrder);
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
    }

    return tabelaHash;
}