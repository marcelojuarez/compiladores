#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symbol_table.h"
#include "expr_solver.h"
#include "type_checker.h"
#include "assembly_generator.h"

int yyparse(void);
extern FILE* yyin;
extern node* root;
extern int yylineno;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s archivo\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    yyin = input_file;
    yylineno = 1;
    if (yyparse() == 0) {
        printf("Parseado correctamente, sin errores.\n");

        print_tree(root, 0);

        symbol_table* table = create_symbol_table_of_tree(root);
        print_symbol_table(table);

        run_type_checker(root);

        execute_tree(root, table);
        print_symbol_table(table);

        generate_assembly(root); 
    }

    fclose(input_file);
    return 0;
}
