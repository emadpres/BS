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
int SHOW_TABLE=-1;

//void yyerror(char *);
int yylex(void);

/* General Variable */
char data[100];
int counter;
int tmpInt;

void getData(char *s){
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
	int varType;
	int len; // ==-1 : not array
	int low; // ==-1 : frame entry
} VarStruct;
VarStruct symbolTable[1000];
int totalSymbol;

/* subprogram_head */
char functionName[50];
char returnType[50];
char parameters[100*50];
int SP=0;
int tabCounter=0;

int turnOfCompoundStart=-1;
int needReturn=-1;

/* identifier_list */
char varNames[100][50];
int varIndex;

/* Array boundry */
int low, high; //temp

void showSymbolTable()
{
	printf("Symbol Table\n");
	for(counter=0 ; counter<totalSymbol ; counter++ )
	{
		if(symbolTable[counter].low==-1)	{printf("------------> %s(%d)\n\n",symbolTable[counter].name,symbolTable[counter].len);continue;}
		printf("%d>\t\t%s",counter,symbolTable[counter].name);
		if(symbolTable[counter].varType==1) printf("\t\tInteger");
		else if(symbolTable[counter].varType==2) printf("\t\tFloat");
		else	printf("\tUnknown");
		if(symbolTable[counter].len!=-1) printf("\t\tYES\t\tLowerBound:%d",symbolTable[counter].low);
		printf("\n");
	}
}


%}

%%

program :		S_PROGRAM								{totalSymbol=0;SP=0;
														symbolTable[SP].low=-1;
														strcpy(symbolTable[SP].name,"Global");
														totalSymbol++;SP;}
				ID										
				'(' 									
				identifier_list
				')' ';' 								
				declarations							
				subprogram_declarations					{printf("void main()\n");
														//showSymbolTable();
														}
				compound_statement						
				'.'										{showSymbolTable();}
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
					type								{counter=tabCounter;
														while(counter--) printf("\t");
														
														counter=0;
														symbolTable[SP].len += varIndex; //first time SP=0
														if(strcmp($<code>5,"int")==0)
															tmpInt=1;
														else if(strcmp($<code>5,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
																				
														printf("%s ",$<code>5);
														while(counter<varIndex)
														{
															if(counter>0)
																printf(", %s",varNames[counter]);
															else
																printf("%s",varNames[counter]);
															strcpy(symbolTable[totalSymbol].name,varNames[counter]);
															symbolTable[totalSymbol].varType=tmpInt;
															if(low!=-1)
															{
																symbolTable[totalSymbol].low=low;
																symbolTable[totalSymbol].len=high-low;
																printf("[%d]",high-low);
															}
															else
															{
																symbolTable[totalSymbol].len=-1; //not Array
																symbolTable[totalSymbol].low=0;		// not frame entry
															}
																
															counter++;
															totalSymbol++;
															
														} free($<code>5);}
					';'									{printf(" ;\n");}
					|
				;

type :				standard_type						{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, $<code>1 );
														low=-1;high=-1;
														free( $<code>1 );}
					|
					S_ARRAY								
					'['									
					NUM									{low = atoi($<code>3);}
					S_DOTDOT							
					NUM									{high = atoi($<code>6);}
					']'									
					S_OF								
					standard_type						{$<code>$=malloc(1+strlen($<code>10));
														strcpy( $<code>$, $<code>10 );
														free( $<code>10);}
				;
				
standard_type :		S_INTEGER 							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "int");}
					| S_REAL							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "float");}
				;

subprogram_declarations :	subprogram_declarations 	{printf("\n");tabCounter++;turnOfCompoundStart=+1;
														//showSymbolTable();
														}
							subprogram_declaration 		
							';'							
							|							
						;

