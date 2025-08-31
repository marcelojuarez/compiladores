#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"


VariableType check_exp_types(node* root) {
    if (root == NULL) {
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
       return check_exp_types(root->left);
    }

    if (root->left == NULL && root->right != NULL) {
        return check_exp_types(root->right);
    }

    if (root->left != NULL && root->right != NULL) {
        
        printf("Entro a ver los tipos \n");
        VariableType leftType = check_exp_types(root->left);
        VariableType rightType = check_exp_types(root->right);
        printf("Salgo de ver los tipos \n");

        switch (root->info->OP.name) {
            
            case suma:
            case resta:
            case divide:
            case mult:
                printf("Operacion aritmetica\n");
                if(leftType != TYPE_INT || rightType != TYPE_INT) {
                    printf("Error de tipos. Requiere tipo entero\n");
                    exit(EXIT_FAILURE); 
                }

                root->info->OP.type = leftType;
                return leftType;
                break;

            case asign:
                printf("Operacion de asignacion\n");
                if(leftType != rightType) {
                    printf("Error de tipos. Tipos incompatible\n");
                    exit(EXIT_FAILURE); 
                }
                root->info->OP.type = leftType;
                return leftType;
                break;   
            case or:
            case and:
                printf("Operacion booleana\n");
                if(leftType != TYPE_BOOL || rightType!= TYPE_BOOL) {
                    printf("Error de tipos. Requiere tipo booleano\n");
                    exit(EXIT_FAILURE); 
                }
                root->info->OP.type = leftType;
                return leftType;
                break;
            default:
                printf("Operacion DESCONOCIDA\n");
                return leftType;
                break;
        }
        
    }
    printf("Error\n");
    exit(EXIT_FAILURE); 
}

char* VariableTypeToString(VariableType type){
    switch(type){
        case TYPE_INT:
            return "INT";
            break;
        case TYPE_BOOL:
            return "BOOL";
            break; 
        case NONE:
            return "VOID";
            break;
    }
}

void check_return_types(node* root, VariableType f_returnType){
    if (root == NULL ) {
        return ;
    }

    if (root->type == NODE_RET) {
        VariableType retType = check_exp_types(root);
       if ( retType !=  f_returnType) {
            printf("ERROR - tipo de retorno incompatible\n");
            printf("%s f \n", VariableTypeToString(f_returnType));
            printf("return expr: %s\n", VariableTypeToString(retType));
            exit(EXIT_FAILURE);
        }
        //printf("\n");
    } else {
        check_return_types(root->left, f_returnType);
        check_return_types(root->right, f_returnType);
    }
}

void check_types(node* root) {
    if (root == NULL) {
        return;
    }

    if (root->type == NODE_FUNC) {
        if (root->info->FUNC.returnType != NONE) {
           check_return_types(root, root->info->FUNC.returnType);
        }
    } 
    
    if (root->type == NODE_OP) {
        check_exp_types(root);
    } else {
        check_types(root->left);
        check_types(root->right);
    }    
    
}
