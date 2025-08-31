#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "tree.h"

symbol_table* create_symbol_table_of_tree(node* root){
        symbol_table *table = NULL;
        aux_create_symbol_table_of_tree(root, &table);
        return table;
}

void aux_create_symbol_table_of_tree(node* root, symbol_table** table) {
    if (root == NULL) {
        return;
    }

    symbol s; 
    if (root->type == NODE_DECL || root->type == NODE_FUNC) {

        // Un nodo declaracion se agrega a la tabla de simbolos

        s.info = root->info;
        //printf("inserto %s en la tabla de simbolos con: %d \n", root->info->ID.name, root->info->ID.type);
        insert_symbol(table, s, root->type);  

    } else if (root->type == NODE_ID_USE) {

        // Un nodo uso se verifica que este en la tabla de simbolos

        s.info = search_symbol(*table, root->info->ID.name);

        if (s.info == NULL) {
            printf("Symbol %s not found.\n", root->info->ID.name);
            exit(EXIT_FAILURE);   
        }
        // Se actualiza la informacion del nodo con la info que esta en la tabla
        root->info = s.info;
    }

    aux_create_symbol_table_of_tree(root->left, table);
    aux_create_symbol_table_of_tree(root->right, table);
}

union type* search_symbol(symbol_table *table, char* name){
    if (table == NULL) {
        return NULL;
    }
    symbol_table *cursor = table;
    while(cursor != NULL) {
        if (strcmp(cursor->s.info->ID.name, name) == 0) {
            return cursor->s.info;
        }
        cursor = cursor->next;
    }
    return NULL;
}

void insert_symbol(symbol_table **table, symbol s, NodeType nodeType){
    if (search_symbol(*table, s.info->ID.name) == NULL){
        symbol_table *aux = malloc(sizeof(symbol_table));
        aux->s.info = s.info;
        aux->nodeType = nodeType;

        if (*table == NULL) {
            *table = aux;
        } else {
            aux->next = *table;
            *table = aux;
        }
    } else {
        printf("error, variable already exists\n");
        exit(EXIT_FAILURE);
    }
}

void print_symbol_table(symbol_table *table){
    if (table == NULL) {
        printf(" ");
        return;
    }
    symbol_table *cursor = table;
    printf("-----\n");
    while(cursor != NULL){
        if (cursor->nodeType == NODE_DECL ||cursor->nodeType == NODE_ID_USE) {
            printf("ID:  %s\n", cursor->s.info->ID.name);
            switch(cursor->s.info->ID.type) {
                case TYPE_BOOL:
                    printf("TYPE: BOOL");
                    break;
                case TYPE_INT:
                    printf("TYPE: INT");
                    break;
                case NONE:
                    printf("TYPE: NONE");
                    break;
            }    
        } else {
            printf("FUNC:  %s\n", cursor->s.info->FUNC.name);
            switch(cursor->s.info->FUNC.returnType){
                case TYPE_BOOL:
                    printf("RETURN_TYPE: BOOL");
                    break;
                case TYPE_INT:
                    printf("RETURN_TYPE: INT");
                    break;
                case NONE:
                    printf("RETURN_TYPE: NONE");
                    break;
            }       
        }
 
        if (cursor->next != NULL) {
            printf("\n-----\n");
        }
        cursor = cursor->next;
    }
    printf("\n-----\n");
}

/*
int main(){
    node* nodex = createIdNode("x");
    nodex->info->ID.type = TYPE_BOOL;
    printTree(nodex, 0);

    symbol_table* table = create_symbol_table_of_tree(nodex);

    print_symbol_table(table);

    //node* root = createNewTree(nodex, NULL, NULL);

    
    printTree(root, 0);

    printf("\n");

    symbol_table* table = create_symbol_table_of_tree(root);

    print_symbol_table(table);
    
    return 0;
}

*/
