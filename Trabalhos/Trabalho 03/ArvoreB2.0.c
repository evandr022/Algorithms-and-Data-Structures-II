//implemente uma arvore B que guarde qualquer tipo em c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

// que guarde qualquer tipo
// ex.: void** chave

typedef struct no{
    int n;
    void** chave;
    struct no** filho;
    struct no* pai;
}no;

typedef struct arvore{
    no* raiz;
}arvore;

void inicializa(arvore* a){
    a->raiz = NULL;
}

void inicializa_no(no* n){
    n->n = 0;
    n->chave = (void**) malloc(sizeof(void*) * MAX);
    n->filho = (no**) malloc(sizeof(no*) * MAX);
    n->pai = NULL;
}

void split_tree(no* n, int i){
    no* z = (no*) malloc(sizeof(no));
    inicializa_no(z);
    no* y = n->filho[i];
    z->filho[0] = y->filho[2];
    if(z->filho[0] != NULL){
        z->filho[0]->pai = z;
    }
    z->chave[0] = y->chave[1];
    z->n = 1;
    y->n = 1;
    int j;
    for(j = n->n; j >= i + 1; j--){
        n->filho[j + 1] = n->filho[j];
    }
    n->filho[i + 1] = z;
    z->pai = n;
    for(j = n->n - 1; j >= i; j--){
        n->chave[j + 1] = n->chave[j];
    }
    n->chave[i] = y->chave[1];
    n->n++;
}

void insere_nao_cheio(no* n, void* chave){
    int i = n->n - 1;
    if(n->filho[0] == NULL){
        while(i >= 0 && strcmp((char*) n->chave[i], (char*) chave) > 0){
            n->chave[i + 1] = n->chave[i];
            i--;
        }
        n->chave[i + 1] = chave;
        n->n++;
    }else{
        while(i >= 0 && strcmp((char*) n->chave[i], (char*) chave) > 0){
            i--;
        }
        i++;
        if(n->filho[i]->n == MAX){
            split_tree(n, i);
            if(strcmp((char*) chave, (char*) n->chave[i]) > 0){
                i++;
            }
        }
        insere_nao_cheio(n->filho[i], chave);
    }
}

void insere(arvore* a, void* chave){
    no* r = a->raiz;
    if(r == NULL){
        r = (no*) malloc(sizeof(no));
        inicializa_no(r);
        r->chave[0] = chave;
        r->n = 1;
        a->raiz = r;
    }else{
        if(r->n == MAX){
            no* s = (no*) malloc(sizeof(no));
            inicializa_no(s);
            a->raiz = s;
            s->filho[0] = r;
            r->pai = s;
            split_tree(s, 0);
            insere_nao_cheio(s, chave);
        }else{
            insere_nao_cheio(r, chave);
        }
    }
}

void imprime_no(no* n){
    int i;
    for(i = 0; i < n->n; i++){
        if(n->filho[0] != NULL){
            imprime_no(n->filho[i]);
        }
        printf("%s ", (char*) n->chave[i]);
    }
    if(n->filho[0] != NULL){
        imprime_no(n->filho[i]);
    }
}

void imprime(arvore* a){
    imprime_no(a->raiz);
}

