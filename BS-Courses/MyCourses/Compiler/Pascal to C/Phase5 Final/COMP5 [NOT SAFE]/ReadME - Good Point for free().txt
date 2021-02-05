In this phase, I was trying to free allocated memory !
in two step we allocate memory:
#############################################################################################################################
1. In Lex:

"<>"								{yylval.code=malloc(strlen(yytext)+1);strcpy(yylval.code,yytext);return S_RELOP;}
[+-]								{yylval.code=malloc(strlen(yytext)+1);strcpy(yylval.code,yytext);return S_PLUSMIN;}

++++++ So we should:

simple_expression :										
					term								
				|	
					S_PLUSMIN							{printf("%s(",$<code>1);
														free($<code>1);}
					term								
				|
														
					simple_expression
					addOp
					term								
				;
				
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$				
2. When we pass result of a non-terminal to upper level:

standard_type :		S_INTEGER 							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "int");}
					| S_REAL							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "float");}
				;
				
				
++++++ So we should:

type :				standard_type						{strcpy( $<code>$, $<code>1 );
														free($<code>1)}
					|
					S_ARRAY								
					'['									
					NUM									{low = atoi($<code>3);}
					S_DOTDOT							
					NUM									{high = atoi($<code>6);}
					']'									
					S_OF								
					standard_type						{strcpy( $<code>$, $<code>10 );
														free($<code>10)}
				;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
NOTE:
Goal:	T1		{...}
		T2		{...}
		R		{...; free($<code>5); }						/** BAD IDEA ! Beacuse 'R' always doesn't allocate memory !!  ==> Runtime Crash ***/
		
R :		 A1 A2 A3 	{ $<code>$=malloc(30);
					strcpy( $<code>$, "pass whatever");}}
		|
		B1 ',' B2 {printf("whatever");}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

