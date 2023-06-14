#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ORDER 3 // ordem da árvore B

// estrutura de um nó da árvore B
typedef struct node {
    void **keys; // vetor de chaves
    struct node **children; // vetor de ponteiros para os filhos
    struct node *parent; // ponteiro para o pai
    int n_keys; // quantidade de chaves armazenadas no nó
} Node;

// estrutura da árvore B
typedef struct btree {
    Node *root; // ponteiro para a raiz da árvore
} BTree;

// cria um novo nó da árvore B
Node *new_node() {
    Node *node = (Node*) malloc(sizeof(Node));
    node->keys = (void**) malloc(sizeof(void*) * ORDER);
    node->children = (Node**) malloc(sizeof(Node*) * (ORDER + 1));
    node->parent = NULL;
    node->n_keys = 0;
    return node;
}

// cria uma nova árvore B
BTree *new_btree() {
    BTree *tree = (BTree*) malloc(sizeof(BTree));
    tree->root = new_node();
    return tree;
}

// busca por um elemento na árvore B
void *btree_search(Node *node, void *key) {
    int i = 0;
    while (i < node->n_keys && strcmp(node->keys[i], key) < 0) {
        i++;
    }
    if (i < node->n_keys && strcmp(node->keys[i], key) == 0) {
        return node->keys[i];
    } else if (node->children[i] != NULL) {
        return btree_search(node->children[i], key);
    } else {
        return NULL;
    }
}

// insere um elemento na árvore B
void btree_insert(BTree *tree, void *key) {
    Node *node = tree->root;
    while (node->children[0] != NULL) {
        int i = 0;
        while (i < node->n_keys && strcmp(node->keys[i], key) < 0) {
        i++;
        }
        node = node->children[i];
    }
    // verifica se o nó está cheio
    if (node->n_keys == ORDER) {
    // divide o nó em dois
        //Node *new_node = new_node();
        Node *new_node = (Node*) malloc(sizeof(Node));
        new_node->parent = node->parent;
        int split_index = ORDER / 2;
        // transfere as chaves e os ponteiros para o novo nó
        for (int i = split_index + 1; i < ORDER; i++) {
            new_node->keys[i - split_index - 1] = node->keys[i];
            node->keys[i] = NULL;
            new_node->children[i - split_index - 1] = node->children[i];
            node->children[i] = NULL;
            if (new_node->children[i - split_index - 1] != NULL) {
                new_node->children[i - split_index - 1]->parent = new_node;
            }
        }
        new_node->children[ORDER - split_index - 1] = node->children[ORDER];
        node->children[ORDER] = NULL;
        if (new_node->children[ORDER - split_index - 1] != NULL) {
            new_node->children[ORDER - split_index - 1]->parent = new_node;
        }
        node->n_keys = split_index;
        new_node->n_keys = ORDER - split_index - 1;
        // insere a chave no nó correto
        if (strcmp(key, new_node->keys[0]) >= 0) {
            btree_insert_nonfull(new_node, key);
        } else {
            btree_insert_nonfull(node, key);
        }
    } else {
        // insere a chave no nó correto
        btree_insert_nonfull(node, key);
    }
}

// insere uma chave em um nó não cheio da árvore B
void btree_insert_nonfull(Node *node, void *key) {
    int i = node->n_keys - 1;
    while (i >= 0 && strcmp(node->keys[i], key) > 0) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->n_keys++;
}

// imprime a árvore B em ordem
void btree_print_inorder(Node node) {
    int i = 0;
    while (i < node.n_keys) {
        if (node.children[i] != NULL) {
            btree_print_inorder(*node.children[i]);
        }
        printf("%s ", (char*) node.keys[i]);
        i++;
    }
    if (node.children[i] != NULL) {
        btree_print_inorder(*node.children[i]);
    }
}

