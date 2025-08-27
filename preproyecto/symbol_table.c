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
        s.name = root->info->ID.name;
        s.type = root->info->ID.type;
        s.value = root->info->ID.value.num;
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
        if (strcmp(cursor->info.name,name) == 0) {
            return 1;
        }
        cursor = cursor->next;
    }
    return 0;
}

void insert_symbol(symbol_table **table, symbol s){
    if (search_symbol(*table, s.name) == 0){    
        symbol_table *aux = malloc(sizeof(symbol_table));
        aux->info.name = s.name;
        aux->info.type = s.type;
        aux->info.value = s.value;

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
        printf("ID:  %s\n", cursor->info.name);
        switch(cursor->info.type) {
            case TYPE_BOOL:
                printf("TYPE_BOOL\n");
                break;
            case TYPE_INT:
                printf("TYPE_INT\n");
                break;
        }
            
        if (cursor->info.type == TYPE_BOOL) {
            printf(cursor->info.value == 1 ? "true" : "false");
        } else {
            printf("VALUE: %d", cursor->info.value);
        }        
        if (cursor->next != NULL) {
            printf(" ,\n");
        }

        cursor = cursor->next;
    }

    printf(" ]\n");
}

int main(){
    node* nodex = createIdNode("x");
    nodex->info->ID.type = TYPE_BOOL;
    printTree(nodex, 0);

    symbol_table* table = create_symbol_table_of_tree(nodex);

    print_symbol_table(table);

    //node* root = createNewTree(nodex, NULL, NULL);

    /*
    printTree(root, 0);

    printf("\n");

    symbol_table* table = create_symbol_table_of_tree(root);

    print_symbol_table(table);
    */
    return 0;
}