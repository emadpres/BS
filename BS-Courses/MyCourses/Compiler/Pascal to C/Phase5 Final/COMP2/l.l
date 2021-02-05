%{
	#include <stdlib.h>
	//void yyerror(char *);
	#include "y.h"
	int lineNo=0;
%}

LETTER [a-zA-Z]
DIGIT    [0-9]

%%

"program"							return S_PROGRAM;
"var"								return S_VAR;
"array"								return S_ARRAY;
"of"								return S_OF;
"integer"							return S_INT;
"real"								return S_REAL;
"function"							return S_FUNC;
"procedure"							return S_PROC;

":"									return S_COL;
";"									return S_SEMICOL;
"."									return S_DOT;

"begin"								return S_BEGIN;
"end"								return S_END;

"if"           						return S_IF;
"then"								return S_THEN;
"else"								return S_ELSE;

"while"								return S_WHILE;
"do"								return S_DO;

"not"								return S_NOT;

"="									return S_EQ;
"<>"								{printf("H %s H",yytext);return S_NE;}
"<"									return S_L;
"<="								return S_LE;
">"									return S_G;
">="								return S_GE;

"+"									return '+';
"-"									return '-';
"or"								return S_OR;

"*"									return '*';
"/"									return '/';
"and"								return S_AND;
"div"								return S_DIV;
"mod"								return S_MOD;


":="								return assignop;

"("									return '(';
")"									return ')';
","									return ',';
"["									return '[';
"]"									return ']';



{LETTER}({LETTER}|{DIGIT})*			{yylval = *yytext;
									{printf("%s",yytext);}
									 return ID;}
{DIGIT}+(\.{DIGIT}+)?        		{
										printf("%d",atoi(yytext));
										return NUM;
									}

"\n"   {lineNo++;}  


[ ]([ ])*
([ \t])+
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
