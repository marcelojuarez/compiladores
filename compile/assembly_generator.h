#ifndef ASEEMBLY_GENERATOR_H
#define ASEEMBLY_GENERATOR_H

#include "tree.h"
#include "symbol_table.h"
#include <stdio.h>

void generate_assembly(node* root);
void write_assembly(node* root, FILE* f);
void gen_expr(node* root, FILE* f);

#endif
