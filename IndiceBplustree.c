#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"

BPLUSNODO* criaNodo(bool folha, unsigned long int sizeRegistro)
{
    BPLUSNODO *novo;

    novo = (BPLUSNODO*)malloc(sizeof(BPLUSNODO));

    novo->numeroValores = 0;
    novo->maxChaves = (int)floor(BLOCKSIZE/sizeRegistro);
    novo->chaves = (unsigned long int *)malloc((novo->maxChaves)*sizeof(unsigned long int));
    novo->desloc = (unsigned long int *)malloc((novo->maxChaves)*sizeof(unsigned long int));
    novo->filhos = (BPLUSNODO **)malloc((novo->maxChaves+1)*sizeof(BPLUSNODO*));
    novo->pai = NULL;
    novo->prox = NULL;
    novo->folha = folha;

    return novo;
} 

BPLUSNODO *voltarParaRaiz(BPLUSNODO *atual)
{
    while(atual->pai)
    {
        atual = atual->pai;
    }
    return atual;
}

BPLUSNODO *splitIntermediario(BPLUSNODO *atual, unsigned long int chave, unsigned long int sizeRegistro)
{
    BPLUSNODO *lado = criaNodo(atual->folha, sizeRegistro);
    int posMeio = atual->numeroValores/2, i, contDim = 1, indFilhosLado = 0;
    unsigned long int vMeio = atual->chaves[posMeio];
    
    for (i = posMeio+1; i < atual->numeroValores; i++)
    {
        lado->chaves[lado->numeroValores] = atual->chaves[i];
        lado->filhos[lado->numeroValores++] = atual->filhos[i];     
        atual->filhos[i] = NULL;
        contDim++;
    }
    lado->chaves[lado->numeroValores] = chave;
    lado->filhos[lado->numeroValores++] = atual->filhos[atual->numeroValores];    

    atual->filhos[atual->numeroValores] = NULL;   
    atual->numeroValores -= contDim;

    if(!atual->pai)
    {
        BPLUSNODO *pai = criaNodo(false, sizeRegistro);
        pai->chaves[pai->numeroValores] = vMeio;
        pai->filhos[pai->numeroValores++] = atual;
        pai->filhos[pai->numeroValores] = lado;
        atual->pai = pai;
        lado->pai = pai;
    }
    else
    {
        if(atual->pai->numeroValores == atual->maxChaves)
        {
            atual->pai = splitIntermediario(atual->pai, vMeio, sizeRegistro);
        }
        else
        {
            i = atual->pai->numeroValores-1;
            while(i >= 0 && vMeio < atual->pai->chaves[i])
            {
                atual->pai->chaves[i+1] = atual->pai->chaves[i];
                i--;
            }
            atual->pai->chaves[i+1] = vMeio;
            atual->pai->numeroValores++;
        }
        atual->pai->filhos[atual->pai->numeroValores] = lado;
        lado->pai = atual->pai;  
    }
    return lado;
}

BPLUSNODO *splitNodoFolha(BPLUSNODO *atual,unsigned long int chave,unsigned long int desloc, unsigned long int sizeRegistro)
{
    BPLUSNODO *lado = criaNodo(atual->folha,sizeRegistro);
    int posMeio = atual->numeroValores/2, i, contDim = 0, indFilhosLado = 0;
    unsigned long int vMeio = atual->chaves[posMeio];

    for (i = posMeio; i < atual->numeroValores; i++)
    {
        lado->chaves[lado->numeroValores] = atual->chaves[i]; 
        lado->desloc[lado->numeroValores++] = atual->desloc[i];      
        contDim++;
    }

    lado->chaves[lado->numeroValores] = chave;
    lado->desloc[lado->numeroValores++] = desloc;

    atual->numeroValores -= contDim;

    if(!atual->pai)
    {
        BPLUSNODO *pai = criaNodo(false,sizeRegistro);
        pai->chaves[pai->numeroValores] = vMeio;
        pai->filhos[pai->numeroValores++] = atual;
        pai->filhos[pai->numeroValores] = lado;
        atual->pai = pai;
        lado->pai = pai;
    }
    else
    {
        if(atual->pai->numeroValores == atual->maxChaves)
        {
            atual->pai = splitIntermediario(atual->pai, vMeio, sizeRegistro);         
        }
        else
        {
            i = atual->pai->numeroValores-1;
            while(i >= 0 && vMeio < atual->pai->chaves[i])
            {
                atual->pai->chaves[i+1] = atual->pai->chaves[i];
                i--;
            }
            atual->pai->chaves[i+1] = vMeio;
            atual->pai->numeroValores++;
        }        
        atual->pai->filhos[atual->pai->numeroValores] = lado;
        lado->pai = atual->pai;     
    }
    atual->prox = lado;
    
    return atual;
}

