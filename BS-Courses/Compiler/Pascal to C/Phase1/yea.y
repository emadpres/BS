%token ID
%token NUM
%token S_PROGRAM
%token S_VAR
%token S_ARRAY
%token S_DOTDOT
%token S_OF
%token S_INTEGER
%token S_REAL
%token S_FUNCTION
%token S_PROCEDURE
%token S_BEGIN
%token S_END
%token S_IF
%token S_THEN
%token S_ELSE
%token S_WHILE
%token S_DO

%token S_RELOP
%token S_ASSIGN
%token S_PLUSMIN
%token S_OR
%token S_MULOP
%token S_NOT

%{

//void yyerror(char *);
int yylex(void);
%}

%%

program :		S_PROGRAM								{printf(" S_PROGRAM");}
				ID										{printf(" ID");}
				'(' 									{printf(" (");}
				identifier_list							
				')' ';' 								{printf(" );\n");}
				declarations							
				subprogram_declarations	
				compound_statement						
				'.'										{printf(".");}
				|										{printf("<Empty Input>");}
			;

identifier_list :	ID									{printf(" ID");}
					|
					identifier_list ',' ID				{printf(" ,ID");}
				;

declarations :		declarations
					S_VAR								{printf(" var");}
					identifier_list
					':'									{printf(" :");}
					type								
					';'									{printf(" ;\n");}
					|
				;

type :				standard_type
					|
					S_ARRAY	'['							{printf("array[");}
					NUM									{printf(" NUM");}
					S_DOTDOT							{printf(" ..");}
					NUM									{printf(" NUM");}
					']'	S_OF							{printf(" ] of");}
					standard_type
				;
				
standard_type :		S_INTEGER 							{printf(" integer");}
					| S_REAL							{printf(" real");}
				;

subprogram_declarations :	subprogram_declarations 	{printf("\n");}
							subprogram_declaration 
							';'							{printf(" ;");}
							|							
						;

subprogram_declaration :	subprogram_head
							declarations
							compound_statement			
						;
						
subprogram_head : 	S_FUNCTION							{printf(" Function");}
					ID									{printf(" ID");}
					arguments
					':'									{printf(" :");}
					standard_type
					';'									{printf(" ;\n");}
				|
					S_PROCEDURE							{printf(" Procedure");}
					ID									{printf(" ID");}
					arguments
					';'									{printf(" ;\n");}
				;

arguments :		'('										{printf(" (");}
				parameter_list
				')'										{printf(" )");}
			|
			;

parameter_list :	identifier_list 
					':'									{printf(" :");}
					type
				|
					parameter_list 
					';'									{printf(" ;");}
					identifier_list
					':'									{printf(" :");}
					type
				;


compound_statement:	S_BEGIN								{printf(" \nbegin\n");}
					optional_statements
					S_END								{printf(" \nend");}



optional_statements :	statement_list
					|									{printf(" <Empty Body>\n");}
					;
					
statement_list :	statement							
				|
					statement_list						
					';'									{printf(" ;;\n");}
					statement							
				;

statement :		variable
				S_ASSIGN								{printf(" =");}
				expression
			|	
				procedure_statement
			|
				compound_statement
			|
				S_IF									{printf(" if");}
				expression							
				S_THEN									{printf(" then\n");}
				statement							
				S_ELSE									{printf(" \nelse\n");}
				statement						
			|
				S_WHILE									{printf(" while");}
				expression
				S_DO									{printf(" do");}
				statement
			;

variable :	ID											{printf(" ID");}	
		|
			ID 											{printf(" ID");}
			'['											{printf(" [");}
			expression 
			']'											{printf(" ]");}
		;


procedure_statement :	ID								{printf(" ID");}
					|
						ID								{printf(" ID");}
						'('								{printf(" (");}
						expression_list
						')'								{printf(" )");}
				;

expression_list :	expression
				|
					expression_list
					','									{printf(" , ");}
					expression
				;

expression :	simple_expression
			|
				simple_expression
				S_RELOP									{printf(" ??");}
				simple_expression
			;

			
simple_expression :	term
				|	
					S_PLUSMIN							{printf(" +-");}
					term
				|
					simple_expression
					addOp
					term
				;

addOp:	S_PLUSMIN										{printf(" +-");}
	|
		S_OR											{printf(" or ");}
	;
	
term :	factor
	|
		term
		S_MULOP											{printf(" */");}
		factor
	;

factor :	variable
		|
			ID 											{printf(" ID");}
			'('											{printf(" (");}
			expression_list 
			')'											{printf(" )");}
		|
			NUM											{printf(" NUM");}
		|
			'('											{printf(" )");}	
			expression 
			')'											{printf(" (");}
		|
			S_NOT										{printf(" not ");}
			factor
		;
		
				
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
	printf("Goind to parse\n\n");
	yyparse();
	printf("\n\nParse Done !!!!!");
	fclose(yyin);
	//getch();
	return 0;
}
