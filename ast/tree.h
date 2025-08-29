// tree.h
#ifndef TREE_H
#define TREE_H

#include "../common.h"

typedef enum{
    NODE_NUM,
    NODE_DECL,
    NODE_ASIGN,
    NODE_OP,
    NODE_BOOL,
    NODE_TYPE,
    NODE  
}NodeType;

typedef enum{
    suma,
    resta,
    asign,
    divide,
    mult,
    or,
    and
} op;

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
    op name;
    VariableType type;
    union values value;
}infoOp;

typedef struct infoNode{
    char* info;
    VariableType type; 
}infoNode;

union type{
    infoInt NUM;
    infoBool BOOL;
    infoId ID;
    infoOp OP;
    infoNode NODE;
    VariableType NODE_TYPE;
};

typedef struct node{
    NodeType type;
    union type *info;
    struct node *left;
    struct node *right;
}node;

node* createIntNode(int value);
node* createBoolNode(int value);
node *createIdDecl(char *name, VariableType typeVar, NodeType typeNode);
node *createIdExpr(char *name, NodeType typeNode);
node* createOpNode(op name, VariableType type);
node* createTypeNode(VariableType type);
node* createNode(char* name, VariableType type);
node* newNode(NodeType type);
node* createNewTree(node* root, node* left, node* right);
void printNode(node* root);
void printInOrder(node *root);
void printPreOrder(node *root);
void printTree(node* root, int level); 

#endif