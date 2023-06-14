
typedef struct NO 
{ 
  int info; 
  struct NO *esquerda, *direita;
  void * dados;
} node; 

node *pesquisar(node*, int); 

int proxmaior(node*, int); 
void inserir(node **, int, void*); 
void imprimir(node*, int); 
void range(node*, int, int); 
int excluir_menor(node*); 
void excluir(node *, int); 
void del(node*, node*); 
 
void percorre_preordem(node *); 
void percorre_posordem(node *); 
void percorre_emordem(node *); 
node * maior(node * ); 
int menor(node * ); 
 

 
node *pesquisar(node *v, int chave) { 
  if( v == NULL) 
  { 
    return NULL; 
  } 
  if(v->info == chave) 
  { 
    return v; 
  } 
  else if(v->info < chave) 
  { 
    return pesquisar(v->direita, chave); 
  } 
  else
  { 
    return pesquisar(v->esquerda, chave); 
  } 
} 
 
/* maior no próximo elemento informado */ 
int proxmaior(node *root, int chave) { 
  node *p=NULL, *v; 
 
  v = root; 
  while( v != NULL && v->info != chave) 
  { 
    if(v->info < chave) 
    { 
      v = v->direita; 
    } 
    else
    { 
      p = v; 
      v = v->esquerda; 
    } 
  } 
  if(v == NULL) 
  { 
    printf("\n Elemento nao encontrado"); 
    return -1; 
  } 
  if( v->direita != NULL ) 
  { 
    v = v->direita; 
    while(v->esquerda != NULL) 
    { 
      v = v->esquerda; 
    } 
    return v->info; 
  } 
  if(p != NULL) 
  { 
    return p->info; 
  } 
  else 
  { 
    return -1; 
  } 
} 
 
void inserir(node **arvore, int chave, void * dados) { 
  if (*arvore == NULL) { 
    *arvore = malloc(sizeof(node)); 
    (*arvore)->info = chave; 
    (*arvore)->esquerda = NULL; 
    (*arvore)->direita = NULL;
    (*arvore)->dados = dados;
  } 
  else if((*arvore)->info < chave) { 
    inserir(&((*arvore)->direita), chave, dados); 
  } 
  else { 
    inserir(&((*arvore)->esquerda), chave, dados); 
  }

  return; 
}
 
void imprimir(node *v, int nivel) { 
  int i; 
 
  if( v != NULL ) 
  { 
    imprimir(v->esquerda, nivel+1); 
    for(i=0; i<nivel; i++) 
    { 
      printf(" "); 
    } 
    printf("%d\n", v->info); 
    imprimir(v->direita, nivel+1);
  } 
  return; 
}
 
/* mostra os nós de um intervalo informado */ 
void range(node *v, int x, int y) { 
  if( v == NULL ) 
  { 
    return; 
  } 
  if(v->info >= x) 
  { 
    range(v->esquerda, x,y); 
  } 
  if(x <= v->info && v->info <= y) 
  { 
    printf(" %d", v->info); 
  } 
  if(v->info <= y) 
  { 
    range(v->direita, x,y); 
  } 
  return; 
}
 
/* excluir o menor */ 
int excluir_menor(node *root) { 
  int menor; 
  node *p, *v; 
  if(root->esquerda == NULL) 
  { 
    menor = root->info; 
    root = root->direita; 
  } 
  else
  { 
    v = root; 
  do 
  { 
    p = v; 
    v = v->esquerda; 
    } while(v->esquerda != NULL); 
    menor = v->info; 
    p->esquerda = v->direita; 
  } 
  return menor; 
}
 
/* exclusão de elemento da árvore */
void excluir(node *p, int chave) { 
  node *q; 
 
  if(p == NULL) 
  { 
    printf("\n Elemento nao existe!"); 
  } 
  else if( chave < p->info ) 
  { 
    excluir(p->esquerda, chave); 
  } 
  else if( chave > p->info ) 
  { 
    excluir(p->direita, chave); 
  } 
  else 
  { 
    q = p; 
    if(q->direita == NULL)
    {
      p = q->esquerda; 
    }
    else if( q->esquerda == NULL) 
    { 
      p = q->direita; 
    } 
    else 
    { 
      del(q, q->esquerda); 
    } 
    free(q); 
  } 
  return; 
} 
 
/* procura sucessor para depois excluir */ 
void del(node *q, node *r) { 
  if(r->direita != NULL) 
  { 
    del(q, r->direita); 
  } 
  else 
  { 
    q->info = r->info; 
    q = r; 
    r = r->esquerda; 
  } 
  return; 
}
 
/* percorrer uma árvore utilizando o algoritmo de pré-ordem */ 
void percorre_preordem(node * arvore) { 
  if( arvore == NULL ) 
  { 
    return; 
  } 
 
  printf(" %d", arvore->info); 
  percorre_preordem(arvore->esquerda); 
  percorre_preordem(arvore->direita); 
  
  return; 
}
 
/* percorrer uma árvore utilizando o algoritmo de pós-ordem */
void percorre_posordem(node * arvore) { 
  if( arvore == NULL ) 
  { 
    return; 
  } 
 
  percorre_posordem(arvore->esquerda); 
  percorre_posordem(arvore->direita); 
  printf(" %d", arvore->info); 
  return; 
}
 
/* percorrer uma árvore utilizando no modo em-ordem */ 
void percorre_emordem(node * arvore) { 
  if( arvore == NULL ) 
  { 
    return; 
  } 
  
  percorre_emordem(arvore->esquerda); 
  printf(" %d", arvore->info); 
  percorre_emordem(arvore->direita); 
  
  return; 
}
 
/* pesquisa do maior elemento na árvore */ 
node * maior(node * arvore ) { 
  node *aux = arvore;

  while(aux != NULL && aux->direita != NULL) { 
    aux = aux->direita; 
  }
  return aux; 
} 
 
/* pesquisa do menor elemento na árvore */ 
int menor(node * arvore) { 
  int menor; 
  menor = arvore->info; 
  
  while( arvore != NULL ) 
  { 
    menor = arvore->info; 
    arvore = arvore->esquerda; 
  } 
  return menor; 
}