%union
{
	char *code;
};
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

char data[100];
void getData(char *s)
{
	int i=0;
	strcpy(data,s);
//	printf("D:%s",data);
	for(;data[i]!='\0';i++)
		if( !(
			(data[i]<='Z' && data[i]>='A' )
				|| (data[i]<='z' && data[i]>='a' )
					|| (data[i]<='9' && data[i]>='0' ) ) )
					break;
					
	data[i]='\0';
	//printf("D*:%s",data);
}


typedef struct{
	char name[50];
	int VarType;
	int len;
} VarStruct;
VarStruct myVariables[100];

/* subprogram_head */
char functionName[50];
char parameters[100*50];

/* identifier_list */
char varNames[100][50];
int varIndex;

/* Array boundry */
int low, high; //temp
char arrayVarNames[100][50];
int arrayVarLowBoundry[100];

int counter;
%}

%%

program :		S_PROGRAM								
				ID										
				'(' 									
				identifier_list
				')' ';' 								
				declarations							
				subprogram_declarations					{printf("void main()\n");}
				compound_statement						
				'.'										
				|										{printf("<Empty Input>");}
			;

identifier_list :	ID									{varIndex=0; 
														strcpy( varNames[varIndex++], $<code>1);}
					|
					identifier_list
					','
					ID									{strcpy( varNames[varIndex++], $<code>3);}
				;

declarations :		declarations
					S_VAR								
					identifier_list						
					':'									
					type								{counter=0;
														printf("%s ",$<code>5);
														while(counter<varIndex)
														{
															if(counter>0)
																printf(", %s",varNames[counter++]);
															else
																printf("%s",varNames[counter++]);
															if(low!=-1)
															{
																printf("[%d]",high-low);
															}
														} }
					';'									{printf(" ;\n");}
					|
				;

type :				standard_type						{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, $<code>1 );
														low=-1;high=-1;}
					|
					S_ARRAY								
					'['									
					NUM									{low = atoi($<code>3);}
					S_DOTDOT							
					NUM									{high = atoi($<code>6);}
					']'									
					S_OF								
					standard_type						{$<code>$=malloc(1+strlen($<code>10));
														strcpy( $<code>$, $<code>10 );}
				;
				
standard_type :		S_INTEGER 							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "int");}
					| S_REAL							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "float");}
				;

subprogram_declarations :	subprogram_declarations 	{printf("\n");}
							subprogram_declaration 
							';'							
							|							//{printf("\n<NoSubFunction>");}
						;

subprogram_declaration :	subprogram_head
							declarations
							compound_statement			//{printf(" \n}\n");}
						;
						
subprogram_head : 	S_FUNCTION							//{printf(" Function");}
					ID									//{strcpy(functionName,$<code>1);}
					arguments							
					':'									
					standard_type						{getData($<code>2); printf("%s %s %s\n{\n",$<code>5,data,$<code>3);}
					';'									{printf("\n");}
				|
					S_PROCEDURE							
					ID									{printf("void %s",$<code>2);}
					arguments							{printf("%s\n{\n",$<code>4);}
					';'									
				;

arguments :		'('										{strcpy(parameters,"");}
				parameter_list							
				')'										{$<code>$=malloc(1+5+strlen(parameters));
														sprintf(data,"(%s)",parameters);
														strcpy( $<code>$, data);}
														
			|
			;

parameter_list :	identifier_list 					
					':'									
					type								{counter=0;
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,$<code>3);
															strcat(parameters," ");
															strcat(parameters,varNames[counter]);
															if(low!=-1)
															{
																sprintf(data,"[%d]",high-low);
																strcat(parameters,data);
															}
															counter++;
														}
														//printf("__%s",parameters);
														}
				|
					parameter_list 						
					';'									{strcat(parameters,", ");}
					identifier_list						
					':'									
					type								{counter=0;
														
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,$<code>6);
															strcat(parameters," ");
															strcat(parameters,varNames[counter]);
															if(low!=-1)
															{
																sprintf(data,"[%d]",high-low);
																strcat(parameters,data);
															}
															counter++;
														}
														//printf("_%s",parameters);
														}
				;


compound_statement:	S_BEGIN								{printf(" \n{\n");}
					optional_statements
					S_END								{printf(" \n}\n");}



optional_statements :	statement_list
					|									//{printf(" <Empty Body>\n");}
					;
					
statement_list :	statement							//{printf(" ;-;\n");}
				|
					statement_list						
					';'									//{printf(" ;;\n");}
					statement							//{printf(" ;+;\n");}
				;

statement :		variable
				S_ASSIGN								{printf(" = ");}
				expression								{printf(" ;\n");}
			|	
				procedure_statement						{printf(" ;\n");}
			|
														//{printf("\n{\n");}
				compound_statement						//{printf("\n}\n");}
			|
				S_IF									{printf("if (");}
				expression							
				S_THEN									{printf(" )");}
				statement							
				S_ELSE									{printf(" \nelse\n");}
				statement						
			|
				S_WHILE									{printf("while (");}
				expression
				S_DO									{printf(" )");}
				statement
			;

variable :	ID											{getData($<code>1);printf("%s ",data);}	
		|
			ID 											{getData($<code>1);printf("%s ",data);}
			'['											{printf("[");}
			expression 									{printf("-LOW");}
			']'											{printf("] ");}
		;


procedure_statement :	ID								{printf("%s()",$<code>1);}
					|
						ID								{getData($<code>1);
														printf("%s",data);}
						'('								{printf("( ");}
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
														//{printf("(E(");}
				simple_expression
				S_RELOP									{strcpy(data,$<code>2);
														//printf("::%s",data);
														if(strcmp(data,"=")==0)
															printf(" == ");
														else if(strcmp(data,"<>")==0)
															printf(" != ");
														else
															printf(" %s ",data);}
				simple_expression						//{printf(")E)");}
			;

			
simple_expression :										//{printf("(T(");}
					term								//{printf(")T)");}
				|	
					S_PLUSMIN							{printf("(%s( ",$<code>1);}
					term								{printf("))");}
				|
														//{printf("(");}
					simple_expression
					addOp
					term								//{printf(")");}
				;

addOp:	S_PLUSMIN										{printf("%s ",$<code>1);}
	|
		S_OR											{printf(" or ");}
	;
	
term :	factor										//	{printf("<F>");}
	|
		term										//	{printf("<T>");}
		S_MULOP											{strcpy(data,$<code>2);
														//printf("::%s::",data);
														if(strcmp(data,"mod")==0)
															printf(" %% ");
														else if(strcmp(data,"and")==0)
															printf("> & ");
														else
															printf(" %s ",data);}
		factor
	;

factor :	ID											{getData($<code>1);printf("%s",data);}
		|
			ID 											{getData($<code>1);printf("%s",data);}
			'('											{printf(" (");}
			expression_list 
			')'											{printf(" )");}
		|
			NUM											{printf(" %s ",$<code>1);}
		|
			'('											{printf(" (");}	
			expression 
			')'											{printf(" )");}
		|
			S_NOT										{printf(" !( ");}
			factor										{printf(" ) ");}
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

	yyin = fopen("t.pas", "r");
	printf("Goind to parse\n\n");
	yyparse();
	printf("\n\nParse Done !!!!!");
	fclose(yyin);
	//getch();
	return 0;
}
