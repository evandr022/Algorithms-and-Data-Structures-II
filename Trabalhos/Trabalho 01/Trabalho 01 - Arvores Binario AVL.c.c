/* Algoritmos e Estruturas de Dados II - AEDII
Aluno: Evandro Salvador Marinho da Silva - 22052988
Professor: Dr. Edson Nascimento Silva Junior
Trabalho 01 - Arvore binaria AVL*/

//-------------------------------------------BIBLIOTECA------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-------------------------------------------ARVORE AVL------------------------------------------//
typedef struct no{
    int pedido;
    int regiao;
    int chave;
    int chaveHora;
    int chaveMinuto;
    int altura;
    int FatorBalanciador;
    struct no *esq;
    struct no *dir;
} no;

typedef struct tipoEntregador{
    int entregador[8];
    no *entregas[8];

} tipoEntregador;

//-------------------------------------------ALTURA----------------------------------------------//
int altura(no *raiz){
    if (raiz == NULL)
        return 0;
    else{
        int alt_esq = altura(raiz->esq);
        int alt_dir = altura(raiz->dir);
        if (alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}

//------------------------------------BALANCEAMENTO----------------------------------------------//
no *rotacao_esquerda(no *raiz){
    no *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->altura = altura(raiz);
    aux->altura = altura(aux);
    return aux;
}

no *rotacao_direita(no *raiz){
    no *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->altura = altura(raiz);
    aux->altura = altura(aux);
    return aux;
}

no *rotacao_dupla_esquerda(no *raiz){
    raiz->dir = rotacao_direita(raiz->dir);
    return rotacao_esquerda(raiz);
}

no *rotacao_dupla_direita(no *raiz){
    raiz->esq = rotacao_esquerda(raiz->esq);
    return rotacao_direita(raiz);
}

no *balancear(no *raiz){
    if (raiz->FatorBalanciador == 2){
        if (raiz->esq->FatorBalanciador >= 0)
            return rotacao_direita(raiz);
        else
            return rotacao_dupla_direita(raiz);
    }
    else{
        if (raiz->FatorBalanciador == -2){
            if (raiz->dir->FatorBalanciador <= 0)
                return rotacao_esquerda(raiz);
            else
                return rotacao_dupla_esquerda(raiz);
        }
    }
    return raiz;
}

//-----------------------------------------INSERIR-----------------------------------------------//
no *insere(no *raiz, int novo, int regiao, int minuto, int pedido){
    if (raiz == NULL){
        no *novo_no = (no *)malloc(sizeof(no));
        novo_no->chaveHora = novo;
        novo_no->chaveMinuto = minuto;
        novo_no->regiao = regiao;
        novo_no->pedido = pedido;
        novo_no->chave = (novo * 60) + minuto;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->altura = 1;
        novo_no->FatorBalanciador = 0;
        return novo_no;
    }
    else{
        if ((novo * 60 + minuto) < raiz->chave){ // se for menor eu insiro do lado esquerto
            raiz->esq = insere(raiz->esq, novo, regiao, minuto, pedido);
            raiz->altura = altura(raiz);
            raiz->FatorBalanciador = altura(raiz->esq) - altura(raiz->dir);
            return balancear(raiz);
        }
        else{
            if ((novo * 60 + minuto) > raiz->chave){ // se for maior eu insiro do lado direito
                raiz->dir = insere(raiz->dir, novo, regiao, minuto, pedido);
                raiz->altura = altura(raiz);
                raiz->FatorBalanciador = altura(raiz->esq) - altura(raiz->dir);
                return balancear(raiz);
            }
            else
                return raiz;
        }
    }
}

//-----------------------------------------BUSCAR------------------------------------------------//
int buscar(no *raiz, int chave){
    if (raiz == NULL)
        return -1;
    else{
        if (raiz->chave == chave)
            return raiz->chave;
        else{
            if (chave < raiz->chave)
                return buscar(raiz->esq, chave);
            else
                return buscar(raiz->dir, chave);
        }
    }
}

//------------------------------------------IMPRIMIR--------------------------------------------//
void imprimir(no *raiz){
    if (raiz != NULL){
        imprimir(raiz->esq);
        printf("\t Numero do pedido: %d -> feito as %dH%dmin \n", raiz->chave, raiz->chaveHora, raiz->chaveMinuto);
        imprimir(raiz->dir);
    }
}

//------------------------------------------REMOVER----------------------------------------------//
no *remover(no *raiz, int chave){

    if (raiz == NULL){
        return NULL;
    }
    else{
        if (chave < raiz->chave){
            raiz->esq = remover(raiz->esq, chave);
            raiz->altura = altura(raiz);
            raiz->FatorBalanciador = altura(raiz->esq) - altura(raiz->dir);
            return balancear(raiz);
        }
        else{
            if (chave > raiz->chave){
                raiz->dir = remover(raiz->dir, chave);
                raiz->altura = altura(raiz);
                raiz->FatorBalanciador = altura(raiz->esq) - altura(raiz->dir);
                return balancear(raiz);
            }
            else{
                if (raiz->esq == NULL && raiz->dir == NULL){
                    free(raiz);

                    return NULL;
                }
                else{
                    if (raiz->esq == NULL || raiz->dir == NULL){
                        no *aux;
                        if (raiz->esq == NULL)
                            aux = raiz->dir;
                        else
                            aux = raiz->esq;
                        free(raiz);
                        return aux;
                    }
                    else{
                        no *aux = raiz->dir;
                        while (aux->esq != NULL)
                            aux = aux->esq;
                        raiz->chave = aux->chave;
                        raiz->dir = remover(raiz->dir, aux->chave);
                        raiz->altura = altura(raiz);
                        raiz->FatorBalanciador = altura(raiz->esq) - altura(raiz->dir);
                        return balancear(raiz);
                    }
                }
            }
        }
    }
}

//----------------------------------------TRANSFERENCIA------------------------------------------//
no *transfereArvore(no *arvore, no *novaArvore){   //copiar a arvore

    if (arvore){
        novaArvore = transfereArvore(arvore->esq, novaArvore);
        int hora = arvore->chaveHora;
        int minuto = arvore->chaveMinuto;
        int regiao = arvore->regiao;
        int pedido = arvore->pedido;
        novaArvore = insere(novaArvore, hora, regiao, minuto, pedido);
        novaArvore = transfereArvore(arvore->dir, novaArvore);
    }
    return novaArvore;
}

//-------------------------------------------REGIÃO----------------------------------------------//
char *definirRegiao(char opcao){
    /*
        1 - norte
        2 - sul
        3 - leste
        4 - oeste
        5 - centro - oeste
        6 - centro - Sul
        7 - centro -Norte
        8 - Extremo - Norte
    */

    switch (opcao){
    case 1:
        return "Norte";
        break;

    case 2:
        return "Sul";
        break;

    case 3:
        return "Leste";
        break;

    case 4:
        return "Oeste";
        break;

    case 5:
        return "Centro-Oeste";
        break;

    case 6:
        return "Centro-Sul";
        break;
    case 7:
        return "Centro-Norte";
        break;

    case 8:
        return "Extremo-Norte";
        break;

    default:
        printf("A região informada não existe.");
    }

    return NULL;
}

//-------------------------------------------ENTREGADORES----------------------------------------//
tipoEntregador *formataEntregadores(int numEntregadores){

    tipoEntregador *entregadores = malloc(numEntregadores * sizeof(tipoEntregador));

    for (int i = 0; i < numEntregadores; i++){
        // 0 - está livre
        // 1 - esta ocupado
        for (int j = 0; j < 8; j++){
            entregadores[i].entregador[j] = 0;
        }
    }

    return entregadores;
}

void alocaEntregador(no *raiz, tipoEntregador *entregadores, int numEntregadores, int relogio){

    if (raiz != NULL){
        alocaEntregador(raiz->esq, entregadores, numEntregadores, relogio);

        for (int i = 0; i < numEntregadores; i++){
            int achei = 0;
            int regiaoAtual = 1;
            for (int j = 0; j < 8; j++){
                // printf("\nrodando o (i): %d e o (j): %d dados: cond 1: %d||| cond 2: %d < %d  :\n", i, j, entregadores[i].entregador[j],raiz->chave, (relogio + (2 * 60)) );
                if (entregadores[i].entregador[j] == 0 && (raiz->chave <= relogio + 59)){
                    printf("entreguei o pedido -> %d <- ao entregador %d e %d  na regiao: %s\n\n", raiz->chave, i, j, definirRegiao(raiz->regiao));
                    entregadores[i].entregador[j] = 1; // ta ocupado meu patrao
                    entregadores[i].entregas[j] = raiz;
                    achei = 1;
                    j = 8;
                }
            }
            if (achei == 1){
                i = numEntregadores;
            }
        }

        alocaEntregador(raiz->dir, entregadores, numEntregadores, relogio);
    }
}

//---------------------------------------------COMADA-------------------------------------------//
no *Comanda(no *ArvEntregas, no *arvore, tipoEntregador *entregadores, int numEntregadores, int relogio){

    ArvEntregas = NULL;
    alocaEntregador(arvore, entregadores, numEntregadores, relogio);
    no *auxVIRGEM = NULL;
    auxVIRGEM = transfereArvore(arvore, auxVIRGEM);

    for (int i = 0; i < numEntregadores; i++){
        for (int j = 0; j < 8; j++){
            // printf("vou bugar no: %d %i e o entregador eh o %d\n", i, j, entregadores[i].entregador[j]);
            if (entregadores[i].entregador[j] == 1){ // agora sim eu vejo se o entregador está livre
                // printf("valor a ser removido %d\n ",entregadores[i].entregas[j]->chave );
                ArvEntregas = insere(ArvEntregas, entregadores[i].entregas[j]->chaveHora, entregadores[i].entregas[j]->regiao,entregadores[i].entregas[j]->chaveMinuto, entregadores[i].entregas[j]->pedido); // considero o pedido entregue

                int remocao = entregadores[i].entregas[j]->chave;
                auxVIRGEM = remover(auxVIRGEM, remocao);
            }
        }

    }

    for (int i = 0; i < numEntregadores; i++){
        for (int j = 0; j < 8; j++){
            // printf("\n parabens soldado %d %d, voce fez sua entrega valor atual: %d\n", i, j, entregadores[i].entregador[j]);
            if (entregadores[i].entregador[j] == 1){
                entregadores[i].entregador[j] = 0;
            }
        }
    }

    entregadores[0].entregas[0] = ArvEntregas;

    return auxVIRGEM;
}

//--------------------------------------------RELATORIO------------------------------------------//
void imprimirTodasAsEntregas(no *arvore){
    if (arvore){
        imprimirTodasAsEntregas(arvore->esq);
        printf("\n\tPedido %d, Horario do pedido: %dH%dMIN, e sua opcao de ceia foi: %d\n", arvore->chave, arvore->chaveHora, arvore->chaveMinuto, arvore->pedido);
        imprimirTodasAsEntregas(arvore->dir);
    }
}

//-----------------------------------------------MAIN--------------------------------------------//
int main(){
    int numEntregadores = 1;
    printf("digite o numero de entregadores: ");
    scanf("%d", &numEntregadores);

    int numeroPedidos = 0;
    printf("digite o numero de pedidos: ");
    scanf("%d", &numeroPedidos);

    tipoEntregador *entregadores;
    entregadores = formataEntregadores(numEntregadores); // todos estão disponíveis ok

    int hora = 0;
    int minuto = 0;
    int regiao = 0;
    int opcao = 0;

    srand(time(NULL));

    no *arvPedidos = NULL;
    no *estruturaEntrega = NULL;
    no *arvVirgemEntregas = NULL; // vai adicionar no momento em que eu registrar a entrega

    for (int i = 0; i < numeroPedidos; i++){
        hora = 8 + (rand() % 14);
        minuto = 0 + (rand() % 59);
        regiao = 1 + (rand() % 8);
        opcao = 1 + (rand() % 4);
        arvPedidos = insere(arvPedidos, hora, regiao, minuto, opcao);
    }

    int relogio = 8 * 60;
    while (relogio <= 22 * 60){  // entrega é feita ate 22h
        printf("\n\n\n----------------------- RELOGIO AVANCOU 1H -  TEMPO ATUAL: %d ---------------------\n\n", relogio / 60);
        printf("relogio: %d", relogio / 60);

        printf("\nPedidos atuais:\n");
        imprimir(arvPedidos);
        printf("\n");

        arvPedidos = Comanda(arvVirgemEntregas, arvPedidos, entregadores, numEntregadores, relogio);
        arvVirgemEntregas = entregadores[0].entregas[0];

        printf("\n -----------> Proximos Pedidos: <-----------\n");
        imprimir(arvPedidos);
        printf("\n -----------> produtos entregues: <----------- \n");
        imprimir(arvVirgemEntregas);
        estruturaEntrega = transfereArvore(arvVirgemEntregas, estruturaEntrega);

        relogio = relogio + 60;
    }
    
    printf("\n\n\n\n\t --------------- DIA ENCERRADO ----------------------\n");
    printf("\n--------------- Relatorio de Entregas de Hoje ----------------------\n");

    imprimirTodasAsEntregas(estruturaEntrega);

    printf("\n\n\n fim do programa");
}