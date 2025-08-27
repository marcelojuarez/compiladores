#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

symbol_table* create_symbol_table_of_tree(symbol_table* tree){
        symbol_table *table = NULL;

        return table;
}

void aux_create_symbol_table_of_tree(symbol_table* tree, symbol_table table) {
    if (tree == NULL) {
        return;
    }

    if (tree->info) {

    }

}

symbol create_symbol(char* name, VariableType type, int value){
    symbol newSymbol;
    newSymbol.name = name;
    newSymbol.type = type;
    newSymbol.value = value;
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
    
    while(cursor != NULL){
        printf("[ ");
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
            printf("VALUE: %d\n", cursor->info.value);
        }        
        printf(" ]\n");
        cursor = cursor->next;
    }
}


int main(){

    return 0;
}