%{
	#include <stdlib.h>
	#include "y.h"
	int lineNo=0;
	//Write C Code Here
%}

LETTER [a-zA-Z]
DIGIT    [0-9]

%%

{LETTER}({LETTER}|{DIGIT})*						{return ID;}
									 
{DIGIT}+(\.{DIGIT}+)?(E(\+|-)?{DIGIT}+)?       	{return NUM;}
												
"\n" 											{lineNo++;}  


[ ]([ ])*								;
([ \t])+								;


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
