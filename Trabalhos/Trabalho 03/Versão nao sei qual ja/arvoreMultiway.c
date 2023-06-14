#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3 

typedef struct no {
    int num_chaves; 
    int chaves[M-1]; 
    struct no *filho[M]; 
    struct no *pai;
    void *dados;
} No;

typedef struct Produto{
    char nome[50];
} Produto;

No *criaNo(){
    No *no = (No*) malloc(sizeof(No));
    no->num_chaves = 0;
    no->pai = NULL;
    for(int i = 0; i < M-1; i++)
        no->chaves[i] = -1;
    for(int i = 0; i < M; i++)
        no->filho[i] = NULL;
    return no;
}

No* buscaFolha(No *no, int valor) {
    if (no->filho[0] == NULL) {
        return no;
    }
    int i;
    for (i = 0; i < no->num_chaves && valor > no->chaves[i]; i++);
    return buscaFolha(no->filho[i], valor);
}

int temEspaco(No *no){
    return no->num_chaves < M-1;
}

int buscaPosicao(No *no, int valor){
    int i = 0;
    while(i < no->num_chaves && valor > no->chaves[i])
        i++;
    return i;
}

No* insereChaveOrdenada(No *no, int valor, void *dados){
    int pos = buscaPosicao(no, valor);
    if (pos < no->num_chaves && no->chaves[pos] == valor) {
        // chave já existe no nó, não faz nada
        return no;
    }
    if (!temEspaco(no)) {
        // nó está cheio, precisa ser dividido
        return NULL;
    }
    for(int i = no->num_chaves; i > pos; i--){
        no->chaves[i] = no->chaves[i-1];
    }
    no->chaves[pos] = valor;
    no->num_chaves++;
    no->dados = dados; 
    return no;
}

void copiaChaves(No *no, No *novoNo, int inicio, int fim){
    int j = 0;
    for(int i = inicio; i <= fim; i++){
        novoNo->chaves[j] = no->chaves[i];
        novoNo->num_chaves++;
        j++;
    }
}

void apagaChaves(No *no, int inicio, int fim){
    int numChavesApagadas = fim - inicio + 1;
    no->num_chaves -= numChavesApagadas;
    for(int i = inicio; i <= fim; i++){
        no->chaves[i] = -1;
    }
}

void insereMultiway(No** raiz, int valor, void *dados) {
    if (*raiz == NULL) {
        *raiz = criaNo();
        *raiz = insereChaveOrdenada(*raiz, valor, dados);
        return;
    }
    No *folha = buscaFolha(*raiz, valor);
    if (temEspaco(folha)) {
        folha = insereChaveOrdenada(folha, valor, dados);
        return;
    }
    No *novaFolha = criaNo();
    No *novaRaiz = criaNo();
    copiaChaves(folha, novaFolha, M/2, M-1);
    apagaChaves(folha, M/2, M-1);
    novaRaiz->filho[0] = *raiz;
    novaRaiz->filho[1] = novaFolha;
    *raiz = novaRaiz;
    insereMultiway(raiz, valor, dados);
}

void imprimeArvore(No *no, int nivel) {
    if (no == NULL) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        printf(" ");
    }
    for (int i = 0; i < no->num_chaves; i++) {
        printf("%d ", no->chaves[i]);
    }
    for (int i = 0; i <= no->num_chaves; i++) {
        imprimeArvore(no->filho[i], nivel + 1);
    }
}

