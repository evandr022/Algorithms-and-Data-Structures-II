//implemente uma arvore B que guarde string em c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct no{
    int n;
    char *chave[MAX+1];
    struct no *filho[MAX+1];
    int folha;
}no;

no *raiz = NULL;

void inserir(no *raiz, char *chave, no *filho){
    int i = raiz->n;
    while(i > 0 && strcmp(chave, raiz->chave[i-1]) < 0){
        raiz->chave[i] = raiz->chave[i-1];
        raiz->filho[i+1] = raiz->filho[i];
        i--;
    }
    raiz->chave[i] = chave;
    raiz->filho[i+1] = filho;
    raiz->n++;
}

void dividir(no *raiz, int i, no *filho){
    no *novo = (no*)malloc(sizeof(no));
    novo->folha = filho->folha;
    novo->n = MAX/2;
    int j;
    for(j = 0; j < MAX/2; j++){
        novo->chave[j] = filho->chave[j+MAX/2+1];
    }
    if(!filho->folha){
        for(j = 0; j < MAX/2+1; j++){
            novo->filho[j] = filho->filho[j+MAX/2+1];
        }
    }
    filho->n = MAX/2;
    inserir(raiz, filho->chave[MAX/2], novo);
}

void inserir_nao_cheio(no *raiz, char *chave){
    int i = raiz->n;
    if(raiz->folha){
        while(i > 0 && strcmp(chave, raiz->chave[i-1]) < 0){
            raiz->chave[i] = raiz->chave[i-1];
            i--;
        }
        raiz->chave[i] = chave;
        raiz->n++;
    }else{
        while(i > 0 && strcmp(chave, raiz->chave[i-1]) < 0){
            i--;
        }
        i++;
        if(raiz->filho[i-1]->n == MAX){
            dividir(raiz, i-1, raiz->filho[i-1]);
            if(strcmp(chave, raiz->chave[i-1]) > 0){
                i++;
            }
        }
        inserir_nao_cheio(raiz->filho[i-1], chave);
    }
}

void inserir_arvore(char *chave){
    if(raiz == NULL){
        raiz = (no*)malloc(sizeof(no));
        raiz->n = 0;
        raiz->folha = 1;
    }
    if(raiz->n == MAX){
        no *novo = (no*)malloc(sizeof(no));
        novo->folha = 0;
        novo->n = 0;
        novo->filho[0] = raiz;
        dividir(novo, 0, raiz);
        raiz = novo;
        inserir_nao_cheio(raiz, chave);
    }else{
        inserir_nao_cheio(raiz, chave);
    }
}

void imprimir(no *raiz){
    int i;
    for(i = 0; i < raiz->n; i++){
        if(!raiz->folha){
            imprimir(raiz->filho[i]);
        }
        printf("%s ", raiz->chave[i]);
    }
    if(!raiz->folha){
        imprimir(raiz->filho[i]);
    }
}

