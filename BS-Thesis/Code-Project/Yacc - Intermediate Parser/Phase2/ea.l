%{
	#include <stdlib.h>
	#include "y.h"			
	// `y.h` will be created by "yacc.exe -d *.y".
	// `y.h` will contain all `Tokens` which we declared in `*.y` in order to be used here for lexical.
	int lineNo=1;
%}

LETTER [_a-zA-Z]
DIGIT    [0-9]

%%
"void"								return S_VOID;
"bool"								return S_BOOL;
"int"								return S_INT;
"float"								return S_FLOAT;
"string"							return S_STRING;

"true"								return S_TRUE;
"false"								return S_FALSE;
[/"]({LETTER}|{DIGIT})*[/"]			return S_TEXT;

"new"								return S_NEW;
"return"							return S_RETURN;
"assert"							return S_ASSERT;
"type"								return S_TYPE;
"var"								return S_VAR;
"function"							return S_FUNCTION;

"main"								return S_MAIN;

"*"									return '*';
"."									return '.';
"("									return '(';
")"									return ')';
"["									return '[';
"]"									return ']';
"{"									return '{';
"}"									return '}';
","									return ',';
"="									return '=';
";"									return ';';
":"									return ':';


{LETTER}({LETTER}|{DIGIT})*					{yylval.code=malloc(strlen(yytext)+1);strcpy(yylval.code,yytext); return ID;}
{DIGIT}+(\.{DIGIT}+)?(E(\+|-)?{DIGIT}+)?	{yylval.code=malloc(strlen(yytext)+1);strcpy(yylval.code,yytext); return NUM;}
											
"\n" 								lineNo++;

[ ]([ ])*							
([ \t])+							
.									return -1;
%%

int yywrap()
{
	return 1;
}
