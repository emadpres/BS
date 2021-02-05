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
%token S_ASSERT
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
#include "dataTypes.h"

int yylex(void);
/************ Declare All Needed Variables & Functions Here *****/

extern pRoot;	// GOOD: Algouth `pRoot` is not `void*` and is `class*` ( defined in cpp), `extern` bring it as `voide*` to be accessible in C;
int isInitialized;

/*
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
*/



%}


%%

Program : 													{	frames[0] = pRoot;
																curFrameIndex = 0;
																typeInheritanceNode = New_Element("TypeInheritance", frames[curFrameIndex]);
																InitialPrimaryDataTypeNode(typeInheritanceNode);
																globalDataTypeNode = New_Element("GlobalType", frames[curFrameIndex]);
																globalVarNode = New_Element("GlobalVar", frames[curFrameIndex]);
																globalFuncNode = New_Element("GlobalFunction", frames[curFrameIndex]);
																
															}
							DeclarationList					{	Set_Attribute_Int(globalDataTypeNode, "count", globalDataTypeCount);
																Set_Attribute_Int(globalVarNode, "count", globalVarCount);
																Set_Attribute_Int(globalFuncNode, "count", globalFuncCount);
															}
;

DeclarationList : 			Declaration DeclarationList
							|
;

Declaration :														{ printf("DataType\n");} 
							TypeDeclaration
							|										{ printf("Function\n");}
							FunctionDeclaration						
							|										{ printf("Var\n");} 
							VariableDeclaration
;

TypeDeclaration :			S_TYPE 							{	isDefiningType = 1;	
																typedefinitionFieldsCount = typedefinitionFunctionsCount = 0 ;
															}
							ID 								{	
																strcpy(curVar.name, $<code>3);
																// Adding In Type Inheritance
																
																// Creating DataType
																if( curFrameIndex == 0)
																{
																	printf("------- >> %d \n",curFrameIndex);
																	frames[curFrameIndex+1] = New_Element( $<code>3, globalDataTypeNode);
																	curFrameIndex++;
																	globalDataTypeCount++;
																}
																else
																{// Bug !!! 
																	printf("BBBBBBBB >> %d \n",curFrameIndex);
																}
																typedefinitionFieldsNode = New_Element("Field", frames[curFrameIndex]);
																typedefinitionFunctionsNode = New_Element("Function", frames[curFrameIndex]);
															}
															
							OptionalSuperclass '{'	
							MemberDeclarationList 
							'}' ';'							{	Set_Attribute_Int(typedefinitionFieldsNode, "count", typedefinitionFieldsCount);
																Set_Attribute_Int(typedefinitionFunctionsNode, "count", typedefinitionFunctionsCount);
																curFrameIndex--;
																isDefiningType = 0;
															}
;

OptionalSuperclass :		':' ID								{
																	void * g, *t, *delCandidate;
																	int size=-1;
																	int notFinished = 1;
																	char nodeValue[NAME_MAX_LENGTH];
																	g = Find_Element(typeInheritanceNode, "Group");
																	while( notFinished && g != NULL)
																	{
																		size = 0 ;
																		t = Find_Element(g,NULL);	// = FirstChild()
																		while( notFinished && t != NULL)
																		{
																			size++;
																			strcpy( nodeValue, Get_Element_Name(t) );
																			//printf("Type : %s    Size:%d\n", nodeValue, size);
																			if ( strcmp(nodeValue, $<code>2) == 0 )
																			{
																				notFinished = 0 ;
																				// Deleting Next Sibiling : We Just suppoert linreal inherince
																				delCandidate = Next_Sibling_Element(t, NULL);
																				while(delCandidate!=NULL)
																				{
																					Delete_Element(g,delCandidate);
																					delCandidate = Next_Sibling_Element(t, NULL);
																				}
																				//
																				t = New_Element( curVar.name, g);
																				Set_Attribute_Int( t, "size", size+1);
																			}
																			printf("NOOOOOT %s\n",nodeValue);
																			t = Next_Sibling_Element(t, NULL);
																		}
																		/////
																		g = Next_Sibling_Element(g, "Group");
																	}
																	if(notFinished==1)
																	{
																		printf("Sorry, You're inheritinf from undefined Type = %s ! (Bug) \n",$<code>2);
																	}
																}
							|									{
																	void * g, *t;
																	int groupID = 1 ;
																	g = Find_Element(typeInheritanceNode, "Group");
																	while( g != NULL)
																	{
																		groupID++;
																		g = Next_Sibling_Element(g, "Group");
																	}
																	// Creating New Group
																	g = New_Element( "Group", typeInheritanceNode);
																	Set_Attribute_Int( g, "id", groupID);	// First Child of Group
																	t = New_Element( curVar.name, g);
																	Set_Attribute_Int( t, "size", 1);	// First Child of Group
																}