void remove(no *raiz, char *chave){
    int i = 0;
    while(i < raiz->n && strcmp(chave, raiz->chave[i]) > 0){
        i++;
    }
    if(i < raiz->n && strcmp(chave, raiz->chave[i]) == 0){
        if(raiz->folha){
            int j;
            for(j = i; j < raiz->n-1; j++){
                raiz->chave[j] = raiz->chave[j+1];
            }
            raiz->n--;
        }else{
            no *aux = raiz->filho[i];
            if(aux->n >= MAX/2+1){
                while(!aux->folha){
                    aux = aux->filho[aux->n];
                }
                raiz->chave[i] = aux->chave[aux->n-1];
                remove(aux, aux->chave[aux->n-1]);
            }else{
                no *aux2 = raiz->filho[i+1];
                if(aux2->n >= MAX/2+1){
                    while(!aux2->folha){
                        aux2 = aux2->filho[0];
                    }
                    raiz->chave[i] = aux2->chave[0];
                    remove(aux2, aux2->chave[0]);
                }else{
                    int j;
                    aux->chave[MAX/2] = raiz->chave[i];
                    for(j = 0; j < aux2->n; j++){
                        aux->chave[MAX/2+1+j] = aux2->chave[j];
                    }
                    for(j = 0; j < aux2->n+1; j++){
                        aux->filho[MAX/2+1+j] = aux2->filho[j];
                    }
                    aux->n = MAX;
                    int k;
                    for(k = i; k < raiz->n-1; k++){
                        raiz->chave[k] = raiz->chave[k+1];
                        raiz->filho[k+1] = raiz->filho[k+2];
                    }
                    raiz->n--;
                    remove(aux, chave);
                }
            }
        }
    }else{
        if(raiz->folha){
            printf("Chave nao encontrada");
        }else{
            no *aux = raiz->filho[i];
            if(aux->n == MAX/2){
                if(i > 0){
                    no *aux2 = raiz->filho[i-1];
                    if(aux2->n >= MAX/2+1){
                        int j;
                        for(j = aux->n; j > 0; j--){
                            aux->chave[j] = aux->chave[j-1];
                        }
                        aux->chave[0] = raiz->chave[i-1];
                        if(!aux->folha){
                            for(j = aux->n+1; j > 0; j--){
                                aux->filho[j] = aux->filho[j-1];
                            }
                            aux->filho[0] = aux2->filho[aux2->n];
                        }
                        aux->n++;
                        raiz->chave[i-1] = aux2->chave[aux2->n-1];
                        aux2->n--;
                        remove(aux, chave);
                    }else{
                        int j;
                        for(j = 0; j < aux->n; j++){
                            aux2->chave[MAX/2+1+j] = aux->chave[j];
                        }
                        aux2->chave[MAX/2] = raiz->chave[i-1];
                        for(j = 0; j < aux->n+1; j++){
                            aux2->filho[MAX/2+1+j] = aux->filho[j];
                        }
                        aux2->n = MAX;
                        int k;
                        for(k = i-1; k < raiz->n-1; k++){
                            raiz->chave[k] = raiz->chave[k+1];
                            raiz->filho[k+1] = raiz->filho[k+2];
                        }
                        raiz->n--;
                        remove(aux2, chave);
                    }
                }else{
                    no *aux2 = raiz->filho[i+1];
                    if(aux2->n >= MAX/2+1){
                        aux->chave[aux->n] = raiz->chave[i];
                        if(!aux->folha){
                            aux->filho[aux->n+1] = aux2->filho[0];
                        }
                        aux->n++;
                        raiz->chave[i] = aux2->chave[0];
                        int j;
                        for(j = 0; j < aux2->n-1; j++){
                            aux2->chave[j] = aux2->chave[j+1];
                        }
                        if(!aux2->folha){
                            for(j = 0; j < aux2->n; j++){
                                aux2->filho[j] = aux2->filho[j+1];
                            }
                        }
                        aux2->n--;
                        remove(aux, chave);
                    }else{
                        int j;
                        for(j = 0; j < aux2->n; j++){
                            aux->chave[MAX/2+1+j] = aux2->chave[j];
                        }
                        aux->chave[MAX/2] = raiz->chave[i];
                        for(j = 0; j < aux2->n+1; j++){
                            aux->filho[MAX/2+1+j] = aux2->filho[j];
                        }
                        aux->n = MAX;
                        int k;
                        for(k = i; k < raiz->n-1; k++){
                            raiz->chave[k] = raiz->chave[k+1];
                            raiz->filho[k+1] = raiz->filho[k+2];
                        }
                        raiz->n--;
                        remove(aux, chave);
                    }
                }
            }else{
                remove(aux, chave);
            }
        }
    }
}



int main(){
    inserir_arvore("a");
    inserir_arvore("b");
    inserir_arvore("c");
    inserir_arvore("d");
    inserir_arvore("e");
    inserir_arvore("f");
    inserir_arvore("g");
    inserir_arvore("h");
    inserir_arvore("i");
    inserir_arvore("j");
    inserir_arvore("k");
    inserir_arvore("l");
    inserir_arvore("m");
    inserir_arvore("n");
    inserir_arvore("o");
    inserir_arvore("p");
    inserir_arvore("q");
    inserir_arvore("r");
    inserir_arvore("s");
    inserir_arvore("t");
    inserir_arvore("u");
    inserir_arvore("v");
    inserir_arvore("w");
    inserir_arvore("x");
    inserir_arvore("y");
    inserir_arvore("z");
    imprimir(raiz);
    return 0;
}
