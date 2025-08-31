#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"
#include "expr_solver.h"
#include "common.h"

int expr_solver(node* root, symbol_table* table) {
    if (root == NULL) return 0;
    printf("%d\n",root->type);

    switch (root->type) {
        case NODE_NUM:
            return root->info->NUM.value;

        case NODE_BOOL:
            return root->info->BOOL.value;

        case NODE_ID: { // Esto puede ser que no sea necesario
            union type* var = search_symbol(table, root->info->ID.name);
            if (var->ID.type == TYPE_BOOL) {
                return var->ID.value.boolean;
            } else {
                return var->ID.value.num;
            }
        }
        case NODE_ASIGN:
            union type* var = search_symbol(table, root->info->ID.name);
            if (var->ID.type == TYPE_BOOL) {
                return var->ID.value.boolean;
            } else {
                return var->ID.value.num;
            }
        case NODE_OP: {
            int left_value  = expr_solver(root->left,  table);
            int right_value = expr_solver(root->right, table);

            switch (root->info->OP.name) {
                case suma:   
                    return left_value + right_value;
                case resta:  
                    return left_value - right_value;
                case mult:   
                    return left_value * right_value;
                case divide:
                    if (right_value == 0) {
                        fprintf(stderr, "Math error: división por cero\n");
                        exit(1);
                    }
                    return left_value / right_value;

                case and:    
                    return left_value && right_value;
                case or:     
                    return left_value || right_value;

                default:
                    fprintf(stderr, "Error: operador no definido\n");
                    exit(1);
            }
        }
        case NODE:
            return expr_solver(root->left, table);
            break;

        default:
            fprintf(stderr, "Error: no es expresión\n");
            exit(1);
    }
}

void execute_tree(node* root, symbol_table* table) {
    if (root == NULL) {
        return;
    }

    if (root->type == NODE_OP && root->info->OP.name == asign) {
        if (root->left != NULL && root->left->info != NULL) {
            char* var_name = root->left->info->ID.name;
            
            int value = expr_solver(root->right, table);
            
            update_symbol_value(table, var_name, value);
        }
    }
    execute_tree(root->left, table);
    execute_tree(root->right, table);
}

void update_symbol_value(symbol_table* table, char* name, int value) {
    union type* v = search_symbol(table, name);
    if (!v) {
        fprintf(stderr, "Error: variable '%s' no declarada\n", name);
        return;
    }
    switch (v->ID.type) {
        case TYPE_INT:
            v->ID.value.num = value;
            break;

        case TYPE_BOOL:
            v->ID.value.boolean = (value != 0);
            break;

        default:
            fprintf(stderr, "Error: tipo no soportado en asignación\n");
            return;
    }
}