;

MemberDeclarationList :		MemberDeclaration
							MemberDeclarationList
							|
;
MemberDeclaration : 		VariableDeclaration
							| FunctionDeclaration
;



FunctionDeclaration :		S_FUNCTION						{	if( curFrameIndex == 0)
																{
																	frames[curFrameIndex+1] = New_Element("Function", globalFuncNode);
																	curFrameIndex++;
																	globalFuncCount++;
																}
																else if(isDefiningType)
																{
																	frames[curFrameIndex+1] = New_Element("Function", typedefinitionFunctionsNode);
																	curFrameIndex++;
																	typedefinitionFunctionsCount++;
																}
																else	// Functio Body
																{
																	printf("BBBBBBBBBug !!!!!!!!!!!!!!!!!!!!! 345344 \n");
																	//frames[curFrameIndex+1] = New_Element("Function", frames[curFrameIndex]);
																	//curFrameIndex++;
																}
																// Current Scope : Function
																returnCount=0;paramCount=0;
															}
							FunctionType
							FunctionName					{	void *returns, *type;
																Set_Attribute_String( frames[curFrameIndex], "name", $<code>4);
																// Return
																returns = New_Element("Returns", frames[curFrameIndex]);
																returnCount = 1;
																Set_Attribute_Int(returns, "count", returnCount);
																// 
																type = New_Element("Type", returns);
																Set_Attribute_String(type, "baseType", curType.baseType);
																Set_Attribute_Int(type, "array", curType.arrayLength);
																// Param
																curFunctionParamNode = New_Element("Param", frames[curFrameIndex]);
																paramCount=0;
															}
							'('								{}
							OptionalParameterList
							')'								{	Set_Attribute_Int(curFunctionParamNode, "count", paramCount);
																frames[curFrameIndex+1] = New_Element("Body", frames[curFrameIndex]);
																curFrameIndex++;
																// Current Scope : Function::Body
															}			
							Block							{	curFrameIndex--;	// Function::Body
																curFrameIndex--; 	// Function
															}	
;

FunctionName : 				S_MAIN							{	$<code>$=malloc(1+strlen("main"));
																strcpy( $<code>$, "main" );
															}
							| ID							{	$<code>$=malloc(1+strlen($<code>1));
																strcpy( $<code>$, $<code>1 );
															}
;

FunctionType :				S_VOID							{	strcpy(curType.baseType, "void");	}	
							| TypeName 
;

OptionalParameterList :		Parameter MoreParameters 
							|
;

Parameter :					TypeName
							Variable						{	 void *type;
																paramCount++;
																type = New_Element("Type", curFunctionParamNode);
																Set_Text_String(type, curVar.name); 
																Set_Attribute_String(type, "baseType", curType.baseType);
																Set_Attribute_Int(type, "array", curType.arrayLength);
															}
;

MoreParameters :			','
							Parameter 
							MoreParameters 
							|
;

Block :						'{' 							{	/* Start of a new function*/	}
							DeclarationOrStatementList 
							'}'								{	/* if we had nested body, we should curScopeNode=parentScope */ }
;

DeclarationOrStatementList: DeclarationOrStatement
							DeclarationOrStatementList
							|
;










