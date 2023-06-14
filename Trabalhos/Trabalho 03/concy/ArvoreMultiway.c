// faca uma arvore multiway de busca que use M para o maximo de nos no filho m para minimo de nos no filho

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3
#define m 2

typedef struct no{
    int nchaves;
    int chaves[M-1];
    struct no *filhos[M];
}no;

typedef struct arvore{
    no *raiz;
}arvore;

void inicializa(arvore *a){
    a->raiz = NULL;
}

void imprime(no *r, int nivel){
    int i;
    if(r != NULL){
        for(i = 0; i < nivel; i++)
            printf(" ");
        for(i = 0; i < r->nchaves; i++)
            printf("%d ", r->chaves[i]);
        printf("");

        for(i = 0; i <= r->nchaves; i++)
            imprime(r->filhos[i], nivel+1);
    }
}

void imprime_arvore(arvore *a){
    imprime(a->raiz, 0);
}

void insere(arvore *a, int chave){
    no *r = a->raiz;
    if(r == NULL){
        r = (no*)malloc(sizeof(no));
        r->nchaves = 1;
        r->chaves[0] = chave;
        r->filhos[0] = NULL;
        r->filhos[1] = NULL;
        a->raiz = r;
    }else{
        if(r->nchaves == M-1){
            no *s = (no*)malloc(sizeof(no));
            s->nchaves = 0;
            s->filhos[0] = r;
            a->raiz = s;
            divide_no(s, 0, r);
            insere_nao_cheio(s, chave);
        }else
            insere_nao_cheio(r, chave);
    }
}

void divide_no(no *x, int i, no *y){
    no *z = (no*)malloc(sizeof(no));
    z->nchaves = m-1;
    int j;
    for(j = 0; j < m-1; j++)
        z->chaves[j] = y->chaves[j+m];
    for(j = 0; j < m; j++)
        z->filhos[j] = y->filhos[j+m];
    y->nchaves = m-1;
    for(j = x->nchaves; j >= i+1; j--)
        x->filhos[j+1] = x->filhos[j];
    x->filhos[i+1] = z;
    for(j = x->nchaves-1; j >= i; j--)
        x->chaves[j+1] = x->chaves[j];
    x->chaves[i] = y->chaves[m-1];
    x->nchaves = x->nchaves + 1;
}

void insere_nao_cheio(no *x, int k){
    int i = x->nchaves-1;
    if(x->filhos[0] == NULL){
        while(i >= 0 && k < x->chaves[i]){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        x->chaves[i+1] = k;
        x->nchaves = x->nchaves + 1;
    }else{
        while(i >= 0 && k < x->chaves[i])
            i--;
        i++;
        if(x->filhos[i]->nchaves == M-1){
            divide_no(x, i, x->filhos[i]);
            if(k > x->chaves[i])
                i++;
        }
        insere_nao_cheio(x->filhos[i], k);
    }
}

void remove_no(arvore *a, int chave){
    no *r = a->raiz;
    if(r != NULL){
        remove_chave(r, chave);
        if(r->nchaves == 0){
            no *s = r;
            r = r->filhos[0];
            free(s);
            a->raiz = r;
        }
    }
}

void remove_chave(no *x, int k){
    int i = 0;
    while(i < x->nchaves && k > x->chaves[i])
        i++;
    if(i < x->nchaves && k == x->chaves[i]){
        if(x->filhos[0] == NULL)
            remove_chave_folha(x, i);
        else
            remove_chave_nao_folha(x, i);
    }else{
        if(x->filhos[0] != NULL){
            int flag = 0;
            if(i == x->nchaves)
                flag = 1;
            if(x->filhos[i]->nchaves < m)
                preenche(x, i);
            if(flag && i > x->nchaves)
                remove_chave(x->filhos[i-1], k);
            else
                remove_chave(x->filhos[i], k);
        }
    }
}