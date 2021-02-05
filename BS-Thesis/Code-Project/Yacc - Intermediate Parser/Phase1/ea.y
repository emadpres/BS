%token ID
%token NUM
%token S_VOID
%token S_BOOL
%token S_INT
%token S_FLOAT
%token S_TEXT

%token S_TRUE
%token S_FALSE
%token S_STRING

%token S_NEW
%token S_RETURN
%token S_TYPE
%token S_VAR
%token S_FUNCTION

%token S_MAIN

%union
{
	char *code;
};

%{
#include <stdlib.h>		/*** for using maaloc **/
#define NAME_MAX_LENGTH 30
#define PARAMETER_MAX_COUNT 10
int yylex(void);
/************ Declare All Needed Variables & Functions Here *****/
typedef struct{
int r, g, b;
} Color;
Color StructInit_Color(int r, int g, int b)
{
	Color c;
	c.r = r ;
	c.g = g ;
	c.b = b ;
	return c;
}

typedef struct{
char name[NAME_MAX_LENGTH];	// We prefer to not use dynamic-allocation,  because struct has no destuctor and freeing mem will be hard.
Color color;
} Type;
Type StructInit_Type(char name[], Color color)
{
	Type t ;
	strcpy(t.name, name);
	t.color = color ;
	return t;
}

typedef struct{
char name[NAME_MAX_LENGTH];
char typeName[NAME_MAX_LENGTH];
Color color;
} Variable;
Variable StructInit_Variable(char name[], char typeName[], Color color)
{
	Variable v ;
	strcpy(v.name, name);
	strcpy(v.typeName, typeName);
	v.color = color ;
	return v;
}

typedef struct{
char name[NAME_MAX_LENGTH];
char typeName[NAME_MAX_LENGTH];
int parameterCount;
Variable parameters[PARAMETER_MAX_COUNT];
} Function;
Function StructInit_Function(char name[], char typeName[], int parameterCount)
{
	Function f ;
	strcpy(f.name, name);
	strcpy(f.typeName, typeName);
	f.parameterCount = parameterCount ;
	return f;
}


%}


%%

Program : 					DeclarationList
;

DeclarationList : 			Declaration DeclarationList
							|
;

Declaration :														{ printf("Function\n");}
							FunctionDeclaration						
							|										{ printf("Type\n");} 
							TypeDeclaration
							|										{ printf("Var\n");} 
							VariableDeclaration
;

TypeDeclaration :			S_TYPE ID OptionalSuperclass '{'	
							MemberDeclarationList '}' ';'			
;

OptionalSuperclass :		':' ID
							|
;

MemberDeclarationList :		MemberDeclaration
							MemberDeclarationList
							|
;
MemberDeclaration : 		VariableDeclaration
							| FunctionDeclaration
;



FunctionDeclaration :		S_FUNCTION
							FunctionType
							FunctionName
							'('
							OptionalParameterList
							')'									
							Block								
;

FunctionName : 				S_MAIN			{printf("<MAIN\n");}
							| ID			{printf("<%s>\n",$<code>1);}
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

DeclarationOrStatementList: DeclarationOrStatement
							DeclarationOrStatementList
							|
;










TypeName :					PrimitiveType | ID
;

PrimitiveType :				S_INT
							| S_BOOL
							| S_FLOAT
							| S_STRING
;

VariableDeclaration :		S_VAR TypeName RestOfVariableDeclaration
;

RestOfVariableDeclaration:	Variable MoreVariables ';'
;

OptionalPointer :			'*' OptionalPointer
							|
;

Dimensions :				'[' NUM ']' Dimensions
							|
;

Variable :					OptionalPointer ID Dimensions
;

MoreVariables :				',' Variable
							MoreVariables 
							|
;






MoreExpressions :			',' Expression MoreExpressions
							|
;
OptionalExpression :		Expression
							|
;

Expression :				Primary					
							MoreOperand
;

MoreOperand :				'*' Primary 
							|
;

Primary :					ID MorePrimary 
							| NUM 				
							| S_TRUE
							| S_FALSE 
							| S_TEXT
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

OptionalArgumentList :		Expression MoreExpressions 		{printf(" F(...)\n");}
							|								{printf(" F()\n");}
;








DeclarationOrStatement : 	VariableDeclaration
							| KeywordStatement
							| OtherStatement
;

KeywordStatement :			Jump
;

Jump :						S_RETURN OptionalExpression ';'
;


OtherStatement :		ID MorePrimary RestOfExpressionStatement
;

RestOfExpressionStatement :		OptionalAssignment ';' ;
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
	
	Type t = StructInit_Type("emad eAmad", StructInit_Color(255,0,99) ) ;
	printf("\n####### 	%s %d" , t.name , t.color.r );
	
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
