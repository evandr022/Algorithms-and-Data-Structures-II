// implemente uma arvore splay

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct node {
    int key;
    struct node *left, *right;
} node;

node *newNode(int item) {
    node *temp = (node *) malloc(sizeof(node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

node *rightRotate(node *y) {
    node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

node *leftRotate(node *x) {
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

node *splay(node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == NULL) return root;

        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);

            root = rightRotate(root);
        } else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);

            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        if (root->right == NULL) return root;

        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);

            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

node *search(node *root, int key) {
    return splay(root, key);
}

node *insert(node *root, int key) {
    if (root == NULL) return newNode(key);

    root = splay(root, key);

    if (root->key == key) return root;

    node *newnode = newNode(key);

    if (root->key > key) {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    } else {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode;
}

node *deleteNode(node *root, int key) {
    node *temp;
    if (!root) return NULL;

    root = splay(root, key);

    if (key != root->key) return root;

    else {
        if (!root->left) {
            temp = root;
            root = root->right;
        } else {
            temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
        }
        free(temp);
        return root;
    }
}

void preOrder(node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    node *root = NULL;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);
    root = insert(root, 40);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);

    printf("Preorder traversal of the modified Splay tree is \n");
    preOrder(root);

    root = deleteNode(root, 20);
    root = deleteNode(root, 30);
    root = deleteNode(root, 40);
    root = deleteNode(root, 50);

    printf("\nPreorder traversal of the modified Splay tree is \n");
    preOrder(root);

    return 0;
}