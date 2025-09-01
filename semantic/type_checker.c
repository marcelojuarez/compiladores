#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"

/**
 * Realiza el chequeo de tipos de las distintas operaciones
 */
VariableType check_exp_types(node* root) {
    if (root == NULL) {
        return NONE;
    }

    if (root->left == NULL && root->right == NULL) {
        switch(root->type) {
            case NODE_NUM:
                return root->info->NUM.type;
                break;
            case NODE_BOOL:
                return root->info->BOOL.type;
                break;
            case NODE_ID_USE:
                return root->info->ID.type;
                break;
            case NODE_DECL:
                return root->info->ID.type;
                break;
            default:
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
        
        VariableType leftType = check_exp_types(root->left);
        VariableType rightType = check_exp_types(root->right);

        switch (root->info->OP.name) {
            
            case OP_ADD:
            case OP_SUB:
            case OP_DIV:
            case OP_MULT:

                if(leftType != TYPE_INT || rightType != TYPE_INT) {
                    printf("Error de tipos. Requiere tipo entero\n");
                    exit(EXIT_FAILURE); 
                }

                root->info->OP.type = leftType;
                return leftType;
                break;

            case OP_ASSIGN:

                if(leftType != rightType) {
                    printf("Error de tipos. Tipos incompatible\n");
                    exit(EXIT_FAILURE); 
                }
                root->info->OP.type = leftType;
                return leftType;
                break;   
            case OP_OR:
            case OP_AND:

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

/** 
 * Devuelve un string por cada valor del enumerado VariableType 
 * Utilizado para mostrar resultados mas claros 
 */
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
    } else {
        check_return_types(root->left, f_returnType);
        check_return_types(root->right, f_returnType);
    }
}

/**
 * Funcion principal que se encarga de comenzar el cheque de tipos
 */

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

/**
 * Funcion de entrada para chequeo de tipos
 */

void run_type_checker(node* root) {

    if (root == NULL) {
        printf("Arbol vacío. No hay nada que chequear.\n");
        return;
    } 

    printf("\n----- Iniciando chequeo de tipos ----- \n");

    check_types(root);

    printf("\nChequeo de tipos correcto \n");

    printf("\n----- Fin del chequeo de tipos ----- \n");
}
