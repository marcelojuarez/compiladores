#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H

#include "tree.h"

VariableType check_exp_types(node* root);
void check_return_types(node* root, VariableType f_returnType);
char* VariableTypeToString(VariableType type);
void check_types(node* root);
void run_type_checker(node* root);

#endif