#include "assembly_generator.h"
#include <string.h>

void generate_assembly(node* root) {
    FILE* f = fopen("compile/assembly.txt", "w");
    if (f == NULL) {
        printf("No se pudo abrir el archivo");
    }

    if (root == NULL) {
        printf("No hay codigo para generar.");
    }
    write_assembly(root, f);
    fclose(f);
}

void write_assembly(node* root, FILE* f) {
    switch (root->type) {
        case NODE_DECL:
            char* string = strcat("DECL", root->info->ID.name);
            fputs("string", f);
            break;
    }
}