TypeName :					PrimitiveType 				
							| ID							{	strcpy(curVar.type->baseType, $<code>1);	}
;				
				
PrimitiveType :				S_INT							{	strcpy(curVar.type->baseType, "int");	}
							| S_BOOL						{	strcpy(curVar.type->baseType, "bool");	}
							| S_FLOAT						{	strcpy(curVar.type->baseType, "float");	}
							| S_STRING						{	strcpy(curVar.type->baseType, "string");	}
;

VariableDeclaration :		S_VAR TypeName RestOfVariableDeclaration
;

RestOfVariableDeclaration:	Variable 						{	 void *type;
																if ( curFrameIndex == 0)
																{
																	printf("****** %s\n",curVar.name);
																	type = New_Element("Type", globalVarNode);
																	globalVarCount++;
																}
																else if(isDefiningType)
																{
																	type = New_Element("Type", typedefinitionFieldsNode);
																	typedefinitionFieldsCount++;
																}
																else	// Functio Body
																{
																	type = New_Element("Type", frames[curFrameIndex]);
																	Set_Attribute_Int(type, "ref_lineNumber", lineNo);
																}
																if(isInitialized==1)
																	Set_Attribute_String(type, "initial", "true");
																else
																	Set_Attribute_String(type, "initial", "false");
																Set_Text_String(type, curVar.name); 
																Set_Attribute_String(type, "baseType", curVar.type->baseType);
																Set_Attribute_Int(type, "array", curVar.type->arrayLength);
															}
							MoreVariables ';'
;

OptionalPointer :			'*' OptionalPointer
							|
;

Dimensions :				'[' NUM ']'						{	/*int temp;
																sscanf( $<code>2,"%d", &temp);
																curType.isArray = temp ;*/
															}
							|
;

InitialValue : 				ID '(' ')' | NUM |S_TRUE | S_FALSE | S_TEXT
;

OptionalInitial :			'='								{	isInitialized=1;	}
							InitialValue						
							|
;

Variable :					OptionalPointer 
							ID								{	isInitialized=0;
																curVar.type->arrayLength=-1;
																strcpy(curVar.name, $<code>2);
															}
							Dimensions
							OptionalInitial
;

MoreVariables :				',' Variable					{	 void *type;
																if ( curFrameIndex == 0 )
																{
																	printf("****** %s\n",curVar.name);
																	type = New_Element("Type", globalVarNode);
																	globalVarCount++;
																}
																else if(isDefiningType)
																{
																	type = New_Element("Type", typedefinitionFieldsNode);
																	typedefinitionFieldsCount++;
																}
																else	// Functio Body
																{
																	type = New_Element("Type", frames[curFrameIndex]);
																	Set_Attribute_Int(type, "ref_lineNumber", lineNo);
																}
																Set_Text_String(type, curVar.name); 
																if(isInitialized==1)
																	Set_Attribute_String(type, "initial", "true");
																else
																	Set_Attribute_String(type, "initial", "false");
																Set_Attribute_String(type, "baseType", curVar.type->baseType);
																Set_Attribute_Int(type, "array", curVar.type->arrayLength);
															}
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

MoreOperand :				'*' 							{	pointer = 3 ; 
																Set_Attribute_Int(rightOfAssignmet, "count" , 2 );
																curPrimaryNode = New_Element("Primary", rightOfAssignmet); 
															}
							Primary 
							|
;

MorePrimary :			',' 								{	// Here we handling 2nd and more Paramter of a function call
																paramCount++;
																// For remembering code, change "Primary" to "CallParameter-Primary"
																curPrimaryNode = New_Element("Primary", curCallNode); 
															} 
						Primary							
						MorePrimary
						|
;