BPLUSNODO *inserirValor(BPLUSNODO *atual, unsigned long int chave, unsigned long int desloc, unsigned long int sizeRegistro)
{
    if(!atual)
    {
        atual = criaNodo(true,sizeRegistro);
        atual->chaves[atual->numeroValores] = chave;
        atual->desloc[atual->numeroValores++] = desloc;
    }
    else
    {
        if(atual->folha)
        {
            if(atual->numeroValores == atual->maxChaves)
            {
                atual = splitNodoFolha(atual, chave, desloc, sizeRegistro);
            }
            else
            {
                atual->chaves[atual->numeroValores] = chave;
                atual->desloc[atual->numeroValores++] = desloc;
            }
        }
        else
        {
            int i = atual->numeroValores-1;
            while(i>=0 && chave < atual->chaves[i])
            {
                i--;
            }
            inserirValor(atual->filhos[i+1], chave, desloc, sizeRegistro); 
        }
    }
    return atual;
}

//Remover?
void imprimirFolhas(BPLUSNODO *raiz)
{
    if(raiz->folha)
    {
        int cont = 1, i;
        while(raiz)
        {
            for (i = 0; i < raiz->numeroValores; i++)
            {
                printf("%d - %lu - %lu\n",cont++, raiz->chaves[i], raiz->desloc[i]);
            }
            raiz = raiz->prox;
        }
    }
    else
    {
        imprimirFolhas(raiz->filhos[0]);        
    }
}

BPLUSNODO* criarIndiceEmMemoriaArquivoJoias(FILE *f)
{
    BPLUSNODO *raiz = NULL;

    unsigned long int desloc = sizeof(HEADER);
    JOIA joiaAux;
    
    fseek(f,desloc,SEEK_SET);

    while(fread(&joiaAux,sizeof(JOIA),1,f))
    {
        raiz = inserirValor(raiz, joiaAux.id, desloc,sizeof(JOIA));
        desloc += sizeof(JOIA);
        raiz = voltarParaRaiz(raiz);
    }
    return raiz;
}

JOIA pesquisaComIndiceEmMemoria(BPLUSNODO *raiz,FILE *f, unsigned long int chave)
{
    int i;
    if(raiz->folha)
    {
        unsigned long int deslocAux;
        for (i = 0; i < raiz->numeroValores; i++)
        {
            if(raiz->chaves[i] == chave)
            {
                fseek(f,raiz->desloc[i],SEEK_SET);
                JOIA joia;
                fread(&joia,sizeof(JOIA),1,f);
                if(!joia.excluido)
                {
                    return joia;
                }
                return;
            }
        }
    }
    else
    {
        for (i = 0; i < raiz->numeroValores; i++)
        {
            if(raiz->chaves[i] > chave)
            {
                JOIA joia;
                joia.id = 0;
                joia = pesquisaComIndiceEmMemoria(raiz->filhos[i],f,chave);
                if(joia.id != 0)
                {
                    return joia;
                }
                return;
            }
        }
        JOIA joia;
        joia.id = 0;
        joia = pesquisaComIndiceEmMemoria(raiz->filhos[i],f,chave);
        if(joia.id != 0)
        {
            return joia;
        }
        return;
    }   

}
