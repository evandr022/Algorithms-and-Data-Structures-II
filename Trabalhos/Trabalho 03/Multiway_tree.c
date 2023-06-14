/*M-way search tree
To mke the processing of m-way tree easier some type of order will be imposed on the keys within each node, 
resulting in a multiway search tree of order m (or an m-way search tree).
By definition an m-way search tree is a m-way tree in which:
1. Each node has maximum of m children and m-1 key fields.
2. The keys in each node are in ascending order.
3. The keys in the first i children are smailer than the ith key.
4. The keys in the last m-i children are larger than the ith key.

With the help of a battery use in the functions Insertion and Deletion in m-way search tree

Insertion in m-way search tree 
1. Insert keys in node till key count == m-1
2. If Node full(no of keys == m-1) insert key to left subtree node whare key k_new < k_parent
3. If Node full(no of keys == m-1) insert key to right subtree node whare key k_new > k_parent
4. Repeat process

Deletion in m-way search tree
Case 1: Deleteion of key with no subtree --> Simply delete key from node
Case 2a: Deleteion of key with left subtree --> Replace largent value from left subtree with value to be deleted. Delete largest value from left subtree.
Case 2b: Deleteion of key with right subtree --> Replace smallest value from right subtree with value to be deleted. Delete smallest value from right subtree.
Case 3: Deleteion of key with both left and right subtree --> Replace smallest value for RST or replace largest value for LST with the key value to be deleted. Then delete this replaced value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3

typedef struct node{
    int key[M-1];
    struct node *child[M];
    int count;
}node;

typedef struct stack{
    node *tree_node; // Ponteiro para o nó na árvore
    int index; // Índice da chave no nó
} stack;

node *root = NULL;

void insertionOrdereKey(node *tree, int key){
    int i = tree->count - 1;
    while(i >= 0 && key < tree->key[i]){
        tree->key[i+1] = tree->key[i];
        i--;
    }
    tree->key[i+1] = key;
    tree->count++;
}

node *splitNode(node *tree, int key){
    int i, j, mid;
    node *newNode, *parent;
    newNode = (node *)malloc(sizeof(node));
    if(key < tree->key[0]){
        mid = 0;
        parent = tree->child[0];
    }else{
        mid = M/2;
        parent = tree->child[M/2];
    }
    for(i = mid+1, j = 0; i < M; i++, j++){
        newNode->key[j] = tree->key[i];
        newNode->child[j] = tree->child[i];
    }
    newNode->child[j] = tree->child[i];
    newNode->count = M - mid - 1;
    tree->count = mid;
    if(key < tree->key[0]){
        insertionOrdereKey(tree, key);
    }else{
        insertionOrdereKey(newNode, key);
    }
    newNode->child[0] = parent;
    return newNode;
}

// Insertion(new, tree, stack, key)
node *insertion(node *tree, int key, stack *pilha){
    int i;
    node *newNode;
    if(tree == NULL){
        tree = (node *)malloc(sizeof(node));
        tree->key[0] = key;
        tree->count = 1;
        for(i = 1; i < M; i++){
            tree->child[i] = NULL;
        }
        tree->child[0] = NULL;
        return tree;
    }
    if(tree->child[0] == NULL){
        if(tree->count < M-1){
            insertionOrdereKey(tree, key);
            return tree;
        }else{
            newNode = splitNode(tree, key);
            return newNode;
        }
    }else{
        if(key < tree->key[0]){
            i = 0;
        }else{
            for(i = tree->count - 1; (key < tree->key[i] && i > 0); i--);
            if(key > tree->key[i]){
                i++;
            }
        }
        pilha->tree_node = tree;
        pilha->index = i;
        pilha++;
        tree->child[i] = insertion(tree->child[i], key, pilha);
        if(tree->child[i] == NULL){
            return tree;
        }else{
            if(tree->count < M-1){
                insertionOrdereKey(tree, tree->child[i]->key[0]);
                tree->child[i] = tree->child[i]->child[0];
                return tree;
            }else{
                newNode = splitNode(tree, tree->child[i]->key[0]);
                tree->child[i] = tree->child[i]->child[0];
                return newNode;
            }
        }
    }
}



int main(){
    int ch, key;
    while(1){
        printf("1. Insertion");
        printf("2. Deletion");
        printf("3. Display");
        printf("4. Exit");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                printf("Enter the key to be inserted: ");
                scanf("%d", &key);
                root = insertion(root, key);
                break;
            case 2:
                printf("Enter the key to be deleted: ");
                scanf("%d", &key);
                root = del(root, key);
                break;
            case 3:
                display(root, 0);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice \n");
        }
    }
    return 0;
}