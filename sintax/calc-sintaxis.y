%{

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int yylex(void);
int yyerror(const char *s);
node* root;
VariableType current_return_type = NONE;
extern int yylineno;

%}

%code requires {
    #include "tree.h"
    #include "symbol_table.h"
    #include "type_checker.h"
    #include "expr_solver.h"
    #include "assembly_generator.h"
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
    return_type TOKEN_ID TOKEN_PAREN_L TOKEN_PAREN_R 
    { // Se asigna el tipo de retorno a la variable global
        current_return_type = $1;
    }
    TOKEN_LLAVE_L body TOKEN_LLAVE_R 
    {
        node* rt = create_function_node($2, $1);
        root = create_tree(rt, $7, NULL);
        
        // Se resetea el tipo de retorno después del parsing
        current_return_type = NONE;
    }
    ;

return_type: TOKEN_VOID { $$ = NONE; }
            | type { $$ = $1; }
            ; 

body: sentencias { 
        node* bd = create_node("body", NONE);
        $$ = create_tree(bd, $1, NULL);
    }
    ;

sentencias:
          /*vacio*/ { $$ = NULL; }
          | sentencia sentencias {
            node* sent = create_node("sentencia", NONE);
            $$ = create_tree(sent, $1, $2);
          }
          ;

sentencia: decl {
            $$ = $1;            
        }
        | asign {
            $$ = $1;
        }
        | ret {
            node* retNode = create_return_node(current_return_type);
            $$ = create_tree(retNode, $1, NULL);
        }
        ;

decl: var{
        node* varNode = create_node("var", NONE);
        $$ = create_tree(varNode, $1, NULL);
    } 
    | cts {
        node* ctsNode = create_node("cts", NONE);
        $$ = create_tree(ctsNode, $1, NULL);
    }
    ;

var: type TOKEN_ID TOKEN_PUNTO_Y_COMA {
        node* idNode = create_id_decl_node($2, $1, NODE_DECL);

        $$ = create_tree(idNode, NULL, NULL);
    }
    | type TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* idNode = create_id_decl_node($2, $1, NODE_DECL);
        node* asignNode = create_operation_node(OP_ASSIGN, NONE);
        
        $$ = create_tree(asignNode, idNode, $4);
    }
    ;

cts: TOKEN_CONST type TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* idNode = create_id_decl_node($3, $2, NODE_DECL);
        $$ = create_tree(idNode, $5, NULL);
   }
   ;

type: TOKEN_INT {$$ = TYPE_INT;}
    | TOKEN_BOOL {$$ = TYPE_BOOL;}
    ;

asign: TOKEN_ID TOKEN_ASSIGN value TOKEN_PUNTO_Y_COMA {
        node* asignNode = create_operation_node(OP_ASSIGN, NONE);
        node* idNode = create_id_expr_node($1, NODE_ID_USE);
        $$ = create_tree(asignNode, idNode, $3);
     }
     ;

ret: 
    TOKEN_RETURN value TOKEN_PUNTO_Y_COMA {
        if (current_return_type == NONE) {
            yyerror("función 'void' no puede retornar un valor");
            YYERROR;
        }
        $$ = $2;
    }
    | TOKEN_RETURN TOKEN_PUNTO_Y_COMA {
        if (current_return_type != NONE) {
            yyerror("función debe retornar un valor");
            YYERROR;
        }
        $$ = NULL;
    }
    ;

value:
    expr 
    {   
        $$ = $1;     
    }
    ;

expr: TOKEN_NUM {$$ = create_int_node($1);}
    | TOKEN_ID {$$ = create_id_expr_node($1, NODE_ID_USE); }
    | TOKEN_VAL_BOOL { $$ = create_bool_node($1);}
    | expr TOKEN_MAS expr {
        node* op = create_operation_node(OP_ADD, TYPE_INT);
        $$ = create_tree(op, $1, $3);
    }
    | expr TOKEN_MENOS expr {
        node* op = create_operation_node(OP_SUB, TYPE_INT);
        $$ = create_tree(op, $1, $3); 
    }
    | expr TOKEN_DIV expr {
        node* op = create_operation_node(OP_DIV, TYPE_INT);
        $$ = create_tree(op, $1, $3);        
    }
    | expr TOKEN_MULT expr  {
        node* op = create_operation_node(OP_MULT, TYPE_INT);
        $$ = create_tree(op, $1, $3);     
    }
    | TOKEN_PAREN_L expr TOKEN_PAREN_R  {
        $$ = $2;        
    }
    | expr TOKEN_AND expr {
        node* op = create_operation_node(OP_AND, TYPE_BOOL);
        $$ = create_tree(op, $1, $3);
    }
    | expr TOKEN_OR expr {
        node* op = create_operation_node(OP_OR, TYPE_BOOL);
        $$ = create_tree(op, $1, $3);
    }
    ;
    
%%

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s near line %d\n", s, yylineno);
    return 0;
}