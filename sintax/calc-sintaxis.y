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
    #include "type_chequer.h"
    #include "semantic/expr_solver.h"
    extern FILE *yyin;
}

%union {
    int ival;
    char* sval;
    node* nd;
    VariableType vtype;
    NodeType ntype;
}

%token TOKEN_RETURN TOKEN_ASSIGN TOKEN_EQUALS TOKEN_CONST TOKEN_PUNTO_Y_COMA
%token <sval> TOKEN_ID 
%token <ival> TOKEN_NUM <ival> TOKEN_VAL_BOOL 
%token <vtype> TOKEN_BOOL TOKEN_INT TOKEN_VOID
%token TOKEN_MAS TOKEN_MENOS TOKEN_MULT TOKEN_DIV TOKEN_OR TOKEN_AND
%token TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L TOKEN_LLAVE_R 
    
%left TOKEN_MAS TOKEN_MENOS
%left TOKEN_MULT TOKEN_DIV
%left TOKEN_AND TOKEN_OR

%type <nd> body sentencia sentencias decl asign ret cts var value expr 
%type <vtype> type return_type
%%

prog:
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_LLAVE_L body TOKEN_LLAVE_R 
    {
        node* rt = createFuncNode($2, $1);
        root = createNewTree(rt, $6, NULL);
    }
    ;

return_type: TOKEN_VOID { $$ = NONE; }
            | type { $$ = $1; }
            ; 

body: sentencias { 
        node* bd = createNode("body", NONE);
        $$ = createNewTree(bd, $1, NULL);
    }
    ;

sentencias:
          /*vacio*/ { $$ = NULL; }
          | sentencia sentencias {
            node* sent = createNode("sentencia", NONE);
            $$ = createNewTree(sent, $1, $2);
          }
          ;

sentencia: decl {
            node* declNode = createNode("decl", NONE);
            $$ = createNewTree(declNode, $1, NULL);            
        }
        | asign {
            node* asignNode = createNode("asign", NONE);
            $$ = createNewTree(asignNode, $1, NULL);
        }
        | ret {
            node* retNode = createRetNode(NONE);
            $$ = createNewTree(retNode, $1, NULL);
        }
        ;

decl: var{
        node* varNode = createNode("var", NONE);
        $$ = createNewTree(varNode, $1, NULL);
    } 
    | cts {
        node* ctsNode = createNode("cts", NONE);
        $$ = createNewTree(ctsNode, $1, NULL);
    }
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdDecl($2, $1, NODE_DECL);

        $$ = createNewTree(idNode, NULL, NULL);
    }
    | type TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdDecl($2, $1, NODE_DECL);
        node* asignNode = createOpNode(asign, NONE);
        
        $$ = createNewTree(asignNode, idNode, $4);
    }
    ;

cts: TOKEN_CONST type TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* idNode = createIdDecl($3, $2, NODE_DECL);
        $$ = createNewTree(idNode, $5, NULL);
   }
   ;

type: TOKEN_INT {$$ = TYPE_INT;}
    | TOKEN_BOOL {$$ = TYPE_BOOL;}
    ;

asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* asignNode = createOpNode(asign, NONE);
        node* idNode = createIdExpr($1, NODE_ID_USE);
        $$ = createNewTree(asignNode, idNode, $3);
     }
     ;

ret: TOKEN_RETURN value TOKEN_PUNTO_Y_COMA {
        $$ = $2;
    }
    | TOKEN_RETURN TOKEN_PUNTO_Y_COMA {
        $$ = NULL;
    }
    ;

value:
    expr 
    {   
        node* node1 = createNode("expr", NONE);
        $$ = createNewTree(node1, $1, NULL);     
    }
    ;

expr: TOKEN_NUM {$$ = createIntNode($1);}
    | TOKEN_ID {$$ = createIdExpr($1, NODE_ID_USE); }
    | TOKEN_VAL_BOOL { $$ = createBoolNode($1);}
    | expr TOKEN_MAS expr {
        node* op = createOpNode(suma, TYPE_INT);
        $$ = createNewTree(op, $1, $3);
    }
    | expr TOKEN_MENOS expr {
        node* op = createOpNode(resta, TYPE_INT);
        $$ = createNewTree(op, $1, $3); 
    }
    | expr TOKEN_DIV expr {
        node* op = createOpNode(divide, TYPE_INT);
        $$ = createNewTree(op, $1, $3);        
    }
    | expr TOKEN_MULT expr  {
        node* op = createOpNode(mult, TYPE_INT);
        $$ = createNewTree(op, $1, $3);     
    }
    | TOKEN_PAREN_L expr TOKEN_PAREN_R  {
        $$ = $2;        
    }
    | expr TOKEN_AND expr {
        node* op = createOpNode(and, TYPE_BOOL);
        $$ = createNewTree(op, $1, $3);
    }
    | expr TOKEN_OR expr {
        node* op = createOpNode(or, TYPE_BOOL);
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

        symbol_table* table = create_symbol_table_of_tree(root);

        print_symbol_table(table);

        execute_tree(root, table);

        print_symbol_table(table);
        //check_types(root);

    }

    fclose(input_file);
    return 0;
}


int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}