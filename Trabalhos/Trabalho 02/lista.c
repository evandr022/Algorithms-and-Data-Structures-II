#include "stdio.h"
#include "stdlib.h"
#include "lista.h"

TLista *criarLista(){
    TLista *lista = malloc(sizeof(TLista));
    lista->tamanho = 0;
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

TELE *criarElemento(int elemento){

    TELE *carga_nova = malloc(sizeof(TELE));
    carga_nova->carga = elemento;
    carga_nova->prox = NULL;

    return carga_nova;
}

void inserirLista(TLista *lista, TELE *carga){
    if(lista->tamanho == 0){
        lista->inicio = carga;
        lista->fim =  carga;
        
    }else{
        lista->fim->prox = carga;
        lista->fim = carga;
    }
    lista->tamanho ++;
}

void removerListaInicio(TLista *lista){
    TELE *aux = lista->inicio->prox;
    free(lista->inicio);
    lista->inicio = aux;
    lista->tamanho --;
    return;
}

int listaVazia(TLista *lista){
    return lista->tamanho == 0 ? 1 : 0;
}

void imprimirLista(TLista *lista){

    TELE *caminhador = lista->inicio;

    while(caminhador != NULL){
        printf("%d ",caminhador->carga);
        caminhador = caminhador->prox;
    }
}