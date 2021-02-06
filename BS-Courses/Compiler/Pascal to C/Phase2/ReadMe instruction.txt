"%union  ..." be balaye *.y !
yylval.code = yytext  tooye *.l !  ==> az in be bad be meghdare yytext ke tooye *.l faghat ghabele dastresi va printf bud, ro dar *.y ham dastresi darim az tarighe khate badi
"$<code>1" ya "$<code>$" hala ghabele estefadast ! ( mesale estefade sampleYY.y ! PS: malloc kardane niaze .. chon aghaye LEX baraye ma $<code># ro doros mikone ( vase terminal ha) va ma baraye dashtane meghdar non-terminal ha bayad khodemun doros konim)


sampleYY.y:

%{
#include "lex.yy.c"
#include <stdlib.h>
void yyerror(char *);
%}
%union
{
	char *code;
};
%token AND
%token THIS
%token PUBLIC
%token STATIC

%%

Goal : 
    MainClass  TypeDeclaration EOF
    {
	    $<code>$=malloc(1+strlen($<code>1)+strlen($<code>2));
		strcpy( $<code>$, $<code>2);
		strcat( $<code>$, $<code>1);
		fprintf($<code>$);	
    }
	;
%%
void yyerror(char *s) {
fprintf(stderr, "%s\n  inline=%d   token=%s \n", s,line_no, yytext);
}
int main(void) {
	yyin = fopen("Factorial.java", "r"); 
	yyparse();
	yyout=fopen("result.txt","w");
	myterminate();
	printf("Parse Has Been Finished");
	getch();
	return 0;
}
