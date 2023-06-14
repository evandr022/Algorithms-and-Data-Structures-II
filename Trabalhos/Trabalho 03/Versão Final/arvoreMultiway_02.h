#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 50

typedef struct Produto_02{

    char nomeProduto[50];
    char valorProduto[10];

} Produto_02;

typedef struct no_02{
    Produto_02 produto[M - 1];
    int num_chaves;
    int chaves[M - 1];
    struct no_02 *filho[M];
    struct no_02 *pai;
} No_02;

No_02 *criaNo_02()
{
    No_02 *no_02 = (No_02 *)malloc(sizeof(No_02));
    no_02->num_chaves = 0;
    no_02->pai = NULL;
    for (int i = 0; i < M - 1; i++)
        no_02->chaves[i] = -1;
    for (int i = 0; i < M; i++)
        no_02->filho[i] = NULL;
    return no_02;
}

No_02 *buscaFolha_02(No_02 *no_02, int valor)
{
    if (no_02->filho[0] == NULL)
    {
        return no_02;
    }
    int i;
    for (i = 0; i < no_02->num_chaves && valor > no_02->chaves[i]; i++)
        ;
    return buscaFolha_02(no_02->filho[i], valor);
}

int temEspaco_02(No_02 *no_02)
{
    return no_02->num_chaves < M - 1;
}

int buscaPosicao_02(No_02 *no_02, int valor)
{
    int i = 0;
    while (i < no_02->num_chaves && valor > no_02->chaves[i])
        i++;
    return i;
}

No_02 *insereChaveOrdenada_02(No_02 *no_02, int valor, Produto_02 *p)
{
    int pos = buscaPosicao_02(no_02, valor);
    if (pos < no_02->num_chaves && no_02->chaves[pos] == valor)
    {
        // chave já existe no_02 nó, não faz nada
        return no_02;
    }
    if (!temEspaco_02(no_02)){
        // nó está cheio, precisa ser dividido
        return NULL;
    }
    for (int i = no_02->num_chaves; i > pos; i--)
    {
        no_02->chaves[i] = no_02->chaves[i - 1];
    }
    no_02->chaves[pos] = valor;
    
    Produto_02 teste;
    strcpy(teste.nomeProduto, p->nomeProduto);
    strcpy(teste.valorProduto, p->valorProduto);

    strcpy(no_02->produto[pos].nomeProduto, teste.nomeProduto);
    strcpy(no_02->produto[pos].valorProduto, teste.valorProduto);

    //no_02->produto.nomeProduto =  "a";



    no_02->num_chaves++;
    

    return no_02;
}

void copiaChaves_02(No_02 *no_02, No_02 *novoNo, int inicio, int fim)
{
    int j = 0;
    for (int i = inicio; i <= fim; i++)
    {
        novoNo->chaves[j] = no_02->chaves[i];
        novoNo->num_chaves++;
        j++;
    }
}

void apagaChaves_02(No_02 *no_02, int inicio, int fim)
{
    int numChavesApagadas = fim - inicio + 1;
    no_02->num_chaves -= numChavesApagadas;
    for (int i = inicio; i <= fim; i++)
    {
        no_02->chaves[i] = -1;
    }
}

void insereMultiway_02(No_02 **raiz, int valor, Produto_02 *p)
{
    if (*raiz == NULL)
    {
        *raiz = criaNo_02();
        *raiz = insereChaveOrdenada_02(*raiz, valor, p);
        return;
    }
    No_02 *folha = buscaFolha_02(*raiz, valor);
    if (temEspaco_02(folha))
    {
        folha = insereChaveOrdenada_02(folha, valor, p);
        return;
    }
    No_02 *novaFolha = criaNo_02();
    No_02 *novaRaiz = criaNo_02();
    copiaChaves_02(folha, novaFolha, M / 2, M - 1);
    apagaChaves_02(folha, M / 2, M - 1);
    novaRaiz->filho[0] = *raiz;
    novaRaiz->filho[1] = novaFolha;
    *raiz = novaRaiz;
    insereMultiway_02(raiz, valor, p);
}

void imprimeArvore_02(No_02 *no_02, int nivel)
{
    if (no_02 == NULL)
    {
        return;
    }
    for (int i = 0; i < nivel; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < no_02->num_chaves; i++)
    {
        printf("Registro do produto: (%d) -> Produto: %s, valor: R$:%s \n", no_02->chaves[i], no_02->produto[i].nomeProduto, no_02->produto[i].valorProduto);
    }
    for (int i = 0; i <= no_02->num_chaves; i++)
    {
        imprimeArvore_02(no_02->filho[i], nivel + 1);
    }
}

