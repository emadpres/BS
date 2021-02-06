%{
	#include <stdlib.h>
	//void yyerror(char *);
	//#include "y.h"
	int lineNo=0;
%}

LETTER [a-zA-Z]
DIGIT    [0-9]

%%


{LETTER}({LETTER}|{DIGIT})*			{//yylval = *yytext;
									printf(">> %s\n",yytext);}
									 
									 
{DIGIT}+(\.{DIGIT}+)?        		{
										printf(">>>> %d\n",atoi(yytext));
										return 3;
									}

"\n"   {lineNo++;}  


[ ]([ ])*
([ \t])+

%%

int yywrap()
{
	return 1;
}


//#if YY_MAIN
//#include <conio.h>

int main()
	{
	printf("------------\n\n");
	//clrscr();
	yyin=fopen("t.pas","r");
	yylex();
	printf("\nTotal line number=%d",lineNo);
	//getch();
	return 0;
	}
//#endif
