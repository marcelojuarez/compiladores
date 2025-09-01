#include "assembly_generator.h"
#include <string.h>

void generate_assembly(node* root) {
    FILE* f = fopen("compile/assembly.txt", "w");
    if (f == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    if (root == NULL) {
        fprintf(stderr, "No hay código para generar.\n");
        fclose(f);
        return;
    }

    write_assembly(root, f);
    fclose(f);
}

void write_assembly(node* root, FILE* f) {
    if (root == NULL) return;

    switch (root->type) {
        case NODE_DECL: {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "DECL %s\n", root->info->ID.name);
            fputs(buffer, f);
            break;
        }
    }

    write_assembly(root->left, f);
    write_assembly(root->right, f);
}
