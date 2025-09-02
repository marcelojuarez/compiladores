#include <stdio.h>
#include <stdlib.h>
#include "tree.h"



/**
 * Crea un nodo correspondiente a una constante entera
 */
node *create_int_node(int value) {
    node *root = new_node(NODE_NUM);
    root->info->NUM.type = TYPE_INT;
    root->info->NUM.value = value;

    return root;
}

/**
 * Crea un nodo correspondiente a valor booleano
 */
node *create_bool_node(int value) {
    node *root = new_node(NODE_BOOL);
    root->info->BOOL.type = TYPE_BOOL;
    root->info->BOOL.value = value;

    return root;
}

/**
 * Crea un nodo correspondiente a una sentencia de declaracion de un ID
 */
node *create_id_decl_node(char *name, VariableType typeVar, NodeType typeNode) {
    node *root = new_node(typeNode);
    root->info->ID.name = name;
    root->info->ID.type = typeVar;

    return root;
}

/**
 * Crea un nodo correspondiente a una sentencia de uso de un ID
 */
node *create_id_expr_node(char *name, NodeType typeNode) {
    node *root = new_node(typeNode);
    root->info->ID.name = name;

    return root;
}

/**
 * Crea un nodo correspondiente a una sentencia de operacion
 */
node* create_operation_node(OpType name, VariableType type) {
    node *root = new_node(NODE_OP);
    root->info->OP.name = name;
    root->info->OP.type = type;

    return root;
}

/**
 * Crea un nodo que  
 */
node *create_node(char *name, VariableType type) {
    node *root = new_node(NODE);
    root->info->NODE.info = name;
    root->info->NODE.type = type;

    return root;
}

/**
 * Crea un nodo correspondiente a una sentencia de funcion
 */
node* create_function_node(char* name, VariableType returnType) {
    node *root = new_node(NODE_FUNC);
    root->info->FUNC.name = name;
    root->info->FUNC.returnType = returnType;

    return root;
}

/**
 * Crea un nodo correspondiente a una sentencia return
 */
node* create_return_node(VariableType returnType) {
    node *root = new_node(NODE_RET);
    root->info->RET.returnType = returnType;

    return root;
}

/**
 * Recibe un tipo de nodo y lo crea
 * Esta funcion se utiliza para crear nodos de un tipo en especifico
 */
node *new_node(NodeType type) {
    node *root = malloc(sizeof(node));
    root->info = malloc(sizeof(union type));
    root->type = type;
    root->left = NULL;
    root->right = NULL;

    return root;
}

/**
 * Crea un arbol a partir de un nodo raiz y dos sub arboles
 */

node *create_tree(node *root, node *left, node *right) {
    node *newRoot = root;
    newRoot->left = left;
    newRoot->right = right;

    return newRoot;
}

void print_node(node *root) {
    if (!root)
        return;
    switch (root->type) {
        case NODE_NUM:
            printf("%d\n", root->info->NUM.value);
            break;
        case NODE_DECL:
            switch(root->info->ID.type){
                case TYPE_INT:
                    printf("int ");
                    break;
                case TYPE_BOOL:
                    printf("bool ");
                    break;
                case NONE:
                    printf("none ");
                    break;
            }
            printf("%s\n", root->info->ID.name ? root->info->ID.name : "NULL");
            break;
        case NODE_ID_USE:
            printf("%s\n", root->info->ID.name ? root->info->ID.name : "NULL");
            break;
        case NODE_BOOL:
            printf("%s\n", root->info->BOOL.value ? "true" : "false");
            break;
        case NODE_FUNC:
            switch(root->info->FUNC.returnType) {
                case TYPE_INT:
                    printf("int ");
                    printf("%s \n", root->info->FUNC.name);
                    break;
                case TYPE_BOOL:
                    printf("bool ");
                    printf("%s \n", root->info->FUNC.name);
                    break; 
                case NONE:
                    printf("void ");
                    printf("%s \n", root->info->FUNC.name);
                    break;
            }
            break;
        case NODE_OP:
            switch (root->info->OP.name) {
            case OP_ADD:
                printf("+\n");
                break;
            case OP_SUB:
                printf("-\n");
                break;
            case OP_MULT:
                printf("*\n");
                break;
            case OP_DIV:
                printf("/\n");
                break;
            case OP_ASSIGN:
                printf("=\n");
                break;
            case OP_OR:
                printf("||\n");
                break;
            case OP_AND:
                printf("&&\n");
                break;
            default:
                printf("OP?\n");
            }
            break;
        case NODE:
             printf("%s\n", root->info->NODE.info ? root->info->NODE.info : "NULL");
            break;
        case NODE_RET:
            printf("ret \n");
            break;
        default:
            printf("UNKNOWN NODE\n");
            break;
        }
}

/**
 * Funcion de entrada que se encarga de imprimir el arbol
 */

void print_tree(node *root, int level) {
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++){
        printf("   ");
    }

    print_node(root);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}
