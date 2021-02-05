%token ID
%token NUM
%token S_VOID
%token S_BOOL
%token S_INT
%token S_FLOAT
%token S_TRUE
%token S_FALSE
%token S_AND
%token S_OR
%token S_EQUALITY
%token S_INEQUALITY
%token S_RETURN
%token S_MAIN
%token S_CLASS
%token S_PUBLIC
%token S_STATIC
%token S_SIGNED
%token S_UNSIGNED
%token S_CONST
%token S_IF
%token S_ELSE
%token S_WHILE
%token S_DO
%token S_GREATER_EQUAL
%token S_LESS_EQUAL

%union
{
	char *code;
	int type;
};

%{
int yylex(void);

/************ Declare All Needed Variables & Functions Here *****/



%}


%%

Program : 					DeclarationList
;

DeclarationList : 			Declaration DeclarationList
							|
;

Declaration :				FunctionDeclaration
							| ClassDeclaration
;

ClassDeclaration :			S_CLASS ID OptionalSuperclass '{'	{ printf("Class{\n");}
							MemberDeclarations '}' VariableList';'			{ printf("}C\n");}
;

VariableList:				Variable MoreVariables
							|
;

OptionalSuperclass :		':' S_PUBLIC ID							{/*Fake*/}
							|
;

MemberDeclarations :		FieldDeclarationList S_PUBLIC ':' MethodDeclarationList
							|
;

FieldDeclarationList :		FieldDeclaration FieldDeclarationList
							|
;

FieldDeclaration :			OptionalStatic VariableDeclaration
;

OptionalStatic :			S_STATIC
							|
;

MethodDeclarationList :		MethodDeclaration MethodDeclarationList
							|
;

MethodDeclaration :			OptionalStatic FunctionDeclaration
;









FunctionDeclaration :		FunctionType						{ printf("Function{\n");}
							ID
							'('
							OptionalParameterList
							')'									
							Block								{ printf("}F\n");}
;

FunctionType :				S_VOID
							| TypeName 
;

OptionalParameterList :		Parameter MoreParameters 
							|
;

Parameter :					TypeName
							Variable
;

MoreParameters :			','
							Parameter 
							MoreParameters 
							|
;

Block :						'{' 
							DeclarationOrStatementList 
							'}'
;

DeclarationOrStatementList: 									{printf("\n>>> ");}
							DeclarationOrStatement				{printf(" <<<<\n");}
							DeclarationOrStatementList
							|
;










TypeName :					PrimitiveType | ID
;

PrimitiveType :				S_INT
							| S_BOOL
							| S_FLOAT
;

TypeModifier :				OptionalPrimaryModifier 
							OptionalSecondaryModifier 
;

OptionalPrimaryModifier:	S_CONST						{printf(" ConstDeclartion ");}
							|
;

OptionalSecondaryModifier:	S_UNSIGNED					{printf(" Unsigned ");}
							| S_SIGNED
							|
;

PrimitiveDeclaration:		TypeModifier
							PrimitiveType 
							RestOfVariableDeclaration 
;

VariableDeclaration :		TypeModifier				{printf("[T]");}
							TypeName 									
							RestOfVariableDeclaration
;

RestOfVariableDeclaration:	Variable MoreVariables ';'
;

OptionalPointer :			'*' OptionalPointer
							|
;

Dimensions :				'[' NUM ']' Dimensions
							|
;

VariableInitilization :		'='	Expression
							|
;

Variable :					OptionalPointer ID Dimensions VariableInitilization
;

MoreVariables :				',' Variable
							MoreVariables 
							|
;



Expression :				Disjunction 
;

MoreExpressions :			',' Expression MoreExpressions
							|
;
OptionalExpression :		Expression
							|
;

Disjunction :				Conjunction MoreConjunctions 
;

MoreConjunctions :			S_OR Conjunction MoreConjunctions 
							|
;

Conjunction :				Equality MoreEqualities
;

MoreEqualities :			S_AND Equality MoreEqualities 
							| 
;

Equality :					Inequality RestOfEquality 
;

RestOfEquality :			S_EQUALITY Inequality 
							| S_INEQUALITY Inequality 
							| 
;

Inequality :				Sum RestOfInequality 
;

RestOfInequality :			'<' Sum 
							| '>' Sum 
							| S_LESS_EQUAL Sum 
							| S_GREATER_EQUAL Sum 
							|
;
Sum :						Product MoreProducts 
;

MoreProducts :				'+' 								{printf(" Sum ");}
							Product MoreProducts 
							| '-'								{printf(" Min ");}
							Product MoreProducts 
							|
;


Product :					Factor MoreFactors
;

MoreFactors :				'*' Factor MoreFactors 
							| '/' Factor MoreFactors 
							| '%' Factor MoreFactors 
							|
;

Factor :					Primary 
							| '+' 								{printf(" +Primary ");}
							Primary
							| '-' 								{printf(" -Primary  ");}
							Primary 
							| '!' Primary 
;

Primary :					ID MorePrimary 
							| NUM 
							| S_TRUE
							| S_FALSE 
							| '(' Expression ')' 
;

MorePrimary :				ArrayAccess 
							| FieldAccess 
							| FunctionCall 
							| 
;

ArrayAccess :				'[' Expression ']' MorePrimary  
;

FieldAccess :				'.' ID MorePrimary
;

FunctionCall : 				'(' OptionalArgumentList ')' MorePrimary 
;

OptionalArgumentList :		Expression MoreExpressions 
							|
;








DeclarationOrStatement : 	PrimitiveDeclaration 					{printf(" PrimitiveDeclaration ");}
							|								
							KeywordStatement						{printf(" KeywordStatement ");}
							|								  
							OtherDeclarationOrStatement				{printf(" OtherDeclarationOrStatement ");}
;

Statement:					KeywordStatement | ExpressionStatement
;

ExpressionStatement :		ID RestOfExpressionStatement
;

KeywordStatement :			Selection | Iteration | Jump | Block
;

Selection :					S_IF 							{printf(" If ");}
							'(' Expression ')' Statement OptionalElse
;

OptionalElse :				S_ELSE							{printf(" Else ");}
							Statement 
							|								{printf(" NoElse ");}
;

Iteration :					S_WHILE '(' Expression ')' Statement 
							| S_DO Statement S_WHILE '(' Expression ')' ';'
;

Jump :						S_RETURN OptionalExpression ';'
;


OtherDeclarationOrStatement:	ID RestOfDeclarationOrStatement 
;

RestOfDeclarationOrStatement:	RestOfExpressionStatement
;

RestOfExpressionStatement :		MorePrimary OptionalAssignment ';' ;
OptionalAssignment :			'=' Expression | ;



%%


#include "lex.c"

/*
* This function handle `Grammer Error` 
*/
int yyerror(char* msgError)
{
	printf("error in line:%d at token: %s ",lineNo,yytext);
	return 1;

}

/*
* Start the yacc parsing
*/
int StartParsing(char inputFile[100])
{
	yyin = fopen(inputFile, "r");
	if(yyin != NULL )
	{
		printf("\n############## PARSE START [%s] ##############\n\n",inputFile);
		yyparse();	// Parse `yyin` file with above grammer.
		fclose(yyin);
		printf("\n\n");
		printf("############## PARSE FINISH ##############\n\n");
	}
	else
	{
		printf("############## Sorry, [%s] Not exists! ##############\n\n",inputFile);
	}
	
	return 0;
}
