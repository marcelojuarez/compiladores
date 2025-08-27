// types.h
#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "common.h"

typedef struct symbol {
    char* name;
    VariableType type;
    int value;
}symbol;

typedef struct symbol_table {
    symbol info;
    struct symbol_table *next;
}symbol_table;

symbol_table* create_symbol_table_of_tree(symbol_table* tree);
void aux_create_symbol_table_of_tree(symbol_table* tree, symbol_table table);
symbol create_symbol(char* name, VariableType type, int value);
int search_symbol(symbol_table *table, char* name);
void insert_symbol(symbol_table **table, symbol s);
void print_symbol_table(symbol_table *table);

#endif