%{

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int yylex(void);
int yyerror(const char *s);
node* root;

%}

%code requires {
    #include "tree.h"
}

%union {
    int ival;
    char* sval;
    node* nd;
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

%type <nd> return_type body sentencia sentencias decl asign ret cts var type value expr exprBool 

%%

prog:
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L body TOKEN_LLAVE_R 
    {
        node* rt = createOpNode("program");
        root = createNewTree(rt, $1, $6);
    }
    ;

return_type: TOKEN_VOID {
                $$ = createOpNode("void");
            }
            | type
            ; 

body: sentencias { 
        node* bd = createOpNode("body");
        $$ = createNewTree(bd, $1, NULL);
    }
    ;

sentencias:
          /*vacio*/ { $$ = NULL; }
          | sentencia sentencias {
            node* sent = createOpNode("sentencia");
            $$ = createNewTree(sent, $1, $2);
          }
          ;

sentencia: decl {
            node* declNode = createOpNode("decl");
            $$ = createNewTree(declNode, $1, NULL);            
        }
        | asign {
            node* asignNode = createOpNode("asign");
            $$ = createNewTree(asignNode, $1, NULL);
        }
        | ret {
            node* retNode = createOpNode("ret");
            $$ = createNewTree(retNode, $1, NULL);
        }
        ;

decl: var{
        node* varNode = createOpNode("var");
        $$ = createNewTree(varNode, $1, NULL);
    } 
    | cts {
        node* ctsNode = createOpNode("cts");
        $$ = createNewTree(ctsNode, $1, NULL);
    }
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdNode($2);
        $$ = createNewTree($1, idNode, NULL);
    }
    | type asign {
        $$ = createNewTree($1, $2, NULL);
    }
    ;

cts: TOKEN_CONST type asign {
        $$ = createNewTree($2, $3, NULL);
   }
   ;

type: TOKEN_INT {$$ =  createOpNode("int");}
    | TOKEN_BOOL {$$ =  createOpNode("bool");}
    ;


asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* asignNode = createOpNode("=");
        node* idNode = createIdNode($1);
        $$ = createNewTree(asignNode, idNode, $3);
     }
     ;

ret: TOKEN_RETURN value TOKEN_PUNTO_Y_COMA {
        $$ = $2;
    }
    ;

value:
    expr 
    {   
        node* node1 = createOpNode("expr");
        $$ = createNewTree(node1, $1, NULL);     
    }
    | exprBool
    {
        node* node1 = createOpNode("exprBool");
        $$ = createNewTree(node1, $1, NULL);
    }
    ;

expr: TOKEN_NUM {$$ = createIntNode($1);}
    | TOKEN_ID {$$ = createIdNode($1); }
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
        $$ = $2;        
    }
    ;

exprBool: TOKEN_VAL_BOOL { $$ = createBoolNode($1);}
    | exprBool TOKEN_AND exprBool {
        node* op = createOpNode("&&");
        $$ = createNewTree(op, $1, $3);
    }
    | exprBool TOKEN_OR exprBool {
        node* op = createOpNode("||");
        $$ = createNewTree(op, $1, $3);
    }
    | TOKEN_PAREN_L exprBool TOKEN_PAREN_R {
        $$ = $2;
    }
    ;
    
%%

int main() {
    if (yyparse() == 0) {
        printf("Parseado correctamente, sin errores.\n");
        printTree(root, 0); 
    }
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}