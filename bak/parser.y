%{
#include <stdio.h>

// Declaraciones adelantadas:
int yylex(void);
int yyerror(const char *s);
%}

%token MAIN INT VOID TOKEN_ID EQUAL ASSIGN RETURN BOOL CONST IF MAS MULT DIV LEFT_BRACKET RIGHT_BRACKET LEFT_LLAVE RIGHT_LLAVE NUM END MENOS RESERVED

%left MAS MENOS
%left MULT DIV

%%

program:
      TR MAIN LEFT_BRACKET RIGHT_BRACKET LEFT_LLAVE statements RIGHT_LLAVE
    ; 
statements:
      /* vacio */
    | statement statements 
    ;

statement:
      TR TOKEN_ID END
    | TR TOKEN_ID ASSIGN expr END
    | TOKEN_ID ASSIGN expr END
    | RETURN expr END
    ;

expr:
      expr MAS expr
    | expr MENOS expr
    | expr MULT expr
    | expr DIV expr
    | expr EQUAL expr
    | NUM
    ;

TR:
      INT
    | VOID
    | BOOL

%%

typedef struct tree {
    int value;                // o cualquier otro tipo de dato
    struct tree *left;        // hijo izquierdo
    struct tree *right;       // hijo derecho
} tree;

int main() {
    if (yyparse() == 0) {
        printf("Parseado correctamente, sin errores.");
    }
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

tree* create_node(int value) {
    tree* node = (tree*)malloc(sizeof(tree));
    if (node != NULL) {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}