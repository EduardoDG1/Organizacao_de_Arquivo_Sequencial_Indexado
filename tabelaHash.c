#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"



int calculaHash(char *horario, int posicoesTabelaHash)
{
    int somaHorario = 0, i;
    for (i = 0; i < SIZETIME; i++)
    {
        somaHorario += horario[i]*i;
    }
    
    return somaHorario%posicoesTabelaHash;
}

ORDER pesquisaTabelaHash(char *horario, TABELAHASH tabelaHash)
{
    int pos = calculaHash(horario,tabelaHash.numeroPosicoes);
    NODOTABELAHASH *aux = tabelaHash.vetorPosicoes[pos];
    while(aux)
    {
        if(!strcmp(horario,aux->order.time) && !aux->order.excluido)
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
        int pos = calculaHash(auxOrder.time,nblocos);
        if(tabelaHash.vetorPosicoes[pos])
        {   
            NODOTABELAHASH *aux = tabelaHash.vetorPosicoes[pos];
            while(aux)
            {
                aux = aux->prox;
            }
            aux = nodo;
        }
        else
        {
            tabelaHash.vetorPosicoes[pos] = nodo;
        }
    }

    return tabelaHash;
}