Primary :					ID 								{	strcpy(curVar.name, $<code>1);
																subPrimary = SUBPRIMARY_None;
															}
							SubPrimary 						{	switch(subPrimary)
																{
																case SUBPRIMARY_None:
																	// We come here for both: 1)a at ..Foo(a)..   2)b at ..=b*..
																	Set_Attribute_String(curPrimaryNode, "source" , "var" );
																	Set_Text_String(curPrimaryNode, $<code>1);
																	break;
																case SUBPRIMARY_FunctionCall:
																	break;
																default:
																	printf(" Why Default SubPrimary .. Bug ? \n");
																	break;
																}
															}
						| NUM 							{		void *type=NULL;
																unsigned int i=0;
																Set_Attribute_String(curPrimaryNode, "source" , "data" );
																
																for(; i< strlen($<code>1); i++ )
																	if($<code>1[i] == '.' )
																		break;
																if( i < strlen($<code>1) )
																{
																	// Put Float DataType Node
																	Set_Attribute_String(curPrimaryNode, "source" , "data" );
																	type = New_Element("Type", curPrimaryNode);
																	Set_Attribute_String(type, "baseType", "float");
																	Set_Attribute_Int(type, "array", -1);
																}
																else
																{
																	// Put Int DataType Node
																	Set_Attribute_String(curPrimaryNode, "source" , "data" );
																	type = New_Element("Type", curPrimaryNode);
																	Set_Attribute_String(type, "baseType", "int");
																	Set_Attribute_Int(type, "array", -1);
																}
															}
							| S_TRUE						{	void *type=NULL;
																Set_Attribute_String(curPrimaryNode, "source" , "data" );
																type = New_Element("Type", curPrimaryNode);
																Set_Attribute_String(type, "baseType", "bool");
																Set_Attribute_Int(type, "array", -1);
															}
							| S_FALSE 						{	
																void *type=NULL;
																Set_Attribute_String(curPrimaryNode, "source" , "data" );
																type = New_Element("Type", curPrimaryNode);
																Set_Attribute_String(type, "baseType", "bool");
																Set_Attribute_Int(type, "array", -1);
															}
							| S_TEXT						{	void *type=NULL;
																Set_Attribute_String(curPrimaryNode, "source" , "data" );
																type = New_Element("Type", curPrimaryNode);
																Set_Attribute_String(type, "baseType", "string");
																Set_Attribute_Int(type, "array", -1);
															}
;

SubPrimary :				ArrayAccess 					{	subPrimary = SUBPRIMARY_ArrayAccess ; }
							| FieldAccess 					{	subPrimary = SUBPRIMARY_FieldAccess ; }
							| 								{	subPrimary = SUBPRIMARY_FunctionCall ; }
							FunctionCall 					
							|
;

ArrayAccess :				'[' Expression ']' SubPrimary  
;

FieldAccess :				'.' ID SubPrimary
;

FunctionCall : 				'(' 						 	{	
																void *pElement= NULL, *type=NULL;
																curCallNode=NULL;
																if ( pointer == 1 )
																{
																	// It mean : Foo(...);
																	pointer = -1 ;	// we have no Left + just >> a simple Function Call
																	Set_Attribute_Int(leftOfAssignmet, "count" , 0 );
																	Set_Attribute_Int(rightOfAssignmet, "count" , 1 );
																	curCallNode = New_Element("Primary", rightOfAssignmet);
																	Set_Attribute_String(curCallNode, "source" , "call" );
																	curCallNode = New_Element("Call", curCallNode);
																	Set_Attribute_String(curCallNode, "name" , curVar.name );
																	Set_Attribute_Int(curCallNode, "argCount" , -1 );
																	paramCount = -1 ;
																	
																}
																else if(  pointer == 2  || pointer == 3 )
																{
																	// It mean:		...= Foo(..)*...  -OR-  ...=....*Foo(..)
																	// Foo() here may refer to function call 
																	// or creating object of Foo data-type
																	
																	pElement = Find_Element(globalDataTypeNode, curVar.name);
																	if(pElement==NULL)
																	{
																		// Function Call
																		Set_Attribute_String(curPrimaryNode, "source" , "call" );
																		curCallNode = New_Element("Call", curPrimaryNode);
																		Set_Attribute_String(curCallNode, "name" , curVar.name );
																		Set_Attribute_Int(curCallNode, "argCount" , -1 );
																		paramCount = -1 ;
																	}
																	else
																	{
																		// Creating DataType Object
																		Set_Attribute_String(curPrimaryNode, "source" , "data" );
																		type = New_Element("Type", curPrimaryNode);
																		Set_Attribute_String(type, "baseType", curVar.name);
																		Set_Attribute_Int(type, "array", -1);
																	}
																	
																	
																}
																	
																pointer += 10 ;
															}
							OptionalArgumentList ')'		{	subPrimary = SUBPRIMARY_FunctionCall;	// parameter may have changed it
																pointer -= 10 ; 
																if(curCallNode != NULL)	// happen when Foo(), Foo is DataType Object Creation not function call
																	Set_Attribute_Int(curCallNode, "argCount" , paramCount );
															}
							SubPrimary 
