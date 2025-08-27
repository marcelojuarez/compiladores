%{

/*Definition section*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}

%option noyywrap
%option yylineno

ID [a-z][a-z0-9]*
letra [a-zA-Z]      
digito [0-9]
valBool true|false


%%
    /*Rules section*/

"void"      { printf("TOKEN_VOID \n"); return TOKEN_VOID; }

"bool"      { printf("TOKEN_BOOL \n"); return TOKEN_BOOL; }

"int"       { printf("TOKEN_INT \n"); return TOKEN_INT; }

"return"    { printf("TOKEN_RETURN \n"); return TOKEN_RETURN; }

"const"     { printf("TOKEN_CONST \n"); return TOKEN_CONST; }                   
            
"=="        { printf("TOKEN_EQUALS \n"); return TOKEN_EQUALS; }

"="         { printf("TOKEN_ASSIGN \n"); return TOKEN_ASSIGN; }

"+"         { printf("TOKEN_MAS \n"); return TOKEN_MAS; }

"-"         { printf("TOKEN_MENOS \n"); return TOKEN_MENOS; }

"*"         { printf("TOKEN_MULT \n"); return TOKEN_MULT; }             

"/"         { printf("TOKEN_DIV \n"); return TOKEN_DIV; }  

"||"        { printf("TOKEN_OR \n"); return TOKEN_OR; }    

"&&"        { printf("TOKEN_AND \n"); return TOKEN_AND; }    


"("         { printf("TOKEN_PAREN_L \n"); return TOKEN_PAREN_L; }   
 
")"         { printf("TOKEN_PAREN_R \n"); return TOKEN_PAREN_R; }

"{"         { printf("TOKEN_LLAVE_L \n"); return TOKEN_LLAVE_L; }   
 
"}"         { printf("TOKEN_LLAVE_R \n"); return TOKEN_LLAVE_R; }

{valBool}   {
                printf("TOKEN_VAL_BOOL \n");

                if(strcmp(yytext, "true") == 0){
                    yylval.ival = 1;
                } else {
                    yylval.ival = 0;
                }
                    
                return TOKEN_VAL_BOOL;
            }   

{digito}+   {
                printf("TOKEN_NUM \n");
                yylval.ival = atoi(yytext);
                return TOKEN_NUM;
            }

{ID}        {
                printf("TOKEN_ID \n");
                yylval.sval = strdup(yytext);
                return TOKEN_ID;
            }

[ \t\n]+   { /* ignorar espacios, tabs y saltos de línea */ }

";"         { printf("TOKEN_PUNTO_Y_COMA \n");  return TOKEN_PUNTO_Y_COMA; }
          
%%

/*User Code section*/

/*
int main( int argc, char **argv ){

    yylex();
    return 0;
}
*/
