#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node *createIntNode(int value) {
    node *root = newNode(NODE_NUM);
    root->info->NUM.type = TYPE_INT;
    root->info->NUM.value = value;

    return root;
}

node *createBoolNode(int value) {
    node *root = newNode(NODE_BOOL);
    root->info->BOOL.type = TYPE_BOOL;
    root->info->BOOL.value = value;

    return root;
}

node *createIdDecl(char *name, VariableType typeVar, NodeType typeNode) {
    node *root = newNode(typeNode);
    root->info->ID.name = name;
    root->info->ID.type = typeVar;

    return root;
}

node *createIdExpr(char *name, NodeType typeNode) {
    node *root = newNode(typeNode);
    root->info->ID.name = name;

    return root;
}

node *createOpNode(op name, VariableType type) {
    node *root = newNode(NODE_OP);
    root->info->OP.name = name;
    root->info->OP.type = type;
    return root;
}

node* createTypeNode(VariableType type){
    node* root = newNode(NODE_TYPE);
    root->info->NODE_TYPE = type;

    return root;
}

node *createNode(char *name, VariableType type) {
    node *root = newNode(NODE);
    root->info->NODE.info = name;
    root->info->NODE.type = type;

    return root;
}

node *newNode(NodeType type) {
    node *root = malloc(sizeof(node));
    root->info = malloc(sizeof(union type));
    root->type = type;
    root->left = NULL;  // asigno a hi
    root->right = NULL; // asigno a hd

    return root;
}

node *createNewTree(node *root, node *left, node *right) {
    node *newRoot = root;
    newRoot->left = left;
    newRoot->right = right;
    return newRoot;
}

void printNode(node *root) {
    if (!root)
        return;
    switch (root->type) {
        case NODE_NUM:
            printf("%d\n", root->info->NUM.value);
            break;
        case NODE_DECL:
            printf("%s\n", root->info->ID.name ? root->info->ID.name : "NULL");
            break;
        case NODE_ASIGN:
            printf("%s\n", root->info->ID.name ? root->info->ID.name : "NULL");
            break;
        case NODE_BOOL:
            printf("%s\n", root->info->BOOL.value ? "true" : "false");
            break;
        case NODE_TYPE:
            switch(root->info->NODE_TYPE) {
                case TYPE_INT:
                    printf("INT\n");
                    break;
                case TYPE_BOOL:
                    printf("BOOL\n");
                    break; 
                default:
                    break;
            }
            break;
        case NODE_OP:
            switch (root->info->OP.name) {
            case suma:
                printf("+\n");
                break;
            case resta:
                printf("-\n");
                break;
            case mult:
                printf("*\n");
                break;
            case divide:
                printf("/\n");
                break;
            case asign:
                printf("=\n");
                break;
            case or:
                printf("||\n");
                break;
            case and:
                printf("&&\n");
                break;
            default:
                printf("OP?\n");
            }
            break;
        case NODE:
             printf("%s\n", root->info->NODE.info ? root->info->NODE.info : "NULL");
            break;
        default:
            printf("UNKNOWN NODE\n");
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

void printTree(node *root, int level) {
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++){
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

    node* op = createOpNode(suma);

    node* tree = createNewTree(op, num, num1);

    printf("Recorrido InOrder:\n");
    printInOrder(tree);

    return 0;

}
*/
