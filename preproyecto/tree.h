// tree.h
#ifndef TREE_H
#define TREE_H

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

node* createIntNode(int value);
node* createBoolNode(int value);
node* createIdNode(char* name);
node* createOpNode(char* name);
node* newNode(NodeType type);
node* createNewTree(node* root, node* left, node* right);
void printNode(node* root);
void printInOrder(node *root);
void printPreOrder(node *root);
void printTree(node* root, int level); 

#endif