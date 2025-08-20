%{

#include <stdlib.h>
#include <stdio.h>

// Declaraciones adelantadas:
int yylex(void);
int yyerror(const char *s);

%}
 
%token TOKEN_VOID TOKEN_RETURN TOKEN_ASSIGN TOKEN_EQUALS TOKEN_CONST
%token TOKEN_ID TOKEN_PUNTO_Y_COMA
%token TOKEN_NUM TOKEN_VAL_BOOL TOKEN_OR TOKEN_AND
%token TOKEN_BOOL TOKEN_INT
%token TOKEN_MAS TOKEN_MENOS TOKEN_MULT TOKEN_DIV
%token TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L TOKEN_LLAVE_R 
    
%left TOKEN_MAS TOKEN_MENOS
%left TOKEN_MULT TOKEN_DIV
%left TOKEN_AND TOKEN_OR

%%
 
prog:
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L body TOKEN_LLAVE_R
    ;

body: sentencias 
    ;

sentencias:
          /*vacio*/
          | sentencia sentencias 
          ;

sentencia: decl 
         | asign
         | ret
         ;

decl: var | cts
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA
   | type asign
   ;

cts: TOKEN_CONST type asign
   ;

asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA
     ;

ret: TOKEN_RETURN value TOKEN_PUNTO_Y_COMA
   ;

value: expr
     | exprBool
     ;

expr: TOKEN_NUM
    | TOKEN_ID
    | expr TOKEN_MAS expr
    | expr TOKEN_MENOS expr
    | expr TOKEN_DIV expr
    | expr TOKEN_MULT expr
    ;

exprBool: TOKEN_VAL_BOOL
        | exprBool TOKEN_AND exprBool
        | exprBool TOKEN_OR exprBool
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
    }
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}