%{

#include <stdlib.h>
#include <stdio.h>
#include "tree.c"

node* root;
int yylex(void);
int yyerror(const char *s);

%}

%union {
    int ival;
    char* sval;
    node* root;
}

%token TOKEN_VOID TOKEN_RETURN TOKEN_ASSIGN TOKEN_EQUALS TOKEN_CONST TOKEN_PUNTO_Y_COMA
%token <sval> TOKEN_ID 
%token <ival> TOKEN_NUM <ival> TOKEN_VAL_BOOL 
%token TOKEN_BOOL TOKEN_INT 
%token TOKEN_MAS TOKEN_MENOS TOKEN_MULT TOKEN_DIV TOKEN_OR TOKEN_AND
%token TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L TOKEN_LLAVE_R 
    
%left TOKEN_MAS TOKEN_MENOS
%left TOKEN_MULT TOKEN_DIV
%left TOKEN_AND TOKEN_OR

%type <root> sentencia sentencias body decl asign ret expr exprBool

%%
 
prog:
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L body TOKEN_LLAVE_R 
    {
        root = createOpNode("program");
        
    }
    ;

body: sentencias { $$ = $1; }
    ;

sentencias:
          /*vacio*/ { $$ = NULL }
          | sentencia sentencias {
            
          }
          ;

sentencia: decl {$$ = $1;}
         | asign {$$ = $1;}
         | ret {$$ = $1;}
         ;

decl: var 
    | cts
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA
   | type asign
   ;

cts: TOKEN_CONST type asign
   ;

asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        $$ = createNewTree('=', $1, $3);
    }
     ;

ret: TOKEN_RETURN value TOKEN_PUNTO_Y_COMA {
        ret = createOpNode('return');
        val = createIntNode();
        $$ = createNewTree();
    }
   ;

value: expr
     | exprBool
     ;

expr: TOKEN_NUM {$$ = createIntNode($1)}
    | TOKEN_ID {$$ = createIdNode($1)}
    | expr TOKEN_MAS expr {

        node* op = createOpNode("+");
        $$ = createNewTree(op, $1, $3);
        
    }
    | expr TOKEN_MENOS expr {

        node* op = createOpNode("-");
        $$ = createNewTree(op, $1, $3);
        
    }
    | expr TOKEN_DIV expr {

        node* op = createOpNode("/");
        $$ = createNewTree(op, $1, $3);
        
    }
    | expr TOKEN_MULT expr  {

        node* op = createOpNode("*");
        $$ = createNewTree(op, $1, $3);
        
    }
    | TOKEN_PAREN_L expr TOKEN_PAREN_R  {

        node* op = createIntNode($2);
        $$ = createNewTree(op, $1, $3);
        
    }
    ;

exprBool: TOKEN_VAL_BOOL
        | exprBool TOKEN_AND exprBool {

        }
        | exprBool TOKEN_OR exprBool {

        }
        | TOKEN_PAREN_L exprBool TOKEN_PAREN_R {

        }
        ;

type: TOKEN_INT 
    | TOKEN_BOOL
    ;

return_type: TOKEN_VOID
           | TOKEN_BOOL
           | TOKEN_INT
           ; 

%%

int main() {
    if (yyparse() == 0) {
        printf("Parseado correctamente, sin errores.\n");
        printInOrder(root);
    }
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}