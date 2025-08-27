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
    #include "symbol_table.h"
    extern FILE *yyin;
}

%union {
    int ival;
    char* sval;
    node* nd;
    VariableType vtype;
    NodeType ntype;
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

%type <nd> return_type body sentencia sentencias decl asign ret cts var value expr 
%type <vtype> type
%%

prog:
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L body TOKEN_LLAVE_R 
    {

        node* rt = createNode("program");
        root = createNewTree(rt, $1, $6);
    }
    ;

return_type: TOKEN_VOID {
                $$ = createNode("void");
            }
            | type {
                $$ = createTypeNode($1);
            }
            ; 

body: sentencias { 
        node* bd = createNode("body");
        $$ = createNewTree(bd, $1, NULL);
    }
    ;

sentencias:
          /*vacio*/ { $$ = NULL; }
          | sentencia sentencias {
            node* sent = createNode("sentencia");
            $$ = createNewTree(sent, $1, $2);
          }
          ;

sentencia: decl {
            node* declNode = createNode("decl");
            $$ = createNewTree(declNode, $1, NULL);            
        }
        | asign {
            node* asignNode = createNode("asign");
            $$ = createNewTree(asignNode, $1, NULL);
        }
        | ret {
            node* retNode = createNode("ret");
            $$ = createNewTree(retNode, $1, NULL);
        }
        ;

decl: var{
        node* varNode = createNode("var");
        $$ = createNewTree(varNode, $1, NULL);
    } 
    | cts {
        node* ctsNode = createNode("cts");
        $$ = createNewTree(ctsNode, $1, NULL);
    }
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdDecl($2, $1, NODE_DECL);
        node* tyNode = createTypeNode($1);
        $$ = createNewTree(tyNode, idNode, NULL);
    }
    | type TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdDecl($2, $1, NODE_DECL);
        node* tyNode = createTypeNode($1);
        $$ = createNewTree(tyNode, idNode, NULL);
    }
    ;

cts: TOKEN_CONST type asign {
        node* tyNode = createTypeNode($2);
        $$ = createNewTree(tyNode, $3, NULL);
   }
   ;

type: TOKEN_INT {$$ = TYPE_INT;}
    | TOKEN_BOOL {$$ = TYPE_BOOL;}
    ;

asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* asignNode = createOpNode(asign);
        node* idNode = createIdExpr($1, NODE_EXPR);
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
        node* node1 = createNode("expr");
        $$ = createNewTree(node1, $1, NULL);     
    }
    ;

expr: TOKEN_NUM {$$ = createIntNode($1);}
    | TOKEN_ID {$$ = createIdExpr($1, NODE_EXPR); }
    | TOKEN_VAL_BOOL { $$ = createBoolNode($1);}
    | expr TOKEN_MAS expr {
        node* op = createOpNode(suma);
        $$ = createNewTree(op, $1, $3);
    }
    | expr TOKEN_MENOS expr {
        node* op = createOpNode(resta);
        $$ = createNewTree(op, $1, $3); 
    }
    | expr TOKEN_DIV expr {
        node* op = createOpNode(divide);
        $$ = createNewTree(op, $1, $3);        
    }
    | expr TOKEN_MULT expr  {
        node* op = createOpNode(mult);
        $$ = createNewTree(op, $1, $3);     
    }
    | TOKEN_PAREN_L expr TOKEN_PAREN_R  {
        $$ = $2;        
    }
    | expr TOKEN_AND expr {
        node* op = createOpNode(and);
        $$ = createNewTree(op, $1, $3);
    }
    | expr TOKEN_OR expr {
        node* op = createOpNode(or);
        $$ = createNewTree(op, $1, $3);
    }
    ;
    
%%

int main(int argc, char *argv[]) {
    
    FILE *input_file = fopen(argv[1], "r");

    yyin = input_file;

    if (yyparse() == 0) {
        printf("Parseado correctamente, sin errores.\n");
        printTree(root, 0);

        //symbol_table* table = create_symbol_table_of_tree(root);
        //print_symbol_table(table);
    }

    fclose(input_file);
    return 0;
}


int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}