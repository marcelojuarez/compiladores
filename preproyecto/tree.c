#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node* createIntNode(int value) {
    node *root = malloc(sizeof(node));
    root->type = NODE_NUM;
    root->info.NUM.type = TYPE_INT; 
    root->info.NUM.value = value;

    root->left = NULL;  // asigno a hi
    root->right = NULL; // asigno a hd

    return root;
}

node* createBoolNode(int value) {
    node *root = malloc(sizeof(node));
    root->type = NODE_BOOL;
    root->info.BOOL.type = TYPE_BOOL; 
    root->info.BOOL.value = value;

    root->left = NULL;  // asigno a hi
    root->right = NULL; // asigno a hd

    return root;
}

node* createIdNode(char* name) {
    node *root = malloc(sizeof(node));
    root->type = NODE_ID;
    root->info.ID.name = name;
    root->left = NULL;  // asigno a hi
    root->right = NULL; // asigno a hd

    return root;
}

node* createOpNode(char* name) {
    node *root = malloc(sizeof(node));
    root->type = NODE_OP;
    root->info.OP.name = name;

    root->left = NULL; // asigno a hi
    root->right = NULL; // asigno a hd

    return root;
}

node* createNewTree(node* root, node* left, node* right){
    node *newRoot = root;
    newRoot->left = left;
    newRoot->right = right;
    return newRoot;
}

void printNode(node* root) {
    switch (root->type) {
        case NODE_NUM:
            printf("%d \n", root->info.NUM.value);
            break;
        case NODE_ID:
            printf("%s \n", root->info.ID.name);
            break;
        case NODE_BOOL:
            printf("%s \n", root->info.BOOL.value ? "true" : "false");
            break;
        case NODE_OP:
            printf("%s \n", root->info.OP.name);
            break;
 
    }
}

 void printInOrder(node *root) {
     if (root == NULL) {
        return;
     }

    printInOrder(root->left);

    printNode(root);

    printInOrder(root->right);
}

 void printPreOrder(node *root) {
     if (root == NULL) {
        return;
     }
    
    printNode(root);

    printPreOrder(root->left);

    printInOrder(root->right);
}

void printTree(node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("   ");  
    }

    printNode(root);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

/**
int main() {
    
    node* num = createIntNode(3);
    node* num1 = createIntNode(5);
    
    node* op = createOpNode("+");

    node* tree = createNewTree(op, num, num1);

    printf("Recorrido InOrder:\n");
    printInOrder(tree);

    return 0;

}
*/

