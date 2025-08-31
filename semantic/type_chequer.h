#ifndef TYPE_CHEQUER_H
#define TYPE_CHEQUER_H

VariableType check_exp_types(node* root);
void check_return_types(node* root, VariableType f_returnType);
char* VariableTypeToString(VariableType type);
void check_types(node* root);

#endif