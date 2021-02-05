#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
#line 1 "yea.y"
typedef union
{
	char *code;
} YYSTYPE;
#line 33 "yea.y"

/*void yyerror(char *);*/
int yylex(void);

/* General Variable */
char data[100];
int counter;
int tmpInt;

void getData(char *s){
	int i=0;
	strcpy(data,s);
/*	printf("D:%s",data);*/
	for(;data[i]!='\0';i++)
		if( !(
			(data[i]<='Z' && data[i]>='A' )
				|| (data[i]<='z' && data[i]>='a' )
					|| (data[i]<='9' && data[i]>='0' ) ) )
					break;
					
	data[i]='\0';
	/*printf("D*:%s",data);*/
}


typedef struct{
	char name[50];
	int varType;
	int len; /* ==-1 : not array*/
	int low; /* ==-1 : frame entry*/
} VarStruct;
VarStruct symbolTable[1000];
int totalSymbol;

/* subprogram_head */
char functionName[50];
char parameters[100*50];
int SP=0;
int tabCounter=0;
int turnOfCompoundStart=0;
/* identifier_list */
char varNames[100][50];
int varIndex;

/* Array boundry */
int low, high; /*temp*/

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


#line 75 "y.tab.c"
#define ID 257
#define NUM 258
#define S_PROGRAM 259
#define S_VAR 260
#define S_ARRAY 261
#define S_DOTDOT 262
#define S_OF 263
#define S_INTEGER 264
#define S_REAL 265
#define S_FUNCTION 266
#define S_PROCEDURE 267
#define S_BEGIN 268
#define S_END 269
#define S_IF 270
#define S_THEN 271
#define S_ELSE 272
#define S_WHILE 273
#define S_DO 274
#define S_RELOP 275
#define S_ASSIGN 276
#define S_PLUSMIN 277
#define S_OR 278
#define S_MULOP 279
#define S_NOT 280
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    1,    6,    0,    0,    2,    2,    8,    3,    3,    7,
   10,   11,    7,    9,    9,   13,    4,    4,   12,   16,
   17,   14,   18,   19,   14,   21,   15,   15,   20,   22,
   20,   24,    5,   23,   23,   25,   25,   29,   26,   26,
   26,   31,   32,   33,   26,   34,   35,   26,   27,   36,
   37,   38,   27,   30,   39,   41,   30,   40,   42,   40,
   28,   44,   28,   43,   46,   43,   43,   47,   47,   45,
   49,   45,   48,   50,   51,   48,   48,   52,   48,   53,
   48,
};
short yylen[] = {                                         2,
    0,    0,   12,    0,    1,    3,    0,    7,    0,    1,
    0,    0,   10,    1,    1,    0,    4,    0,    3,    0,
    0,    8,    0,    0,    6,    0,    4,    0,    3,    0,
    6,    0,    4,    1,    0,    1,    3,    0,    4,    1,
    1,    0,    0,    0,    9,    0,    0,    6,    1,    0,
    0,    0,    7,    1,    0,    0,    6,    1,    0,    4,
    1,    0,    4,    1,    0,    3,    3,    1,    1,    1,
    0,    4,    1,    0,    0,    6,    1,    0,    4,    0,
    3,
};
short yydefred[] = {                                      0,
    1,    0,    0,    0,    0,    5,    0,    0,    0,    9,
    6,    0,    0,    0,    0,    0,    0,    0,   32,    0,
    0,    0,    0,    9,    0,   14,   15,    7,   10,    0,
    3,   20,   23,   17,    0,    0,    0,    0,   42,   46,
   41,    0,    0,   36,    0,   40,    0,    0,   19,   11,
    8,    0,    0,    0,    0,   33,    0,   38,   26,    0,
   24,    0,   51,   56,    0,   77,   65,   80,   78,    0,
    0,    0,   70,    0,   37,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   43,   62,   68,   69,
    0,   71,   47,   39,    0,    0,   21,   25,   12,   52,
   58,    0,   75,    0,   81,    0,    0,    0,    0,    0,
    0,    0,   27,   30,    0,    0,    0,   57,   59,    0,
   79,    0,    0,   72,   48,   29,    0,   22,    0,   53,
    0,    0,   44,    0,    0,   60,   76,    0,    0,   13,
   45,   31,
};
short yydgoto[] = {                                       2,
    3,    7,   12,   14,   41,   16,   28,   37,   29,   62,
  116,   23,   17,   24,   60,   47,  115,   48,   79,   96,
   77,  127,   42,   30,   43,   44,   45,  101,   76,   46,
   54,  107,  138,   55,  111,   52,   81,  117,   53,  102,
   82,  131,   71,  108,   72,   84,   91,   73,  110,   83,
  120,   86,   85,
};
short yysindex[] = {                                   -241,
    0,    0, -231,    5, -194,    0,   28,   11, -180,    0,
    0, -169, -194,    0,  -29, -174, -216, -244,    0,   49,
 -160, -159,   40,    0,    9,    0,    0,    0,    0, -232,
    0,    0,    0,    0, -249, -157,   43,    0,    0,    0,
    0, -166,   45,    0, -171,    0,   66,   66,    0,    0,
    0,   17,   69,  -40,  -40,    0, -232,    0,    0,   52,
    0, -151,    0,    0,    0,    0,    0,    0,    0, -156,
 -229, -167,    0, -158,    0,  -40, -194, -181,   55, -141,
  -40,  -40,   79,  -38,  -38,  -40,    0,    0,    0,    0,
  -38,    0,    0,    0,   -5,  -36,    0,    0,    0,    0,
    0,   30,    0, -167,    0,   80, -232,  -40, -167,  -38,
 -232, -244,    0,    0,   61,   29,   31,    0,    0,  -40,
    0, -149, -185,    0,    0,    0, -194,    0, -138,    0,
  -40,   34,    0,   -1, -181,    0,    0, -232, -244,    0,
    0,    0,
};
short yyrindex[] = {                                    126,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -186,    0, -178,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -142,
    0,    0,    0,    0,    0,    0,    0,  -37,    0,    0,
    0,    0, -140,    0,    0,    0,   70,   71,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -28,    0,    0,    0,    0,    0,
   14,  -17,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -7,    0,    0,    0,    0,    3,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   20,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
short yygindex[] = {                                      0,
    0,   -9,  107,    0,   -2,    0, -111,    0,  -68,    0,
    0,    0,    0,    0,   84,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -51,    0,  -46,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,
    0,    0,   26,    0,  -25,    0,    0,  -78,    0,    0,
    0,    0,    0,
};
#define YYTABLESIZE 294
short yytable[] = {                                      69,
  126,   69,   55,   15,  113,   75,  105,   70,   74,   97,
   13,   74,   73,   20,    9,   73,   25,    1,   19,   26,
   27,   54,  114,   64,   38,    4,   64,  142,   18,   94,
   73,  124,   49,   66,  100,   19,   66,   39,    9,  106,
   40,   64,    9,   67,    5,   88,   67,   89,   90,   21,
   22,   66,  112,   50,   61,  122,  139,   61,  104,  125,
   63,   67,    6,   63,   73,  109,  140,   95,    8,   10,
  118,    9,   61,  119,  137,   64,   11,  119,   63,   18,
   18,   18,   26,   27,  136,   66,  141,   16,   16,    2,
   13,   89,   90,   19,   31,   67,   32,   33,   34,   36,
   50,   51,   56,   57,   58,   59,   61,   63,   64,   78,
   80,   92,   63,   98,   87,   93,   99,  134,  103,  128,
  121,  129,  133,  130,  135,    4,   35,   28,   34,   28,
   35,   61,  132,  123,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   65,   66,   65,   66,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   54,    0,    0,   54,    0,   67,    0,   49,   68,
   73,   68,   73,   73,    0,   73,   73,    0,   73,   73,
   73,   64,    0,   64,   64,    0,   64,   64,    0,   64,
   64,   66,    0,   66,   66,    0,   66,   66,    0,   66,
   66,   67,    0,   67,   67,    0,   67,   67,    0,   67,
   67,    0,   61,    0,   61,   61,    0,   61,   63,    0,
   63,   63,    0,   63,
};
short yycheck[] = {                                      40,
  112,   40,   40,   13,   41,   57,   85,   54,   55,   78,
  260,   40,   41,   16,   44,   44,  261,  259,  268,  264,
  265,   59,   59,   41,  257,  257,   44,  139,   58,   76,
   59,  110,   35,   41,   81,  268,   44,  270,   44,   86,
  273,   59,   44,   41,   40,  275,   44,  277,  278,  266,
  267,   59,   58,   91,   41,  107,   58,   44,   84,  111,
   41,   59,  257,   44,   93,   91,  135,   77,   41,   59,
   41,   44,   59,   44,   41,   93,  257,   44,   59,  266,
  267,  268,  264,  265,  131,   93,  138,  266,  267,  268,
  260,  277,  278,  268,   46,   93,  257,  257,   59,   91,
  258,   59,  269,   59,  276,   40,   93,   91,   40,   58,
  262,  279,   93,   59,  271,  274,  258,  127,   40,   59,
   41,   93,  272,   93,  263,    0,  269,   58,  269,   59,
   24,   48,  120,  108,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  257,  258,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  269,   -1,   -1,  272,   -1,  277,   -1,  276,  280,
  269,  280,  271,  272,   -1,  274,  275,   -1,  277,  278,
  279,  269,   -1,  271,  272,   -1,  274,  275,   -1,  277,
  278,  269,   -1,  271,  272,   -1,  274,  275,   -1,  277,
  278,  269,   -1,  271,  272,   -1,  274,  275,   -1,  277,
  278,   -1,  269,   -1,  271,  272,   -1,  274,  269,   -1,
  271,  272,   -1,  274,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 280
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,"'.'",0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"ID","NUM","S_PROGRAM","S_VAR","S_ARRAY","S_DOTDOT","S_OF","S_INTEGER","S_REAL",
"S_FUNCTION","S_PROCEDURE","S_BEGIN","S_END","S_IF","S_THEN","S_ELSE","S_WHILE",
"S_DO","S_RELOP","S_ASSIGN","S_PLUSMIN","S_OR","S_MULOP","S_NOT",
};
char *yyrule[] = {
"$accept : program",
"$$1 :",
"$$2 :",
"program : S_PROGRAM $$1 ID '(' identifier_list ')' ';' declarations subprogram_declarations $$2 compound_statement '.'",
"program :",
"identifier_list : ID",
"identifier_list : identifier_list ',' ID",
"$$3 :",
"declarations : declarations S_VAR identifier_list ':' type $$3 ';'",
"declarations :",
"type : standard_type",
"$$4 :",
"$$5 :",
"type : S_ARRAY '[' NUM $$4 S_DOTDOT NUM $$5 ']' S_OF standard_type",
"standard_type : S_INTEGER",
"standard_type : S_REAL",
"$$6 :",
"subprogram_declarations : subprogram_declarations $$6 subprogram_declaration ';'",
"subprogram_declarations :",
"subprogram_declaration : subprogram_head declarations compound_statement",
"$$7 :",
"$$8 :",
"subprogram_head : S_FUNCTION ID $$7 arguments ':' standard_type $$8 ';'",
"$$9 :",
"$$10 :",
"subprogram_head : S_PROCEDURE ID $$9 arguments $$10 ';'",
"$$11 :",
"arguments : '(' $$11 parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"$$12 :",
"parameter_list : parameter_list ';' $$12 identifier_list ':' type",
"$$13 :",
"compound_statement : S_BEGIN $$13 optional_statements S_END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"statement_list : statement_list ';' statement",
"$$14 :",
"statement : variable S_ASSIGN $$14 expression",
"statement : procedure_statement",
"statement : compound_statement",
"$$15 :",
"$$16 :",
"$$17 :",
"statement : S_IF $$15 expression S_THEN $$16 statement S_ELSE $$17 statement",
"$$18 :",
"$$19 :",
"statement : S_WHILE $$18 expression S_DO $$19 statement",
"variable : ID",
"$$20 :",
"$$21 :",
"$$22 :",
"variable : ID $$20 '[' $$21 expression $$22 ']'",
"procedure_statement : ID",
"$$23 :",
"$$24 :",
"procedure_statement : ID $$23 '(' $$24 expression_list ')'",
"expression_list : expression",
"$$25 :",
"expression_list : expression_list ',' $$25 expression",
"expression : simple_expression",
"$$26 :",
"expression : simple_expression S_RELOP $$26 simple_expression",
"simple_expression : term",
"$$27 :",
"simple_expression : S_PLUSMIN $$27 term",
"simple_expression : simple_expression addOp term",
"addOp : S_PLUSMIN",
"addOp : S_OR",
"term : factor",
"$$28 :",
"term : term S_MULOP $$28 factor",
"factor : ID",
"$$29 :",
"$$30 :",
"factor : ID $$29 '(' $$30 expression_list ')'",
"factor : NUM",
"$$31 :",
"factor : '(' $$31 expression ')'",
"$$32 :",
"factor : S_NOT $$32 factor",
};
#endif
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 470 "yea.y"


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
#line 408 "y.tab.c"
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d (%s)\n",
                    yystate, yytable[yyn],yyrule[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 100 "yea.y"
{totalSymbol=0;SP=0;
														symbolTable[SP].low=-1;
														strcpy(symbolTable[SP].name,"Global");
														totalSymbol++;SP;}
break;
case 2:
#line 109 "yea.y"
{printf("void main()\n");}
break;
case 3:
#line 111 "yea.y"
{showSymbolTable();}
break;
case 4:
#line 112 "yea.y"
{printf("<Empty Input>");}
break;
case 5:
#line 115 "yea.y"
{varIndex=0; 
														strcpy( varNames[varIndex++], yyvsp[0].code);}
break;
case 6:
#line 120 "yea.y"
{strcpy( varNames[varIndex++], yyvsp[0].code);}
break;
case 7:
#line 127 "yea.y"
{counter=tabCounter;
														while(counter--) printf("\t");
														
														counter=0;
														symbolTable[SP].len += varIndex; /*first time SP=0*/
														if(strcmp(yyvsp[0].code,"int")==0)
															tmpInt=1;
														else if(strcmp(yyvsp[0].code,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
																				
														printf("%s ",yyvsp[0].code);
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
																symbolTable[totalSymbol].len=-1; /*not Array*/
																symbolTable[totalSymbol].low=0;		/* not frame entry*/
															}
																
															counter++;
															totalSymbol++;
															
														} }
break;
case 8:
#line 164 "yea.y"
{printf(" ;\n");}
break;
case 10:
#line 168 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );
														low=-1;high=-1;}
break;
case 11:
#line 174 "yea.y"
{low = atoi(yyvsp[0].code);}
break;
case 12:
#line 176 "yea.y"
{high = atoi(yyvsp[0].code);}
break;
case 13:
#line 179 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );}
break;
case 14:
#line 183 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "int");}
break;
case 15:
#line 185 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "float");}
break;
case 16:
#line 189 "yea.y"
{printf("\n");tabCounter++;turnOfCompoundStart=+1;}
break;
case 19:
#line 197 "yea.y"
{/*printf("\nFun:%s SP:%d TotalSym:%d\n",functionName,SP,totalSymbol);*/
														/*totalSymbol -= (symbolTable[SP].len+1) ; //1 for frame container*/
														/*printf("*Fun:%s SP:%d TotalSym:%d\n",functionName,SP,totalSymbol);*/
														}
break;
case 20:
#line 205 "yea.y"
{getData(yyvsp[0].code);strcpy(functionName,data);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
break;
case 21:
#line 212 "yea.y"
{printf("%s %s %s\n{\n",yyvsp[0].code,functionName,yyvsp[-2].code);}
break;
case 22:
#line 213 "yea.y"
{printf("\n");}
break;
case 23:
#line 216 "yea.y"
{getData(yyvsp[0].code);strcpy(functionName,data);
														printf("void %s",functionName);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
break;
case 24:
#line 222 "yea.y"
{printf("%s\n{\n",yyvsp[0].code);}
break;
case 26:
#line 226 "yea.y"
{strcpy(parameters,"");}
break;
case 27:
#line 228 "yea.y"
{yyval.code=malloc(1+5+strlen(parameters));
														sprintf(data,"(%s)",parameters);
														strcpy( yyval.code, data);}
break;
case 29:
#line 237 "yea.y"
{counter=0;
														symbolTable[SP].len += varIndex ;
														if(strcmp(yyvsp[0].code,"int")==0)
															tmpInt=1;
														else if(strcmp(yyvsp[0].code,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,yyvsp[0].code);
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
break;
case 30:
#line 273 "yea.y"
{strcat(parameters,", ");}
break;
case 31:
#line 276 "yea.y"
{counter=0;
														symbolTable[SP].len += varIndex ;
														if(strcmp(yyvsp[0].code,"int")==0)
															tmpInt=1;
														else if(strcmp(yyvsp[0].code,"float")==0)
															tmpInt=2;
														else
															tmpInt=-1;
														while(counter<varIndex)
														{
															if(counter>0)
																strcat(parameters,",");
															strcat(parameters,yyvsp[0].code);
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
														/*printf("_%s",parameters);*/
														}
break;
case 32:
#line 313 "yea.y"
{if(turnOfCompoundStart==+1) {printf("\n");turnOfCompoundStart=-1;}
														else {printf("{\n");tabCounter++;}
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 33:
#line 318 "yea.y"
{tabCounter--;
														counter=tabCounter;
														printf("\n");
														while(counter--) printf("\t");
														printf("}\n");}
break;
case 38:
#line 338 "yea.y"
{printf(" = ");}
break;
case 39:
#line 339 "yea.y"
{printf(" ;\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 40:
#line 343 "yea.y"
{printf(" ;\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 42:
#line 350 "yea.y"
{counter=tabCounter;
														while(counter--) printf("\t");
														printf("if (");}
break;
case 43:
#line 354 "yea.y"
{printf(" )\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 44:
#line 358 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");
														printf("else\n");}
break;
case 46:
#line 363 "yea.y"
{counter=tabCounter-1;
														while(counter--) printf("\t");
														printf("while( ");}
break;
case 47:
#line 367 "yea.y"
{printf(" )");}
break;
case 49:
#line 371 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 50:
#line 373 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 51:
#line 374 "yea.y"
{printf("[");}
break;
case 52:
#line 375 "yea.y"
{counter=totalSymbol;
														/*printf(">>>>%d",totalSymbol);*/
														for(;counter>0;counter--)
														{
															if( symbolTable[counter].low==-1 ||
																strcmp(data,symbolTable[counter].name)!=0 )
																	continue;
															printf("-%d",symbolTable[counter].low);
															break;
														}}
break;
case 53:
#line 385 "yea.y"
{printf("]");}
break;
case 54:
#line 389 "yea.y"
{printf("%s()",yyvsp[0].code);}
break;
case 55:
#line 391 "yea.y"
{getData(yyvsp[0].code);
														printf("%s",data);}
break;
case 56:
#line 393 "yea.y"
{printf("( ");}
break;
case 57:
#line 395 "yea.y"
{printf(" )");}
break;
case 59:
#line 401 "yea.y"
{printf(", ");}
break;
case 62:
#line 409 "yea.y"
{strcpy(data,yyvsp[0].code);
														/*printf("::%s",data);*/
														if(strcmp(data,"=")==0)
															printf("==");
														else if(strcmp(data,"<>")==0)
															printf("!=");
														else
															printf("%s",data);}
break;
case 65:
#line 424 "yea.y"
{printf("%s(",yyvsp[0].code);}
break;
case 66:
#line 425 "yea.y"
{printf(" )");}
break;
case 68:
#line 433 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 69:
#line 435 "yea.y"
{printf("|");}
break;
case 71:
#line 441 "yea.y"
{strcpy(data,yyvsp[0].code);
														if(strcmp(data,"mod")==0)
															printf("%%");
														else if(strcmp(data,"and")==0)
															printf("&");
														else
															printf("%s",data);}
break;
case 73:
#line 451 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 74:
#line 453 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 75:
#line 454 "yea.y"
{printf("(");}
break;
case 76:
#line 456 "yea.y"
{printf(" )");}
break;
case 77:
#line 458 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 78:
#line 460 "yea.y"
{printf("(");}
break;
case 79:
#line 462 "yea.y"
{printf(" )");}
break;
case 80:
#line 464 "yea.y"
{printf("!( ");}
break;
case 81:
#line 465 "yea.y"
{printf(" )");}
break;
#line 959 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
