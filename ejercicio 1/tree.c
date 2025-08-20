#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_NUM,
    NODE_ID,
    NODE_OP,
    NODE_BOOL
} NodeType;

typedef enum {
    INT,
    BOOL
} VariableType;

typedef struct NUM {
    int value;
    char *type;
} NUM;

typedef struct ID {
    char* name;
    VariableType* type;
    union {
        int num;
        int bool_val;
    } value;
} ID;

typedef struct OP {
    char* name;
    char* type;
} OP;

typedef struct BOOL {
    int value;
    char* type;
} BOOL;

union Type {
    NUM num;
    ID id;
    OP op;
    BOOL bool_val;
};

typedef struct Node {
    NodeType type;
    union Type info;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(union Type val, NodeType t, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->type = t;
    n->left = left;
    n->right = right;

    switch (t)
    {
    case NODE_BOOL:
        n->info.bool_val.value = val.bool_val.value;
        break;
    case NODE_ID:
        n->info.id.value = strdup(val.id.value); // Copia segura
        break;
    case NODE_NUM:
        n->info.num.value= val.num.value;
        break;
    case NODE_OP:
        n->info.op.name = val.op.name;
        break;
    default:
        break;
    }
    return n;
}
