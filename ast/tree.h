// tree.h
#ifndef TREE_H
#define TREE_H

#include "../common.h"

/* Tipos de nodos del ast */
typedef enum {
    NODE_FUNC,
    NODE_NUM,
    NODE_DECL,
    NODE_ID_USE,
    NODE_OP,
    NODE_BOOL,
    NODE_RET,
    NODE  
}NodeType;

/* Tipos de operaciones */
typedef enum {
    OP_ADD,
    OP_SUB, 
    OP_ASSIGN,
    OP_DIV,
    OP_MULT,
    OP_OR,
    OP_AND
} OpType;

union values{
    int num;
    int boolean;
};

typedef struct IntInfo {
    VariableType type;
    int value;
} IntInfo;  

typedef struct BoolInfo {
    VariableType type;
    int value;
} BoolInfo; 

typedef struct IdInfo {
    char* name;
    VariableType type;
    union values value;
} IdInfo;

typedef struct OpInfo {
    OpType name;
    VariableType type;
    union values value;
} OpInfo;

typedef struct NodeInfo {
    char* info;
    VariableType type; 
} NodeInfo;

typedef struct FunctionInfo {
    char* name;
    VariableType returnType;
    union values value;
} FunctionInfo;

typedef struct ReturnInfo {
    VariableType returnType;
    union values value;
} ReturnInfo;

/* Info que llevan los nodos */
union type {
    IntInfo NUM;
    BoolInfo BOOL;
    IdInfo ID;
    OpInfo OP;
    NodeInfo NODE;
    FunctionInfo FUNC;
    ReturnInfo RET;
};

/*Estructura de los nodos del ast*/
typedef struct node {
    NodeType type;
    union type *info;
    struct node *left;
    struct node *right;
} node;


/* Contructores de nodos */
node* create_int_node(int value);
node* create_bool_node(int value);
node* create_id_decl_node(char *name, VariableType typeVar, NodeType typeNode);
node* create_id_expr_node(char *name, NodeType typeNode);
node* create_operation_node(OpType name, VariableType type);
node* create_node(char* name, VariableType type);
node* create_function_node(char* name, VariableType returnType);
node* create_return_node(VariableType returnType);
node* new_node(NodeType type);
node* create_tree(node* root, node* left, node* right);
void print_node(node* root);
void print_tree(node* root, int level); 

#endif