#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {
    NODE_NUM,
    NODE_ID,
    NODE_OP,
    NODE_BOOL,
    NODE  
} NodeType;

typedef enum{
    suma,
    resta,
    asign,
    divide,
    mult,
    op_or,
    op_and
} op;

typedef enum {
    TYPE_INT,
    TYPE_BOOL
} VariableType;

union values {
    int num;
    int boolean;
};

typedef struct infoInt {
    VariableType type;
    int value;
} infoInt;  

typedef struct infoBool {
    VariableType type;
    int value;
} infoBool; 

typedef struct infoId {
    char* name;
    VariableType type;
    union values value;
} infoId;

typedef struct infoOp {
    op name;
    VariableType type;
    union values value;
} infoOp;

union type {
    infoInt NUM;
    infoBool BOOL;
    infoId ID;
    infoOp OP;
    char* NODE;
};

typedef struct symbol_table {
    union type *info;
    struct symbol_table *next;
} symbol_table;

symbol_table* createSymbolTable();
symbol_table *insertSymbol(symbol_table *head, union type value);

#endif