void remove_nao_vazio(no* n, void* chave){
    int i = 0;
    while(i < n->n && strcmp((char*) n->chave[i], (char*) chave) < 0){
        i++;
    }
    if(i < n->n && strcmp((char*) n->chave[i], (char*) chave) == 0){
        if(n->filho[0] == NULL){
            int j;
            for(j = i + 1; j < n->n; j++){
                n->chave[j - 1] = n->chave[j];
            }
            n->n--;
        }else{
            no* y = n->filho[i];
            if(y->n >= 1){
                while(y->filho[0] != NULL){
                    y = y->filho[y->n];
                }
                n->chave[i] = y->chave[y->n - 1];
                remove_nao_vazio(y, y->chave[y->n - 1]);
            }else{
                no* z = n->filho[i + 1];
                if(z->n >= 1){
                    while(z->filho[0] != NULL){
                        z = z->filho[0];
                    }
                    n->chave[i] = z->chave[0];
                    remove_nao_vazio(z, z->chave[0]);
                }else{
                    y->chave[1] = n->chave[i];
                    y->n = 2;
                    y->filho[2] = z->filho[0];
                    if(y->filho[2] != NULL){
                        y->filho[2]->pai = y;
                    }
                    y->filho[3] = z->filho[1];
                    if(y->filho[3] != NULL){
                        y->filho[3]->pai = y;
                    }
                    int j;
                    for(j = i + 1; j < n->n; j++){
                        n->chave[j - 1] = n->chave[j];
                        n->filho[j] = n->filho[j + 1];
                    }
                    n->n--;
                    free(z);
                    remove_nao_vazio(y, chave);
                }
            }
        }
    }else{
        if(n->filho[0] == NULL){
            printf("Chave nao encontrada");
        }else{
            no* y = n->filho[i];
            if(y->n == 1){
                if(i > 0){
                    no* w = n->filho[i - 1];
                    if(w->n >= 2){
                        int j;
                        for(j = y->n; j >= 1; j--){
                            y->chave[j] = y->chave[j - 1];
                        }
                        y->chave[0] = n->chave[i - 1];
                        y->n++;
                        n->chave[i - 1] = w->chave[w->n - 1];
                        w->n--;
                        if(w->filho[0] != NULL){
                            y->filho[0] = w->filho[w->n];
                            y->filho[0]->pai = y;
                            w->filho[w->n] = NULL;
                        }
                    }else{
                        w->chave[1] = n->chave[i - 1];
                        w->n = 2;
                        w->filho[2] = y->filho[0];
                        if(w->filho[2] != NULL){
                            w->filho[2]->pai = w;
                        }
                        w->filho[3] = y->filho[1];
                        if(w->filho[3] != NULL){
                            w->filho[3]->pai = w;
                        }
                        int j;
                        for(j = i - 1; j < n->n; j++){
                            n->chave[j] = n->chave[j + 1];
                            n->filho[j + 1] = n->filho[j + 2];
                        }
                        n->n--;
                        free(y);
                        y = w;
                    }
                }else{
                    no* w = n->filho[i + 1];
                    if(w->n >= 2){
                        y->chave[1] = n->chave[i];
                        y->n = 2;
                        y->filho[2] = w->filho[0];
                        if(y->filho[2] != NULL){
                            y->filho[2]->pai = y;
                        }
                        y->filho[3] = w->filho[1];
                        if(y->filho[3] != NULL){
                            y->filho[3]->pai = y;
                        }
                        n->chave[i] = w->chave[0];
                        int j;
                        for(j = 1; j < w->n; j++){
                            w->chave[j - 1] = w->chave[j];
                        }
                        for(j = 1; j <= w->n; j++){
                            w->filho[j - 1] = w->filho[j];
                        }
                        w->n--;
                    }else{
                        y->chave[1] = n->chave[i];
                        y->n = 2;
                        y->filho[2] = w->filho[0];
                        if(y->filho[2] != NULL){
                            y->filho[2]->pai = y;
                        }
                        y->filho[3] = w->filho[1];
                        if(y->filho[3] != NULL){
                            y->filho[3]->pai = y;
                        }
                        int j;
                        for(j = i + 1; j < n->n; j++){
                            n->chave[j - 1] = n->chave[j];
                            n->filho[j] = n->filho[j + 1];
                        }
                        n->n--;
                        free(w);
                    }
                }
                remove_nao_vazio(y, chave);
            }else{
                remove_nao_vazio(y, chave);
            }
        }
    }
}

void remover(arvore* a, void* chave){
    no* r = a->raiz;
    if(r == NULL){
        printf("Arvore vazia");
    }else{
        if(r->n == 1){
            if(r->filho[0] == NULL){
                a->raiz = NULL;
                free(r);
            }else{
                if(r->filho[0]->n == 1){
                    no* s = r->filho[0];
                    r->chave[0] = s->chave[0];
                    r->filho[0] = s->filho[0];
                    r->filho[1] = s->filho[1];
                    r->n = 1;
                    free(s);
                    remove_nao_vazio(r, chave);
                }else{
                    remove_nao_vazio(r, chave);
                }
            }
        }else{
            remove_nao_vazio(r, chave);
        }
    }
}

int main(){
    arvore a;
    inicializa(&a);
    insere(&a, "a");
    insere(&a, "b");
    insere(&a, "c");
    insere(&a, "d");
    insere(&a, "e");
    insere(&a, "f");
    insere(&a, "g");
    insere(&a, "h");
    insere(&a, "i");
    insere(&a, "j");
    insere(&a, "k");
    insere(&a, "l");
    insere(&a, "m");
    insere(&a, "n");
    insere(&a, "o");
    insere(&a, "p");
    insere(&a, "q");
    insere(&a, "r");
    insere(&a, "s");
    insere(&a, "t");
    insere(&a, "u");
    insere(&a, "v");
    insere(&a, "w");
    insere(&a, "x");
    insere(&a, "y");
    insere(&a, "z");
    imprime(&a);
    remover(&a, "a");
    remover(&a, "b");
    imprime(&a);
    return 0;
}

