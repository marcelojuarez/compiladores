#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"


VariableType return_types(node* root){
    if(root == NULL) {
        return NONE;
    }

    if (root->left == NULL && root->right == NULL) {
        switch(root->type) {
            case NODE_NUM:
                printf("simbolo %d: ", root->info->NUM.value);
                printf("tipo:  %d \n", root->info->NUM.type);
                return root->info->NUM.type;
                break;
            case NODE_BOOL:
                printf("simbolo %d: ", root->info->BOOL.value);
                printf("tipo:  %d \n", root->info->BOOL.type);
                return root->info->BOOL.type;
                break;
            case NODE_ID_USE:
                printf("simbolo %s: ", root->info->ID.name);
                printf("tipo  %d \n", root->info->ID.type);
                return root->info->ID.type;
                break;
            case NODE_DECL:
                printf("simbolo %s: ", root->info->ID.name);
                printf("tipo  %d \n", root->info->ID.type);
                return root->info->ID.type;
                break;
            default:
                printf("Entro por default \n");
                break;
        }
    }

    if (root->left != NULL && root->right == NULL) {
       return return_types(root->left);
    }

    if (root->left == NULL && root->right != NULL) {
        return return_types(root->right);
    }

    if (root->left != NULL && root->right != NULL) {
        VariableType left = return_types(root->left);
        VariableType right = return_types(root->right);

        printf(" %d == %d ?", left, right);

        if (right == left){
            printf("Sin error de tipos \n");
            return right;
        } else {
            printf("Tipos incompatibles\n");
            exit(EXIT_FAILURE); 
        }
    }
    printf("Llegue aca y retorno NONE \n");
    return NONE;
}

void check_types(node* root) {
    if (root == NULL) {
        return;
    }

    if (root->type == NODE_OP) {
        switch (root->info->OP.name) {
            case suma:
                printf("Entro por la operacion SUMA\n");
                break;
            case resta:
                printf("Entro por la operacion RESTA\n");
                break;
            case asign:
                printf("Entro por la operacion ASIGNACION\n");
                break;
            case divide:
                printf("Entro por la operacion DIVISION\n");
                break;
            case mult:
                printf("Entro por la operacion MULTIPLICACION\n");
                break;
            case or:
                printf("Entro por la operacion OR\n");
                break;
            case and:
                printf("Entro por la operacion AND\n");
                break;
            default:
                printf("Operacion DESCONOCIDA\n");
                break;
        }

        VariableType typeNode = return_types(root);

        switch(typeNode){
            case TYPE_INT:
                printf("Operacion entera \n");
                break;
            case TYPE_BOOL:
                printf("Operacion booleana \n");
                break;
            case NONE:
                printf("no tiene tipo \n");
                break;
        }
    } else {
        //printf("No hay operaciones \n");
        check_types(root->left);
        check_types(root->right);
    }
}