void removeMultiway_02(No_02 **raiz, int valor)
{
    if (*raiz == NULL)
    {
        return;
    }
    No_02 *folha = buscaFolha_02(*raiz, valor);
    if (folha == NULL)
    {
        return;
    }
    int posicao = buscaPosicao_02(folha, valor);
    if (posicao == folha->num_chaves || folha->chaves[posicao] != valor)
    {
        return;
    }
    for (int i = posicao + 1; i < folha->num_chaves; i++)
    {
        folha->chaves[i - 1] = folha->chaves[i];
    }
    folha->chaves[folha->num_chaves - 1] = -1;
    folha->num_chaves--;
    if (folha->num_chaves >= (M - 1) / 2)
    {
        return;
    }
    if (folha->pai == NULL)
    {
        if (folha->num_chaves == 0)
        {
            *raiz = folha->filho[0];
        }
        return;
    }
    No_02 *pai = folha->pai;
    int posicaoPai = buscaPosicao_02(pai, folha->chaves[0]);
    No_02 *vizinhoEsquerdo = NULL;
    No_02 *vizinhoDireito = NULL;
    if (posicaoPai > 0)
    {
        vizinhoEsquerdo = pai->filho[posicaoPai - 1];
    }
    if (posicaoPai < pai->num_chaves)
    {
        vizinhoDireito = pai->filho[posicaoPai + 1];
    }
    if (vizinhoEsquerdo != NULL && vizinhoEsquerdo->num_chaves > (M - 1) / 2)
    {
        for (int i = folha->num_chaves; i > 0; i--)
        {
            folha->chaves[i] = folha->chaves[i - 1];
        }
        folha->chaves[0] = pai->chaves[posicaoPai - 1];
        folha->num_chaves++;
        pai->chaves[posicaoPai - 1] = vizinhoEsquerdo->chaves[vizinhoEsquerdo->num_chaves - 1];
        vizinhoEsquerdo->chaves[vizinhoEsquerdo->num_chaves - 1] = -1;
        vizinhoEsquerdo->num_chaves--;
        return;
    }
    if (vizinhoDireito != NULL && vizinhoDireito->num_chaves > (M - 1) / 2)
    {
        folha->chaves[folha->num_chaves] = pai->chaves[posicaoPai];
        folha->num_chaves++;
        pai->chaves[posicaoPai] = vizinhoDireito->chaves[0];
        for (int i = 0; i < vizinhoDireito->num_chaves - 1; i++)
        {
            vizinhoDireito->chaves[i] = vizinhoDireito->chaves[i + 1];
        }
        vizinhoDireito->chaves[vizinhoDireito->num_chaves - 1] = -1;
        vizinhoDireito->num_chaves--;
        return;
    }
    if (vizinhoEsquerdo != NULL)
    {
        copiaChaves_02(folha, vizinhoEsquerdo, 0, folha->num_chaves - 1);
        for (int i = posicaoPai; i < pai->num_chaves; i++)
        {
            pai->chaves[i - 1] = pai->chaves[i];
        }
        for (int i = posicaoPai + 1; i <= pai->num_chaves; i++)
        {
            pai->filho[i - 1] = pai->filho[i];
        }
        pai->chaves[pai->num_chaves - 1] = -1;
        pai->filho[pai->num_chaves] = NULL;
        pai->num_chaves--;
        free(folha);
        removeMultiway_02(raiz, valor);
        return;
    }
    if (vizinhoDireito != NULL)
    {
        copiaChaves_02(vizinhoDireito, folha, folha->num_chaves, vizinhoDireito->num_chaves - 1);
        for (int i = posicaoPai; i < pai->num_chaves; i++)
        {
            pai->chaves[i] = pai->chaves[i + 1];
        }
        for (int i = posicaoPai + 1; i <= pai->num_chaves; i++)
        {
            pai->filho[i] = pai->filho[i + 1];
        }
        pai->chaves[pai->num_chaves - 1] = -1;
        pai->filho[pai->num_chaves] = NULL;
        pai->num_chaves--;
        free(vizinhoDireito);
        removeMultiway_02(raiz, valor);
        return;
    }
}