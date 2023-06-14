// implemente um funcao que le um CSV("Precos.csv") e insere em uma arvore ("arvoreMultiway.h") em c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreMultiway.h"

int main(){
    FILE *arq;
    char linha[100];
    char *result;
    int i = 0;

    arq = fopen("Precos.csv", "r");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo");
    else{
        while(!feof(arq)){
            result = fgets(linha, 100, arq);
            if(result){
                printf("%s", linha);
            }
        }
    }
    fclose(arq);
    return 0;
}