void removeMultiway(No** raiz, int valor) {
    if (*raiz == NULL) {
        return;
    }
    No *folha = buscaFolha(*raiz, valor);
    if (folha == NULL) {
        return;
    }
    int posicao = buscaPosicao(folha, valor);
    if (posicao == folha->num_chaves || folha->chaves[posicao] != valor) {
        return;
    }
    for (int i = posicao + 1; i < folha->num_chaves; i++) {
        folha->chaves[i - 1] = folha->chaves[i];
    }
    folha->chaves[folha->num_chaves - 1] = -1;
    folha->num_chaves--;
    if (folha->num_chaves >= (M-1)/2) {
        return;
    }
    if (folha->pai == NULL) {
        if (folha->num_chaves == 0) {
            *raiz = folha->filho[0];
        }
        return;
    }
    No *pai = folha->pai;
    int posicaoPai = buscaPosicao(pai, folha->chaves[0]);
    No *vizinhoEsquerdo = NULL;
    No *vizinhoDireito = NULL;
    if (posicaoPai > 0) {
        vizinhoEsquerdo = pai->filho[posicaoPai - 1];
    }
    if (posicaoPai < pai->num_chaves) {
        vizinhoDireito = pai->filho[posicaoPai + 1];
    }
    if (vizinhoEsquerdo != NULL && vizinhoEsquerdo->num_chaves > (M-1)/2) {
        for (int i = folha->num_chaves; i > 0; i--) {
            folha->chaves[i] = folha->chaves[i - 1];
        }
        folha->chaves[0] = pai->chaves[posicaoPai - 1];
        folha->num_chaves++;
        pai->chaves[posicaoPai - 1] = vizinhoEsquerdo->chaves[vizinhoEsquerdo->num_chaves -1];
        vizinhoEsquerdo->chaves[vizinhoEsquerdo->num_chaves - 1] = -1;
        vizinhoEsquerdo->num_chaves--;
        return;
    }
    if (vizinhoDireito != NULL && vizinhoDireito->num_chaves > (M-1)/2) {
        folha->chaves[folha->num_chaves] = pai->chaves[posicaoPai];
        folha->num_chaves++;
        pai->chaves[posicaoPai] = vizinhoDireito->chaves[0];
        for (int i = 0; i < vizinhoDireito->num_chaves - 1; i++) {
            vizinhoDireito->chaves[i] = vizinhoDireito->chaves[i + 1];
        }
        vizinhoDireito->chaves[vizinhoDireito->num_chaves - 1] = -1;
        vizinhoDireito->num_chaves--;
        return;
    }
    if (vizinhoEsquerdo != NULL) {
        copiaChaves(folha, vizinhoEsquerdo, 0, folha->num_chaves - 1);
        for (int i = posicaoPai; i < pai->num_chaves; i++) {
            pai->chaves[i - 1] = pai->chaves[i];
        }
        for (int i = posicaoPai + 1; i <= pai->num_chaves; i++) {
            pai->filho[i - 1] = pai->filho[i];
        }
        pai->chaves[pai->num_chaves - 1] = -1;
        pai->filho[pai->num_chaves] = NULL;
        pai->num_chaves--;
        free(folha);
        removeMultiway(raiz, valor);
        return;
    }
    if (vizinhoDireito != NULL) {
        copiaChaves(vizinhoDireito, folha, folha->num_chaves, vizinhoDireito->num_chaves - 1);
        for (int i = posicaoPai; i < pai->num_chaves; i++) {
            pai->chaves[i] = pai->chaves[i + 1];
        }
        for (int i = posicaoPai + 1; i <= pai->num_chaves; i++) {
            pai->filho[i] = pai->filho[i + 1];
        }
        pai->chaves[pai->num_chaves - 1] = -1;
        pai->filho[pai->num_chaves] = NULL;
        pai->num_chaves--;
        free(vizinhoDireito);
        removeMultiway(raiz, valor);
        return;
    }
}

int main(){ 
    int opcao, valor;
    No *raiz = NULL;

    do{
        printf("1 - Inserir \n");
        printf("2 - Remover \n");
        printf("3 - Imprimir \n");
        printf("4 - Buscar \n");
        printf("5 - Sair \n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                Produto *p = (Produto*) malloc(sizeof(Produto));
                strcpy(p->nome, "Produto 1");
                insereMultiway(&raiz, valor, p);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removeMultiway(&raiz, valor);
                break;
            case 3:
                printf("Imprimindo arvore: \n");
                imprimeArvore(raiz, 0);
                break;
            case 4:
                // verificar se o valor foi encontrado
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                if(buscaFolha(raiz, valor) != NULL){
                    printf("Valor encontrado!\n");
                }else{
                    printf("Valor nao encontrado! \n");
                }
                break;
            case 5:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    }while(opcao != 5);
}