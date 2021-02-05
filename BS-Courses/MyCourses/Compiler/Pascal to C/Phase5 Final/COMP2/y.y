%token ID
%token S_PROGRAM
%token S_VAR
%token S_ARRAY
%token S_OF
%token S_INT
%token S_REAL
%token S_FUNC
%token S_PROC
%token S_COL
%token S_SEMICOL
%token S_DOT
%token S_BEGIN
%token S_END
%token S_IF
%token S_ELSE
%token S_WHILE
%token assignop
%token NUM
%token S_THEN
%token S_DO
%token S_NOT
%token S_EQ
%token S_LE
%token S_GE
%token S_L
%token S_G
%token S_NE
%token S_OR
%token S_AND
%token S_DIV
%token S_MOD

%{

//void yyerror(char *);
int yylex(void);
int myArray[100];
int arrayCount;
%}

%%
	;
program	: S_PROGRAM 								{printf("int main ");} 
					ID 
					'(' 							{printf("(");} 
					identifier_list 
					')' 							{printf(") \n");} 
					S_SEMICOL 						{printf("{ \n");}
	declarations
	subprogram_declarations
	compound_statement
	S_DOT 											{printf(" retrun 0;\n");printf("}");}
	; 
identifier_list	: ID								//{printf("%s ",$1);}
				|	identifier_list
				',' 								{printf(", ");}
				ID									//{printf("%s ",$3);}
				;
declarations	:  declarations
						S_VAR
						identifier_list
						S_COL
						type
						S_SEMICOL					{printf(";");}
				|
	;
type	: standard_type								
		| S_ARRAY '[' NUM S_DOT S_DOT NUM ']' S_OF standard_type S_SEMICOL
		;
standard_type	: S_INT 							//{printf("int");}
				| S_REAL							//{{printf("float");}}
				;
subprogram_declarations	: subprogram_declarations subprogram_declaration  S_SEMICOL	
						|
						;
subprogram_declaration	: subprogram_head declarations 	compound_statement		
						;
subprogram_head	: S_FUNC 							{printf("\nint function ");}
						ID							//{printf("%s ",$3);}
						arguments  S_COL standard_type 	S_SEMICOL
				| S_PROC							{printf("\nvoid function ");}
						ID							//{printf("%s ",$3);}
						arguments S_SEMICOL
				;
arguments	: '(' 									{printf("(");}
				paremeter_list
				')'									{printf(")");}
			|
			;
paremeter_list	: identifier_list S_COL type
				| paremeter_list S_SEMICOL identifier_list S_COL type

compound_statement	: S_BEGIN 						{printf("\n{\n");}
						optional_statements
						S_END 						{printf("\n}\n");}
					;
optional_statements	: statement_list
					| 
					;
statement_list	: statement							
				| statement_list
						S_SEMICOL					{printf(";\n");} 
						statement					{printf(";");} 
				;
statement	: variable								
					assignop						{printf("=");} 
					expression						{printf(";");}
			| procedure_statement
			| compound_statement
			| S_IF									{printf("if ( ");}
				expression
				S_THEN								{printf(" ) \n");}
				statement
				S_ELSE								{printf("\nelse \n");}
				statement
			| S_WHILE								{printf("\nwhile (");}
				expression
				S_DO								{printf(" ) \n");}
				statement							
			;
variable	: ID										
			| ID 
				'['
				expression
				']'
			;
procedure_statement	: ID
					| ID 
							'('						{printf("(");}
							expression_list
							')'						{printf(")");}
					;
expression_list	: expression
				| expression_list
					','								{printf(",");}
					expression
				;
expression	: simple_expression						
			| simple_expression relop simple_expression
			;
simple_expression	: term
					| sign term
					| simple_expression addop term
					;
term	: factor
		| term mulop factor
		;
factor	: ID
		| ID
			'(' 									{printf("(");}
			expression_list
			')'										{printf(")");}
		| NUM
		| '('										{printf("(");}
			expression 
			')'										{printf(")");}
		| S_NOT										{printf("!");}
			factor
		;
sign 	: '+'										{printf("+");}
		| '-'										{printf("-");}
		;
relop	: S_EQ										{printf(" == ");}
		| S_NE										{printf(" != ");}
		| S_L										{printf(" < ");}
		| S_LE										{printf(" <= ");}
		| S_G										{printf(" > ");}
		| S_GE										{printf(" >= ");}
		;
addop	: '+'										{printf(" + ");}
		| '-'										{printf(" - ");}
		| S_OR										{printf(" || ");}
		;
mulop	: '*'										{printf(" * ");}
		| '/'										{printf(" / ");}
		| S_AND										{printf(" && ");}
		| S_DIV										{printf(" / ");}
		| S_MOD										{printf(" %% ");}
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


	yyin = fopen("test.pas", "r"); 
	yyparse();
	printf("\n\n !!!!! parse success !!!!!");
	fclose(yyin);
	//getch();
	return 0;
}