subprogram_declaration :	subprogram_head				{ if(returnType[0]!='\0') { printf("\t%s __%s;\n",returnType,functionName);
														//printf("\n>>>>>>>>>> %d    %d\n\n",SP,totalSymbol);
														sprintf(symbolTable[totalSymbol].name,"__%s",functionName);
														if(strcpy(returnType,"int")==0)
															symbolTable[totalSymbol].varType=1;
														else if(strcpy(returnType,"float")==0)
															symbolTable[totalSymbol].varType=2;
														else
															symbolTable[totalSymbol].varType=-1;
														symbolTable[totalSymbol].len=-1;
														symbolTable[totalSymbol].low=0;
														symbolTable[SP].len++;
														//printf("\n\n\n%s    %d\n\n\n",symbolTable[SP].name,symbolTable[SP].len);
														 totalSymbol++;}}
							declarations				
							compound_statement			{ if(SHOW_TABLE==-1) totalSymbol -= (symbolTable[SP].len+1) ;}
															
						;
						
subprogram_head : 	S_FUNCTION							
					ID									{needReturn=+1;
														getData($<code>2);strcpy(functionName,data);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														symbolTable[SP].len=0;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
					arguments							{free($<code>4);}
					':'									
					standard_type						{printf("%s %s %s\n{\n",$<code>6,functionName,$<code>4);strcpy(returnType,$<code>6);}
					';'									{printf("\n");}
				|
					S_PROCEDURE							
					ID									{getData($<code>2);strcpy(functionName,data);
														printf("void %s",functionName);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														symbolTable[SP].len=0;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
					arguments							{printf("%s\n{\n",$<code>4);returnType[0]='\0';free($<code>4);}
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
														symbolTable[SP].len += varIndex ;
														if(strcmp($<code>3,"int")==0)
															tmpInt=1;
														else if(strcmp($<code>3,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,$<code>3);
															strcat(parameters," ");
															strcat(parameters,varNames[counter]);
															strcpy(symbolTable[totalSymbol].name,varNames[counter]);
															symbolTable[totalSymbol].varType=tmpInt;
		
															if(low!=-1)
															{
																symbolTable[totalSymbol].low=low;
																symbolTable[totalSymbol].len=high-low;
																sprintf(data,"[%d]",high-low);
																strcat(parameters,data);
															}
															else
															{
																symbolTable[totalSymbol].len=-1;
																symbolTable[totalSymbol].low=0;
															}
															totalSymbol++;
															counter++;
														}
														}
				|
					parameter_list 						
					';'									{strcat(parameters,", ");}
					identifier_list						
					':'									
					type								{counter=0;
														symbolTable[SP].len += varIndex ;
														if(strcmp($<code>6,"int")==0)
															tmpInt=1;
														else if(strcmp($<code>6,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,$<code>6);
															strcat(parameters," ");
															strcat(parameters,varNames[counter]);
															strcpy(symbolTable[totalSymbol].name,varNames[counter]);
															symbolTable[totalSymbol].varType=tmpInt;
															if(low!=-1)
															{
																symbolTable[totalSymbol].low=low;
																symbolTable[totalSymbol].len=high-low;
																sprintf(data,"[%d]",high-low);
																strcat(parameters,data);
															}
															else
															{
																symbolTable[totalSymbol].len=-1;
																symbolTable[totalSymbol].low=0;
															}
															totalSymbol++;
															counter++;
														}
														//printf("_%s",parameters);
														}
				;


compound_statement:	S_BEGIN								{if(turnOfCompoundStart==+1) {printf("\n");turnOfCompoundStart=-1;}
														else {printf("{\n");tabCounter++;}
														counter=tabCounter;
														while(counter--) printf("\t");}
					optional_statements
					S_END								{
														if(needReturn==+1 && tabCounter==1)
														{
														needReturn=-1;
														printf("return __%s;\n",symbolTable[SP].name);
														}
					
														tabCounter--;
														counter=tabCounter;
														printf("\n");
														while(counter--) printf("\t");
														printf("}\n");}



optional_statements :	statement_list					{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
					|									//{printf(" <Empty Body>\n");}
					;
					
statement_list :	statement							
				|
					statement_list						
					';'									{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
					statement							
				;

statement :		variable
				S_ASSIGN								{printf(" = ");}
				expression								{printf(" ;");
														counter=tabCounter;
														while(counter--) printf("\t");}
			|	
				procedure_statement						{printf(" ;\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
			|
														
				compound_statement						
			|
				S_IF									{counter=tabCounter;
														//printf(">");
														//while(counter--) printf("P\t");
														printf("if (");}
				expression							
				S_THEN									{tabCounter++;printf(" )\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
				statement								{tabCounter--;}
				S_ELSE									{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");
														printf("else\n");tabCounter++;counter=tabCounter;
														while(counter--) printf("\t");
														}
				statement								{tabCounter--;}
			|
				S_WHILE									{counter=tabCounter-1;
														while(counter--) printf("\t");
														printf("while( ");}
				expression
				S_DO									{printf(" )");}
				statement								
			;

variable :	ID											{ getData($<code>1); if(strcmp(data,symbolTable[SP].name)==0)	printf("__%s",data);
																			else	printf("%s",data);	}	
		|
			ID 											{getData($<code>1);printf("%s",data);}
			'['											{printf("[");}
			expression 									{getData($<code>1);
														counter=totalSymbol;
														//showSymbolTable();
														//printf(">>>>%d",totalSymbol);
														for(;counter>0;counter--)
														{
															//printf("X%sX ? X%sX\n",data,symbolTable[counter].name);
															if( symbolTable[counter].low==-1 ||
																strcmp(data,symbolTable[counter].name)!=0 )
																	continue;
															printf("-%d",symbolTable[counter].low);
															break;
														}}														
			']'											{printf("]");}
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
					','									{printf(", ");}
					expression
				;

expression :	simple_expression						
			|
														//{printf("(E(");}
				simple_expression
				S_RELOP									{strcpy(data,$<code>2);
														//printf("::%s",data);
														if(strcmp(data,"=")==0)
															printf("==");
														else if(strcmp(data,"<>")==0)
															printf("!=");
														else
															printf("%s",data);}
				simple_expression						//{printf(")E)");}
			;

			
simple_expression :										//{printf("(T(");}
					term								//{printf(")T)");}
				|	
					S_PLUSMIN							{printf("%s(",$<code>1);}
					term								{printf(" )");}
				|
														//{printf("(");}
					simple_expression
					addOp
					term								//{printf(")");}
				;

addOp:	S_PLUSMIN										{printf("%s",$<code>1);}
	|
		S_OR											{printf("||");}
	;
	
term :	factor										//	{printf("<F>");}
	|
		term										//	{printf("<T>");}
		S_MULOP											{strcpy(data,$<code>2);
														if(strcmp(data,"mod")==0)
															printf("%%");
														else if(strcmp(data,"and")==0)
															printf("&&");
														else if(strcmp(data,"div")==0)
															printf("/");
														else
															printf("%s",data);}
		factor
	;

factor :	ID											{ getData($<code>1); if(strcmp(data,symbolTable[SP].name)==0)	printf("__%s",data);
																			else	printf("%s",data);	
														/*counter=totalSymbol;
														for(;counter>0;counter--)
														{
															printf("XX%sXX != XX%sXX\n",symbolTable[counter].name,data);
															if( symbolTable[counter].low==-1 ||
																strcmp(data,symbolTable[counter].name)!=0 )
																	continue;
															counter=-100;
															break;
														
														}
														if(counter!=-100)
															printf("\t// Warning: This variable has not define !");*/
															
														}	
		|
			ID 											{getData($<code>1);printf("%s",data);}
			'('											{printf("(");}
			expression_list 
			')'											{printf(" )");}
		|
			NUM											{printf("%s",$<code>1);}
		|
			'('											{printf("(");}	
			expression 
			')'											{printf(" )");}
		|
			S_NOT										{printf("!( ");}
			factor										{printf(" )");}
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
