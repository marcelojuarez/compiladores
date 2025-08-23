#include <stdio.h>
#include <stdlib.h>

typedef enum{
    NODE_NUM,
    NODE_ID,
    NODE_OP,
    NODE_BOOL    
}NodeType;

typedef enum {
    TYPE_INT,
    TYPE_BOOL
} VariableType;

union values{
    int num;
    int boolean;
};

typedef struct infoInt{
    VariableType type;
    int value;
}infoInt;  

typedef struct infoBool{
    VariableType type;
    int value;
}infoBool; 

typedef struct infoId{
    char* name;
    VariableType type;
    union values value;
}infoId;

typedef struct infoOp{
    char* name;
    VariableType type;
    union values value;
}infoOp;

union type{
    infoInt NUM;
    infoBool BOOL;
    infoId ID;
    infoOp OP;
};

typedef struct node{
    NodeType type;
    union type info;
    struct node *left;
    struct node *right;
}node;

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

int main() {
    
    node* num = createIntNode(3);
    node* num1 = createIntNode(5);
    
    node* op = createOpNode("+");

    node* tree = createNewTree(op, num, num1);

    printf("Recorrido InOrder:\n");
    printInOrder(tree);

    return 0;

}

