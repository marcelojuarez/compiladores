
#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "common.h"
#include "tree.h"

typedef struct symbol {
    union type *info;
} symbol;

typedef struct symbol_table {
    NodeType nodeType;
    symbol s;
    struct symbol_table *next;
} symbol_table;

symbol_table* create_symbol_table_of_tree(node* tree);
void aux_create_symbol_table_of_tree(node* tree, symbol_table **table);
union type*  search_symbol(symbol_table *table, char* name);
void insert_symbol(symbol_table **table, symbol s, NodeType node);
void check_vars(node* tree, symbol_table* table);
void print_symbol_table(symbol_table *table);

#endif