#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structs.h"

#define DELIM '@'  
#define MIN_REP 3  



char *criptografia(char *palavra, char *password) {
    int coluna = strlen(password);
    int totalChars = strlen(palavra);
    int linha = totalChars / coluna;
    if (totalChars % coluna != 0) linha++;

    char **matriz = malloc(linha * sizeof(char *));
    for (int i = 0; i < linha; i++) {
        matriz[i] = malloc(coluna * sizeof(char));
    }

    int cont = 0;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j] = (cont < totalChars) ? palavra[cont++] : '#';
        }
    }

    int *ordem = malloc(coluna * sizeof(int));
    for (int i = 0; i < coluna; i++) ordem[i] = i;

    int temp;
    for (int i = 0; i < coluna; i++) {
        for (int j = i + 1; j < coluna; j++) {
            if (password[ordem[i]] > password[ordem[j]]) {
                temp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = temp;
            }
        }
    }

    char *criptografada = malloc(linha * coluna + 1);
    cont = 0;
    for (int i = 0; i < coluna; i++) {
        int col = ordem[i];
        for (int j = 0; j < linha; j++) {
            criptografada[cont++] = matriz[j][col];
        }
    }
    criptografada[cont] = '\0';

    for (int i = 0; i < linha; i++) free(matriz[i]);
    free(matriz);
    free(ordem);

    return criptografada;
}

char *descriptografia(char *palavra_criptografada, char *password) {
    int coluna = strlen(password);
    int totalChars = strlen(palavra_criptografada);
    int linha = totalChars / coluna;
    if (totalChars % coluna != 0) linha++;

    char **matriz = malloc(linha * sizeof(char *));
    for (int i = 0; i < linha; i++) {
        matriz[i] = malloc(coluna * sizeof(char));
    }

    int *ordem = malloc(coluna * sizeof(int));
    for (int i = 0; i < coluna; i++) ordem[i] = i;

    int temp;
    for (int i = 0; i < coluna; i++) {
        for (int j = i + 1; j < coluna; j++) {
            if (password[ordem[i]] > password[ordem[j]]) {
                temp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = temp;
            }
        }
    }

    int cont = 0;
    for (int i = 0; i < coluna; i++) {
        int col = ordem[i];
        for (int j = 0; j < linha; j++) {
            matriz[j][col] = palavra_criptografada[cont++];
        }
    }

    char *palavra_original = malloc(totalChars + 1);
    cont = 0;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (matriz[i][j] != '#') {
                palavra_original[cont++] = matriz[i][j];
            }
        }
    }
    palavra_original[cont] = '\0';

    for (int i = 0; i < linha; i++) free(matriz[i]);
    free(matriz);
    free(ordem);

    return palavra_original;
}

char *orderToString(ORDER *o){
    int size = 0;

    size += snprintf(NULL, 0, 
    "%lu %s %s %d %d", o->id,o->date,o->time, o->countItems,o->excluido);

    for (int i = 0; i < o->countItems; i++){
        size += snprintf(NULL, 0, " %lu", o->items[i]);
    }

    char *buffer = malloc(size +1);

    if (!buffer) {
        printf("Não foi possivel realizar a criptografia dos dados");
        exit(0);
    };

    int offset  = 0;

    offset = snprintf(buffer, size+1,
    "%lu %s %s %d %d", o->id,o->date,o->time, o->countItems,o->excluido);

    for (int i = 0; i< o->countItems; i++){

        offset += snprintf(buffer + offset, (size +1) - offset, " %lu", o->items[i]);
    }

    return buffer;
}

char *jewelryToString(JOIA *j){
    int size = 0;

    size += snprintf(NULL, 0, 
    "%lu %lf %s %s %c %s %s %d", j->id, j->price, j->mainMetal,j->mainColor, j->productGender, j->category,j->mainGem,j->excluido);

    char *buffer = malloc(size +1);

    if (!buffer) {
        printf("Não foi possivel realizar a criptografia dos dados");
        exit(0);
    };

    snprintf(buffer, size+1,
   "%lu %lf %s %s %c %s %s %d", j->id, j->price, j->mainMetal,j->mainColor, j->productGender, j->category,j->mainGem,j->excluido);

    return buffer;
}


void securityPedidos(FILE *f, char *password, bool type){
    ORDER order;
    HEADER header;


    if(type){

        FILE *fOencW= fopen("order_encripted.dat", "wb+");
        fseek(f,0,SEEK_SET);
        fread(&header,sizeof(HEADER),1,f);
        fwrite(&header,sizeof(HEADER),1,fOencW);
    
    
        while (fread(&order, sizeof(ORDER), 1, f))
        {
            char *palavra = orderToString(&order);
            char *palavra_criptografada = criptografia(palavra, password);
            
            size_t tamanho = strlen(palavra_criptografada);
            fwrite(&tamanho, sizeof(size_t), 1, fOencW);
            fwrite(palavra_criptografada, sizeof(char), tamanho, fOencW);
            printf("%s\n", palavra_criptografada);
            free(palavra_criptografada);
            free(palavra);
        }
        fclose(fOencW);
    }

    if(!type){

        FILE *fOencR= fopen("order_encripted.dat", "rb+");
        fseek(fOencR,0,SEEK_SET);
        fread(&header, sizeof(HEADER), 1, fOencR);

        while (1) {
            size_t tamanho;
            if (fread(&tamanho, sizeof(size_t), 1, fOencR) != 1) break;

            char *palavra_criptografada = malloc(tamanho + 1);
            fread(palavra_criptografada, sizeof(char), tamanho, fOencR);
            palavra_criptografada[tamanho] = '\0';

            char *palavra_descriptografada = descriptografia(palavra_criptografada, password);
            printf("%s\n", palavra_descriptografada);

            free(palavra_criptografada);
            free(palavra_descriptografada);
        }
    fclose(fOencR);

    }

}

void securityJoias(FILE *f, char *password, bool type){
    JOIA joia;
    HEADER header;
    
    // criptografia dos dados
    if (type){
        FILE *fJencW= fopen("jewelry_encripted.dat", "wb+");
        
        
        fseek(f,0,SEEK_SET);
        fread(&header, sizeof(HEADER), 1, f);
        fwrite(&header,sizeof(HEADER),1,fJencW);
        
        while(fread(&joia,sizeof(JOIA),1,f))
        {
            char *palavra = jewelryToString(&joia);
            char *palavra_criptografada = criptografia(palavra, password);
            
            size_t tamanho = strlen(palavra_criptografada);
            fwrite(&tamanho, sizeof(size_t), 1, fJencW);
            fwrite(palavra_criptografada, sizeof(char), tamanho, fJencW);
            printf("%s\n", palavra_criptografada);
            free(palavra_criptografada);
            free(palavra);
        }

        fclose(fJencW);
    }
    
    // descriptografia dos dados
    if (!type){
        
        FILE *fJencR= fopen("jewelry_encripted.dat", "rb+");
        fseek(fJencR,0,SEEK_SET);
        fread(&header, sizeof(HEADER), 1, fJencR);

        while (1) {
            size_t tamanho;
            if (fread(&tamanho, sizeof(size_t), 1, fJencR) != 1) break;

            char *palavra_criptografada = malloc(tamanho + 1);
            fread(palavra_criptografada, sizeof(char), tamanho, fJencR);
            palavra_criptografada[tamanho] = '\0';

            char *palavra_descriptografada = descriptografia(palavra_criptografada, password);
            printf("%s\n", palavra_descriptografada);

            free(palavra_criptografada);
            free(palavra_descriptografada);
        }
    fclose(fJencR);

    }
}
