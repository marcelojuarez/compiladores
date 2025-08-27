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

    if (root->type == NODE_ID) {
        symbol s; 
        s.info = malloc(sizeof(symbol));
        s.info->ID.name = root->info->ID.name;
        s.info->ID.type = root->info->ID.type;
        s.info->ID.value.num = root->info->ID.value.num;
        insert_symbol(table, s);
    }

    aux_create_symbol_table_of_tree(root->left, table);
    aux_create_symbol_table_of_tree(root->right, table);
}

int search_symbol(symbol_table *table, char* name){
    if (table == NULL) {
        return 0;
    }

    symbol_table *cursor = table;

    while(cursor != NULL) {
        if (strcmp(cursor->s.info->ID.name, name) == 0) {
            return 1;
        }
        cursor = cursor->next;
    }
    return 0;
}

void insert_symbol(symbol_table **table, symbol s){
    if (search_symbol(*table, s.info->ID.name) == 0){    
        symbol_table *aux = malloc(sizeof(symbol_table));
        aux->s.info = malloc(sizeof(symbol));
        aux->s.info->ID.name = s.info->ID.name;
        aux->s.info->ID.type = s.info->ID.type;
        aux->s.info->ID.value.num = s.info->ID.value.num;

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
    
    printf("[ ");

    while(cursor != NULL){
        printf("ID:  %s\n", cursor->s.info->ID.name);
        switch(cursor->s.info->ID.type) {
            case TYPE_BOOL:
                printf("TYPE_BOOL\n");
                break;
            case TYPE_INT:
                printf("TYPE_INT\n");
                break;
        }
            
        if (cursor->s.info->ID.type == TYPE_BOOL) {
            printf(cursor->s.info->ID.value.num == 1 ? "true" : "false");
        } else {
            printf("VALUE: %d", cursor->s.info->ID.value.num);
        }        
        if (cursor->next != NULL) {
            printf(" ,\n");
        }

        cursor = cursor->next;
    }

    printf(" ]\n");
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
