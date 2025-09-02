#include "assembly_generator.h"
#include <string.h>

/**
 * Funcion principal que se encarga de traducir el ast a un pseudo assembler
 */

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
    char buffer[256];
    snprintf(buffer, sizeof(buffer), ".global\n");
    fputs(buffer, f);
    write_assembly(root, f);
    fclose(f);
}

/**
 * Realiza la traduccion segun el tipo de nodo que esta leyendo
 */

void write_assembly(node* root, FILE* f) {
    if (root == NULL) return;

    switch (root->type) {
        case NODE_DECL:
            fprintf(f, "    DECL %s\n", root->info->ID.name);
            break;

        case NODE_OP:
            if (root->info->OP.name == OP_ASSIGN) {
                if (root->left->type == NODE_DECL) {
                    char* var_name = root->left->info->ID.name;
                    fprintf(f, "    DECL %s\n", var_name);
                    gen_expr(root->right, f);
                    fprintf(f, "    STORE %s\n", var_name);
                }else {
                    char* var_name = root->left->info->ID.name;
                    gen_expr(root->right, f);
                    fprintf(f, "    STORE %s\n", var_name);
                }
            }
            break;
        case NODE_RET: {
            gen_expr(root->left, f);
            fprintf(f, "    RET\n");
            break;
        }
        default:
            write_assembly(root->left, f);
            write_assembly(root->right, f);
            break;
    }
}

/**
 * Se encarga de traducir al pseudo assembler cada posible expresion del programa
 */

void gen_expr(node* root, FILE* f) {
    if (root == NULL) return;

    switch (root->type) {
        case NODE_NUM: {
            fprintf(f, "    PUSH %d\n", root->info->NUM.value);
            break;
        }
        case NODE_BOOL: {
            fprintf(f, "    PUSH %d\n", root->info->BOOL.value);
            break;
        }
        case NODE_ID_USE: {
            fprintf(f, "    LOAD %s\n", root->info->ID.name);
            break;
        }
        case NODE_OP: {
            gen_expr(root->left, f);
            gen_expr(root->right, f);

            switch (root->info->OP.name) {
                case OP_ADD:
                    fprintf(f, "    ADD\n");
                    break;
                case OP_SUB:
                    fprintf(f, "    SUB\n");
                    break;
                case OP_MULT:
                    fprintf(f, "    MUL\n");
                    break;
                case OP_DIV:
                    fprintf(f, "    DIV\n");
                    break;
                case OP_AND:
                    fprintf(f, "    AND\n");
                    break;
                case OP_OR:
                    fprintf(f, "    OR\n");
                    break;
                default:
                    fprintf(stderr, "Operador no soportado en gen_expr\n");
                    break;
            }
            break;
        }
        default:
            // Nodos que se omiten
            break;
    }
}