void btree_remove_nonfull(Node *node, void *key) {
    int i = 0;
    while (i < node->n_keys && strcmp(node->keys[i], key) < 0) {
        i++;
    }
    if (i < node->n_keys && strcmp(node->keys[i], key) == 0) {
        if (node->children[i] != NULL) {
            Node *left_child = node->children[i];
            Node *right_child = node->children[i + 1];
            if (left_child->n_keys >= ORDER / 2) {
                Node *predecessor = left_child;
                while (predecessor->children[predecessor->n_keys] != NULL) {
                    predecessor = predecessor->children[predecessor->n_keys];
                }
                node->keys[i] = predecessor->keys[predecessor->n_keys - 1];
                btree_remove_nonfull(left_child, predecessor->keys[predecessor->n_keys - 1]);
            } else if (right_child->n_keys >= ORDER / 2) {
                Node *successor = right_child;
                while (successor->children[0] != NULL) {
                    successor = successor->children[0];
                }
                node->keys[i] = successor->keys[0];
                btree_remove_nonfull(right_child, successor->keys[0]);
            } else {
                left_child->keys[left_child->n_keys] = node->keys[i];
                for (int j = 0; j < right_child->n_keys; j++) {
                    left_child->keys[left_child->n_keys + j + 1] = right_child->keys[j];
                }
                for (int j = 0; j <= right_child->n_keys; j++) {
                    left_child->children[left_child->n_keys + j + 1] = right_child->children[j];
                }
                left_child->n_keys += right_child->n_keys + 1;
                for (int j = i; j < node->n_keys - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                }
                for (int j = i + 1; j <= node->n_keys; j++) {
                    node->children[j] = node->children[j + 1];
                }
                node->n_keys--;
                free(right_child);
                btree_remove_nonfull(left_child, key);
            }
        } else {
            for (int j = i; j < node->n_keys - 1; j++) {
                node->keys[j] = node->keys[j + 1];
            }
            node->n_keys--;
        }
    } else {
        if (node->children[i] != NULL) {
            Node *child = node->children[i];
            if (child->n_keys >= ORDER / 2) {
                btree_remove_nonfull(child, key);
            } else {
                Node *left_sibling = NULL;
                Node *right_sibling = NULL;
                if (i > 0) {
                    left_sibling = node->children[i - 1];
                }
                if (i < node->n_keys) {
                    right_sibling = node->children[i + 1];
                }
                if (left_sibling != NULL && left_sibling->n_keys >= ORDER / 2) {
                    for (int j = child->n_keys; j > 0; j--) {
                        child->keys[j] = child->keys[j - 1];
                    }
                    child->keys[0] = node->keys[i - 1];
                    for (int j = child->n_keys + 1; j > 0; j--) {
                        child->children[j] = child->children[j - 1];
                    }
                    child->children[0] = left_sibling->children[left_sibling->n_keys];
                    node->keys[i - 1] = left_sibling->keys[left_sibling->n_keys - 1];
                    left_sibling->n_keys--;
                    child->n_keys++;
                    btree_remove_nonfull(child, key);
                } else if (right_sibling != NULL && right_sibling->n_keys >= ORDER / 2) {
                    child->keys[child->n_keys] = node->keys[i];
                    child->children[child->n_keys + 1] = right_sibling->children[0];
                    node->keys[i] = right_sibling->keys[0];
                    for (int j = 0; j < right_sibling->n_keys - 1; j++) {
                        right_sibling->keys[j] = right_sibling->keys[j + 1];
                    }
                    for (int j = 0; j < right_sibling->n_keys; j++) {
                        right_sibling->children[j] = right_sibling->children[j + 1];
                    }
                    right_sibling->n_keys--;
                    child->n_keys++;
                    btree_remove_nonfull(child, key);
                } else {
                    if (left_sibling != NULL) {
                        left_sibling->keys[left_sibling->n_keys] = node->keys[i - 1];
                        for(int j = 0; j < child->n_keys; j++) {
                            left_sibling->keys[left_sibling->n_keys + j + 1] = child->keys[j];
                        }
                        for(int j = 0; j <= child->n_keys; j++) {
                            left_sibling->children[left_sibling->n_keys + j + 1] = child->children[j];
                        }
                        left_sibling->n_keys += child->n_keys + 1;
                        for (int j = i - 1; j < node->n_keys - 1; j++) {
                            node->keys[j] = node->keys[j + 1];
                        }
                        for (int j = i; j <= node->n_keys; j++) {
                            node->children[j] = node->children[j + 1];
                        }
                        node->n_keys--;
                        free(child);
                        btree_remove_nonfull(left_sibling, key);
                    } else {
                        child->keys[child->n_keys] = node->keys[i];
                        for(int j = 0; j < right_sibling->n_keys; j++) {
                            child->keys[child->n_keys + j + 1] = right_sibling->keys[j];
                        }
                        for(int j = 0; j <= right_sibling->n_keys; j++) {
                            child->children[child->n_keys + j + 1] = right_sibling->children[j];
                        }
                        child->n_keys += right_sibling->n_keys + 1;
                        for (int j = i; j < node->n_keys - 1; j++) {
                            node->keys[j] = node->keys[j + 1];
                        }
                        for (int j = i + 1; j <= node->n_keys; j++) {
                            node->children[j] = node->children[j + 1];
                        }
                        node->n_keys--;
                        free(right_sibling);
                        btree_remove_nonfull(child, key);
                    }
                }
            }
        }
    }
}

void btree_remove(BTree *tree, char *key) {
    Node *root = tree->root;
    if (root == NULL) {
        return;
    }
    btree_remove_nonfull(root, key);
    if (root->n_keys == 0) {
        Node *new_root = root->children[0];
        free(root);
        tree->root = new_root;
    }
}




// exemplo de uso
int main() {
    BTree *tree = new_btree();
    btree_insert(tree, "banana");
    btree_insert(tree, "maçã");
    btree_insert(tree, "abacate");
    btree_insert(tree, "uva");
    btree_insert(tree, "laranja");
    // imprimir a arvore
    btree_print(tree);
    // remover um elemento
    btree_remove(tree, "uva");
    // imprimir a arvore
    btree_print(tree);
    printf("\n");
    return 0;
}