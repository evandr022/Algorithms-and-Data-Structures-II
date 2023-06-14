/*arvore multiway
M = impar - max #chaves
m = M/2 - m(n) #chaves

vetor chave [M+1]
chave[0] controle de #chave
vetor pont [M+1]

#filho = #chave -1

usar ED auxiliar pilha para guardar o caminhmento
*/

#include <stdio.h>
#include <stdlib.h>

#define M 5

typedef struct no{
    int chave[M+1];
    struct no *pont[M+1];
}no;

typedef struct pilha{
    no *p;
    struct pilha *prox;
}pilha;

void inicializa_pilha(pilha **p){
    *p = NULL;
}

void push(pilha **p, no *n){
    pilha *aux = (pilha*)malloc(sizeof(pilha));
    aux->p = n;
    aux->prox = *p;
    *p = aux;
}

no *pop(pilha **p){
    pilha *aux = *p;
    no *n = aux->p;
    *p = aux->prox;
    free(aux);
    return n;
}

int pilha_vazia(pilha *p){
    if(p == NULL)
        return 1;
    return 0;
}

void inicializa_arvore(no **n){
    *n = NULL;
}

/*Inserção sempre na folha 
pode haver a necessidade de particioar um no
(split)
chaves [M+1] sobre para o pai
    -> como é uma inserção pode gerar particonamento no pai
    portanto, o algoritmo tem que ser recursivo */

void insere(no **n, int x){
    if(*n == NULL){
        *n = (no*)malloc(sizeof(no));
        (*n)->chave[0] = 1;
        (*n)->chave[1] = x;
        (*n)->pont[0] = NULL;
        (*n)->pont[1] = NULL;
        return;
    }
    int i = 1;
    while(i <= (*n)->chave[0] && x > (*n)->chave[i])
        i++;
    if(x == (*n)->chave[i])
        return;
    if((*n)->pont[i-1] == NULL){
        if((*n)->chave[0] < M){
            int j = (*n)->chave[0];
            while(j >= i){
                (*n)->chave[j+1] = (*n)->chave[j];
                j--;
            }
            (*n)->chave[i] = x;
            (*n)->chave[0]++;
            return;
        }
        else{
            no *aux = (no*)malloc(sizeof(no));
            aux->chave[0] = 0;
            aux->pont[0] = NULL;
            int j = M;
            while(j >= i){
                aux->chave[j+1-i] = (*n)->chave[j];
                aux->pont[j+1-i] = (*n)->pont[j];
                j--;
            }
            aux->chave[i] = x;
            aux->chave[0] = M;
            aux->pont[0] = (*n)->pont[M];
            (*n)->chave[0] = M;
            insere(n, aux->chave[(M/2)+1]);
            int k = (*n)->chave[0];
            while(k >= i){
                (*n)->chave[k+1] = (*n)->chave[k];
                (*n)->pont[k+1] = (*n)->pont[k];
                k--;
            }
            (*n)->chave[i] = aux->chave[M/2];
            (*n)->pont[i] = aux;
            (*n)->pont[i-1] = aux;
            return;
        }
    }
    else
        insere(&(*n)->pont[i-1], x);
}