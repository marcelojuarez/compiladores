#ifndef EXPR_SOLVER_H
#define EXPR_SOLVER_H

#include "tree.h"
#include "symbol_table.h"

int expr_solver(node* root, symbol_table* table);
void update_symbol_value(symbol_table* table, char* name, int value);
void execute_tree(node* root, symbol_table* table);

#endif
