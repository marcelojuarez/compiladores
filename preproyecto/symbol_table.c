#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"

symbol_table *createSymbolTable()
{
    symbol_table *head = NULL;
}

symbol_table *insertSymbol(symbol_table *head, union type value)
{
    symbol_table *newSymbol = malloc(sizeof(symbol_table));
    newSymbol->info = malloc(sizeof(union type));
    *(newSymbol->info) = value;
    newSymbol->next = NULL;

    if (head == NULL)
    {
        return newSymbol;
    }
    else
    {
        symbol_table *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newSymbol;
        return head;
    }
}

int main()
{
    symbol_table *table = NULL;
    union type value1, value2, value3;

    value1.NUM.type = TYPE_INT;
    value1.NUM.value = 10;
    value2.NUM.type = TYPE_BOOL;
    value2.NUM.value = 1;
    value3.OP.type = TYPE_INT;
    value3.OP.value.num = asign;

    table = insertSymbol(table, value1);
    table = insertSymbol(table, value2);
    table = insertSymbol(table, value3);

    symbol_table *current = table;
    int i = 1;
    while (current != NULL)
    {
        if (current->info->NUM.type == TYPE_INT)
            printf("Simbolo %d: %d\n", i, current->info->NUM.value);
        else if (current->info->BOOL.type == TYPE_BOOL)
            printf("Simbolo %d: %s\n", i, current->info->BOOL.value ? "true" : "false");
        else
            printf("Simbolo %d: OP %d\n", i, current->info->OP.name);
        current = current->next;
        i++;
    }
    return 0;
}