;

OptionalArgumentList :										{	paramCount=1;
																// For remembering code, change "Primary" to "CallParameter-Primary"
																curPrimaryNode = New_Element("Primary", curCallNode); 
															}
							Primary 						
							MorePrimary 					
							|								{	paramCount=0; 	}
;








DeclarationOrStatement : 	VariableDeclaration
							| KeywordStatement
							| OtherStatement
;

KeywordStatement :			Jump | Asserts
;

OptionalID :				ID								{	strcpy(curVar.name, $<code>1); }
							|								{	strcpy(curVar.name, ""); }
;

Jump :						S_RETURN 
							OptionalID ';'					{	void *st = New_Element("Return", frames[curFrameIndex]);
																if( strcmp( curVar.name, "" ) != 0 )
																	Set_Text_String(st, curVar.name);
															}
;

Asserts :					DataTypeAssert
;

DataTypeAssert :			S_ASSERT '('
							ID ','					
							TypeName ')' ';'				{	void *st;
																st = New_Element("Assert", frames[curFrameIndex]);
																Set_Attribute_String(st, "baseType", curVar.type->baseType);
																Set_Attribute_Int(st, "array", -1);
																Set_Text_String(st, $<code>3);
															}
;


OtherStatement :		ID									{	void *st;
																strcpy(curVar.name, $<code>1); // Used by "Foo(..);" in FunctionCall Rule
																pointer = 1 ;	// Notice how pointer change to next numbers
																st = New_Element("Assignment", frames[curFrameIndex]);
																Set_Attribute_Int(st, "ref_lineNumber", lineNo);
																leftOfAssignmet = New_Element("Left", st);
																rightOfAssignmet = New_Element("Right", st);
																//Set_Attribute_Int(rightOfAssignmet, "count" , 0 );
																
																subPrimary = SUBPRIMARY_None ;
															}
						SubPrimary							{	// Handling `Left` Assignment-Element
																switch(subPrimary)
																{
																case SUBPRIMARY_None:
																	Set_Text_String(leftOfAssignmet, $<code>1);
																	break;
																case SUBPRIMARY_FunctionCall:
																	// It mean code is "Foo();" and we have handled it.
																	// and pointer = -1.
																	// and we will have not `=...`
																	break;
																default:
																	printf(" Why Default SubPrimary .. Bug ? \n");
																	break;
																}
															}
						RestOfExpressionStatement
;

RestOfExpressionStatement :		OptionalAssignment ';' 		{	pointer=-1; }
;

OptionalAssignment :			'=' 						{	if(pointer == -1 )
																{
																	printf("Sorry, You can't \"Foo() = .... \" <Bug>\n");
																}
																
																pointer = 2 ; 
																curPrimaryNode = New_Element("Primary", rightOfAssignmet); 
																Set_Attribute_Int(rightOfAssignmet, "count" , 1 );
																// Handling `Right` Assignment-Element from here
															}				
								Expression 					
								| 
;

//printf("$$%s$$%d$$",curVar.name,pointer );

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
	
	//Type t = StructInit_Type("emad eAmad", StructInit_Color(255,0,99) ) ;
	//printf("\n####### 	%s %d" , t.name , t.color.r );
	
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
