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
    if (root->type == NODE_DECL) {
        
        s.info = root->info;
        insert_symbol(table, s);  
    } else if (root->type == NODE_ASIGN) {
        s.info = search_symbol(*table, root->info->ID.name);
        if (s.info == NULL) {
            printf("Symbol %s not found.\n", root->info->ID.name);
            return;
        }
    } else if(root->type == NODE_NUM) {
        s.info->NUM.value = root->info->NUM.value;
        return;
    }
    aux_create_symbol_table_of_tree(root->left, table);
    aux_create_symbol_table_of_tree(root->right, table);
}

union type* search_symbol(symbol_table *table, char* name){
    if (table == NULL) {
        return NULL;
    }
    symbol_table *cursor = table;
    while(cursor->next != NULL) {
        if (strcmp(cursor->s.info->ID.name, name) == 0) {
            return cursor->s.info;
        }
        cursor = cursor->next;
    }
    return NULL;
}

void insert_symbol(symbol_table **table, symbol s){
    if (search_symbol(*table, s.info->ID.name) == NULL){    
        symbol_table *aux = malloc(sizeof(symbol_table));
        aux->s.info = s.info;

        if (*table == NULL) {
            *table = aux;
        } else {
            aux->next = *table;
            *table = aux;
        }
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
        printf("ID:  %s\n", cursor->s.info->ID.name);
        switch(cursor->s.info->ID.type) {
            case TYPE_BOOL:
                printf("TYPE: BOOL");
                break;
            case TYPE_INT:
                printf("TYPE: INT");
                break;
        }
        /*
        if (cursor->s.info->ID.type == TYPE_BOOL) {
            printf(cursor->s.info->ID.value.num == 1 ? "true" : "false");
        } else {
            printf("VALUE: %d", cursor->s.info->ID.value.num);
        } 
        */   
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
