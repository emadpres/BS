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
"//"[^"\n"]*"\n"							;
"/*"[^"*/"]*"*/"						;
"void"								return S_VOID;
"bool"								return S_BOOL;
"int"								return S_INT;
"float"								return S_FLOAT;
"true"								return S_TRUE;
"false"								return S_FALSE;
"return"							return S_RETURN;
"class"								return S_CLASS;
"public"							return S_PUBLIC;
"static"							return S_STATIC;
"const"								return S_CONST;
"signed"							return S_SIGNED;
"unsigned"							return S_UNSIGNED;

"if"								return S_IF;
"else"								return S_ELSE;
"while"								return S_WHILE;
"do"								return S_DO;

"||"								return S_OR;
"&&"								return S_AND;
"=="								return S_EQUALITY;
"!="								return S_INEQUALITY;

"+"									return '+';
"-"									return '-';
"!"									return '!';
"*"									return '*';
"/"									return '/';
"%"									return '%';

"<"									return '<';
">"									return '>';
">="								return S_GREATER_EQUAL;
"<="								return S_LESS_EQUAL;

"&"									return '&';
"."									return '.';
"("									return '(';
")"									return ')';
"["									return '[';
"]"									return ']';
"{"									return '{';
"}"									return '}';
","									return ',';
"/""								return '"';
"="									return '=';
";"									return ';';
":"									return ':';


{LETTER}({LETTER}|{DIGIT})*			{return ID;}

{DIGIT}+(\.{DIGIT}+)?(E(\+|-)?{DIGIT}+)?	{return NUM;}
											
"\n" 								lineNo++;

[ ]([ ])*							
([ \t])+							
.									return -1;
%%

int yywrap()
{
	return 1;
}
