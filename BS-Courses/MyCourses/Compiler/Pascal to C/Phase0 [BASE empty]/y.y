%union
{
	char *code;
};

%{
int yylex(void);
//Write C Code Here
%}

%%

program :	;	
		
				
%%


#include "lex.c"


int yyerror(char* msgError)
{
	printf("error in line:%d at token: %s ",lineNo,yytext);
	return 1;

}


int main()
{

	yyin = fopen("input.pas", "r");
	printf("Parsing\n\n");
	yyparse();
	printf("\n\nParse Done !!!!!");
	fclose(yyin);
	//getch();
	return 0;
}
