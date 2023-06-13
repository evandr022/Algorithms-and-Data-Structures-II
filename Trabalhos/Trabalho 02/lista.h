#include "stdio.h"
#include "stdlib.h"

typedef struct carga{
    int carga;
    struct carga *prox;
}TELE;

typedef struct lista{
    int tamanho;
    TELE *inicio;
    TELE *fim;
}TLista;

TLista *criarLista();
TELE *criarElemento(int elemento);
void inserirLista(TLista *lista, TELE *carga);
void removerListaInicio(TLista *lista);
int listaVazia(TLista *lista);
void imprimirLista(TLista *lista);