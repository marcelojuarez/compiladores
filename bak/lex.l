%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.tab.h"

%}

%option noyywrap
%option yylineno

ID [a-z][a-z0-9]*
letra [a-zA-Z]      
digito [0-9]   


%%

    /*Rules section*/

"void"      {
                printf("VOID\n");
                return VOID;
            }

"main"      {
                printf("MAIN\n");
                return MAIN;
            }      

"if"        {
                printf("IF\n");
                return IF;
            }

"bool"      {
                printf("BOOL\n");
                return BOOL;
            }

"int"       {
                printf("INT\n");
                return INT;
            }

"return"    {
                printf("RETURN\n");
                return RETURN;
            }

"const"     {
                printf("CONST\n");
                return CONST;
            }                   
            
"=="        {
                printf("EQUAL\n");
                return EQUAL;
            }

"="         {
                printf("ASSIGN\n");
                return ASSIGN;
            }

"+"         {
                printf("MAS \n");
                return MAS;
            }

"-"         {
                printf("MENOS\n");
                return MENOS;
            }

"*"         {
                printf("MULT\n");
                return MULT;
            }             

"/"         {
                printf("DIV\n");
                return DIV;
            }    

"("         {
                printf("LEFT_BRACKET\n");
                return LEFT_BRACKET;
            }   
 
")"         {
                printf("RIGHT_BRACKET\n");
                return RIGHT_BRACKET;
            }

"{"         {
                printf("LEFT_LLAVE\n");
                return LEFT_LLAVE;
            }   
 
"}"         {
                printf("RIGHT_LLAVE\n");
                return RIGHT_LLAVE;
            }

{digito}+   {
                printf("NUM: %s\n", yytext);
                return NUM;
            }

{ID}        {
                printf("TOKEN_ID %s\n", yytext);
                return TOKEN_ID;
            }

";"         {
                printf("END: ;\n");
                return END;
            }

[\t\n]+     { /* ignorar espacios, tabs y saltos de lÃ­nea */ }

%%

/*
int main() {
    yylex();
    return 0;
}
*/


