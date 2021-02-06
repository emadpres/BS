%{
	#include <stdlib.h>
	//void yyerror(char *);
	#include "y.h"
	int lineNo=0;
%}

LETTER [a-zA-Z]
DIGIT    [0-9]

%%
"{"[^}]*"}"							;
"program"							return S_PROGRAM;
"of"								return S_OF;
"array"								return S_ARRAY;
"var"								return S_VAR;
"real"								return S_REAL;
"integer"							return S_INTEGER;
".."								return S_DOTDOT;
"function"							return S_FUNCTION;
"procedure"							return S_PROCEDURE;
"begin"								return S_BEGIN;
"end"								return S_END;
"if"								return S_IF;
"then"								return S_THEN;
"else"								return S_ELSE;
"while"								return S_WHILE;
"do"								return S_DO;
"<>"								return S_RELOP;	
"<"									return S_RELOP;
"<="								return S_RELOP;
">"									return S_RELOP;
">="								return S_RELOP;
"="									return S_RELOP;

":="								return S_ASSIGN;

[+-]								return S_PLUSMIN;
"or"								return S_OR;
[*/]								return S_MULOP;
"div"								return S_MULOP;
"mod"								return S_MULOP;
"and"								return S_MULOP;
"not"								return S_NOT;
"("									return '(';
")"									return ')';
"["									return '[';
"]"									return ']';
"."									return '.';
","									return ',';
";"									return ';';
":"									return ':';



{LETTER}({LETTER}|{DIGIT})*			return ID;
									 
{DIGIT}+(\.{DIGIT}+)?(E(\+|-)?{DIGIT}+)?       		return NUM;
"\n" 								{lineNo++;}  


[ ]([ ])*							
([ \t])+

.									return -1;
%%

int yywrap()
{
	return 1;
}


#if YY_MAIN
#include <conio.h>

int main()
	{
	printf("------------");
	clrscr();
	yyin=fopen("test.pas","r");
	yylex();
	printf("\nTotal line number=%d",lineNo);
	//getch();
	return 0;
	}
#endif