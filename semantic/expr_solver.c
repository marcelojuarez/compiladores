#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"
#include "common.h"

int expr_solver(node* root, symbol_table* table) {
    if (root == NULL) {
        return 0;
    }

    switch (root->type) {
        case NODE_NUM:
            return root->info->NUM.value;

        case NODE_BOOL:
            return root->info->BOOL.value;

        case NODE_OP:
            int left_value = expr_solver(root->left, table);
            int right_value = expr_solver(root->right, table);

            switch (root->info->OP.type) {
                case suma: return left_value + right_value;
                case resta: return left_value - right_value;
                case mult: return left_value * right_value;
                case divide: return right_value != 0 ? left_value / right_value : (printf("Math error. Cannot divide by zero."));
                
                case and: return left_value && right_value;
                case or: return left_value || right_value;
                
                default:
                    printf("Error: operation not defined.");
                    break;
                }

        case NODE_ASIGN:
            symbol* s = search_symbol(table, root->info->ID.name);
            if (s == NULL) {
                printf("Error: variable not declared.");
            }
            if (s->info == NODE_BOOL) {
                return s->info->BOOL.value;
            } else {
                return s->info->NUM.value;
            }
    } 
}