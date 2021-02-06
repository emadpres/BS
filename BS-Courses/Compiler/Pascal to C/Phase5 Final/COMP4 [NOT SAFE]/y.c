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
int SHOW_TABLE=-1;

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


#line 80 "y.tab.c"
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
   10,   11,    7,    9,    9,   13,    4,    4,   15,   12,
   17,   18,   19,   14,   20,   21,   14,   23,   16,   16,
   22,   24,   22,   26,    5,   25,   25,   27,   29,   27,
   32,   28,   28,   28,   34,   35,   36,   37,   28,   38,
   39,   28,   30,   40,   41,   42,   30,   33,   43,   45,
   33,   44,   46,   44,   31,   48,   31,   47,   50,   47,
   47,   51,   51,   49,   53,   49,   52,   54,   55,   52,
   52,   56,   52,   57,   52,
};
short yylen[] = {                                         2,
    0,    0,   12,    0,    1,    3,    0,    7,    0,    1,
    0,    0,   10,    1,    1,    0,    4,    0,    0,    4,
    0,    0,    0,    9,    0,    0,    6,    0,    4,    0,
    3,    0,    6,    0,    4,    1,    0,    1,    0,    4,
    0,    4,    1,    1,    0,    0,    0,    0,   10,    0,
    0,    6,    1,    0,    0,    0,    7,    1,    0,    0,
    6,    1,    0,    4,    1,    0,    4,    1,    0,    3,
    3,    1,    1,    1,    0,    4,    1,    0,    0,    6,
    1,    0,    4,    0,    3,
};
short yydefred[] = {                                      0,
    1,    0,    0,    0,    0,    5,    0,    0,    0,    9,
    6,    0,    0,    0,    0,    0,    0,    0,   34,    0,
    0,    0,    0,   19,    0,   14,   15,    7,   10,    0,
    3,   21,   25,   17,    9,    0,    0,    0,   45,   50,
   44,    0,    0,   38,    0,   43,    0,    0,    0,   11,
    8,    0,    0,    0,    0,   35,   39,   41,   28,   22,
   26,   20,    0,   55,   60,    0,   81,   69,   84,   82,
    0,    0,    0,   74,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   46,   66,   72,
   73,    0,   75,   51,   40,   42,    0,    0,    0,   27,
   12,   56,   62,    0,   79,    0,   85,    0,    0,    0,
    0,    0,    0,    0,   29,   32,   23,    0,    0,   61,
   63,    0,   83,   47,    0,   76,   52,   31,    0,    0,
    0,   57,    0,    0,    0,    0,   24,    0,   64,   80,
   48,    0,   13,    0,   33,   49,
};
short yydgoto[] = {                                       2,
    3,    7,   12,   14,   41,   16,   28,   37,   29,   63,
  118,   23,   17,   24,   35,   60,   47,   79,  130,   48,
   80,   98,   78,  129,   42,   30,   43,   44,   76,   45,
  103,   77,   46,   54,  109,  135,  144,   55,  113,   52,
   82,  119,   53,  104,   83,  133,   72,  110,   73,   85,
   92,   74,  112,   84,  122,   87,   86,
};
short yysindex[] = {                                   -244,
    0,    0, -238,  -10, -211,    0,  -27,    9, -197,    0,
    0, -185, -211,    0,  -26, -190, -174, -194,    0,   37,
 -172, -158,   41,    0,   -4,    0,    0,    0,    0, -247,
    0,    0,    0,    0,    0, -157,   43,    0,    0,    0,
    0, -166,   45,    0, -171,    0,   66,   66, -219,    0,
    0,   17,   69,  -40,  -40,    0,    0,    0,    0,    0,
    0,    0, -152,    0,    0,    0,    0,    0,    0,    0,
 -160, -227, -167,    0, -159, -247,  -40, -211,   56,   57,
 -140,  -40,  -40,   79,  -38,  -38,  -40,    0,    0,    0,
    0,  -38,    0,    0,    0,    0,  -19,  -30, -170,    0,
    0,    0,    0,   28,    0, -167,    0,   80, -247,  -40,
 -167,  -38, -247, -194,    0,    0,    0,   27,   29,    0,
    0,  -40,    0,    0, -180,    0,    0,    0, -211,   64,
 -139,    0,  -40,   33, -147,    1,    0, -170,    0,    0,
    0, -194,    0, -247,    0,    0,
};
short yyrindex[] = {                                    126,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -186,    0, -177,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -142,
    0,    0,    0,    0,    0,    0,    0,  -37,    0,    0,
    0,    0, -141,    0,    0,    0,   71,   72,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -28,    0,    0,    0,    0,
    0,   14,  -17,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   -7,    0,    0,    0,    0,
    3,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   20,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  -12,   95,    0,   -9,    0, -106,    0,  -95,    0,
    0,    0,    0,    0,    0,   84,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -56,    0,    0,
  -49,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   11,    0,    0,   24,    0,  -29,    0,
    0,  -77,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 294
short yytable[] = {                                      70,
   15,   70,   59,  117,   71,   75,   20,  128,  107,   38,
  115,   78,   77,    8,    1,   77,    9,    9,    4,   95,
   19,   58,   39,   68,    9,   40,   68,   96,  116,    5,
   77,   18,  102,   70,  126,  145,   70,  108,  114,   62,
   13,   68,  143,   71,    9,    6,   71,   89,   19,   90,
   91,   70,  124,   54,   65,  106,  127,   65,  142,   11,
   67,   71,  111,   67,   77,   97,   25,   10,  120,   26,
   27,  121,   65,  140,   13,   68,  121,   19,   67,   18,
   18,   18,   31,  139,   32,   70,   36,  146,   16,   16,
    2,   21,   22,   26,   27,   71,   90,   91,   33,   34,
   50,   51,   56,   57,   58,   59,   65,   64,   65,   81,
   88,   93,   67,   99,   94,  100,  136,  101,  105,  131,
  123,  132,  137,  138,  141,    4,   37,   36,   30,   49,
   30,   61,  134,  125,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   66,   67,   66,   67,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   58,    0,    0,   58,    0,   68,    0,   53,   69,
   77,   69,   77,   77,    0,   77,   77,    0,   77,   77,
   77,   68,    0,   68,   68,    0,   68,   68,    0,   68,
   68,   70,    0,   70,   70,    0,   70,   70,    0,   70,
   70,   71,    0,   71,   71,    0,   71,   71,    0,   71,
   71,    0,   65,    0,   65,   65,    0,   65,   67,    0,
   67,   67,    0,   67,
};
short yycheck[] = {                                      40,
   13,   40,   40,   99,   54,   55,   16,  114,   86,  257,
   41,   40,   41,   41,  259,   44,   44,   44,  257,   76,
  268,   59,  270,   41,   44,  273,   44,   77,   59,   40,
   59,   58,   82,   41,  112,  142,   44,   87,   58,   49,
  260,   59,  138,   41,   44,  257,   44,  275,  268,  277,
  278,   59,  109,   91,   41,   85,  113,   44,   58,  257,
   41,   59,   92,   44,   93,   78,  261,   59,   41,  264,
  265,   44,   59,   41,  260,   93,   44,  268,   59,  266,
  267,  268,   46,  133,  257,   93,   91,  144,  266,  267,
  268,  266,  267,  264,  265,   93,  277,  278,  257,   59,
  258,   59,  269,   59,  276,   40,   93,   91,   40,  262,
  271,  279,   93,   58,  274,   59,  129,  258,   40,   93,
   41,   93,   59,  263,  272,    0,  269,  269,   58,   35,
   59,   48,  122,  110,   -1,   -1,   -1,   -1,   -1,   -1,
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
"$$7 :",
"subprogram_declaration : subprogram_head $$7 declarations compound_statement",
"$$8 :",
"$$9 :",
"$$10 :",
"subprogram_head : S_FUNCTION ID $$8 arguments $$9 ':' standard_type $$10 ';'",
"$$11 :",
"$$12 :",
"subprogram_head : S_PROCEDURE ID $$11 arguments $$12 ';'",
"$$13 :",
"arguments : '(' $$13 parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"$$14 :",
"parameter_list : parameter_list ';' $$14 identifier_list ':' type",
"$$15 :",
"compound_statement : S_BEGIN $$15 optional_statements S_END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"$$16 :",
"statement_list : statement_list ';' $$16 statement",
"$$17 :",
"statement : variable S_ASSIGN $$17 expression",
"statement : procedure_statement",
"statement : compound_statement",
"$$18 :",
"$$19 :",
"$$20 :",
"$$21 :",
"statement : S_IF $$18 expression S_THEN $$19 statement $$20 S_ELSE $$21 statement",
"$$22 :",
"$$23 :",
"statement : S_WHILE $$22 expression S_DO $$23 statement",
"variable : ID",
"$$24 :",
"$$25 :",
"$$26 :",
"variable : ID $$24 '[' $$25 expression $$26 ']'",
"procedure_statement : ID",
"$$27 :",
"$$28 :",
"procedure_statement : ID $$27 '(' $$28 expression_list ')'",
"expression_list : expression",
"$$29 :",
"expression_list : expression_list ',' $$29 expression",
"expression : simple_expression",
"$$30 :",
"expression : simple_expression S_RELOP $$30 simple_expression",
"simple_expression : term",
"$$31 :",
"simple_expression : S_PLUSMIN $$31 term",
"simple_expression : simple_expression addOp term",
"addOp : S_PLUSMIN",
"addOp : S_OR",
"term : factor",
"$$32 :",
"term : term S_MULOP $$32 factor",
"factor : ID",
"$$33 :",
"$$34 :",
"factor : ID $$33 '(' $$34 expression_list ')'",
"factor : NUM",
"$$35 :",
"factor : '(' $$35 expression ')'",
"$$36 :",
"factor : S_NOT $$36 factor",
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
#line 528 "yea.y"


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
#line 417 "y.tab.c"
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
#line 105 "yea.y"
{totalSymbol=0;SP=0;
														symbolTable[SP].low=-1;
														strcpy(symbolTable[SP].name,"Global");
														totalSymbol++;SP;}
break;
case 2:
#line 114 "yea.y"
{printf("void main()\n");
														/*showSymbolTable();*/
														}
break;
case 3:
#line 118 "yea.y"
{showSymbolTable();}
break;
case 4:
#line 119 "yea.y"
{printf("<Empty Input>");}
break;
case 5:
#line 122 "yea.y"
{varIndex=0; 
														strcpy( varNames[varIndex++], yyvsp[0].code);}
break;
case 6:
#line 127 "yea.y"
{strcpy( varNames[varIndex++], yyvsp[0].code);}
break;
case 7:
#line 134 "yea.y"
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
															
														} free(yyvsp[0].code);}
break;
case 8:
#line 171 "yea.y"
{printf(" ;\n");}
break;
case 10:
#line 175 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );
														low=-1;high=-1;
														free( yyvsp[0].code );}
break;
case 11:
#line 182 "yea.y"
{low = atoi(yyvsp[0].code);}
break;
case 12:
#line 184 "yea.y"
{high = atoi(yyvsp[0].code);}
break;
case 13:
#line 187 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );
														free( yyvsp[0].code);}
break;
case 14:
#line 192 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "int");}
break;
case 15:
#line 194 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "float");}
break;
case 16:
#line 198 "yea.y"
{printf("\n");tabCounter++;turnOfCompoundStart=+1;
														/*showSymbolTable();*/
														}
break;
case 19:
#line 206 "yea.y"
{ if(returnType[0]!='\0') { printf("\t%s __%s;\n",returnType,functionName);
														/*printf("\n>>>>>>>>>> %d    %d\n\n",SP,totalSymbol);*/
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
														/*printf("\n\n\n%s    %d\n\n\n",symbolTable[SP].name,symbolTable[SP].len);*/
														 totalSymbol++;}}
break;
case 20:
#line 221 "yea.y"
{ if(SHOW_TABLE==-1) totalSymbol -= (symbolTable[SP].len+1) ;}
break;
case 21:
#line 226 "yea.y"
{needReturn=+1;
														getData(yyvsp[0].code);strcpy(functionName,data);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														symbolTable[SP].len=0;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
break;
case 22:
#line 233 "yea.y"
{free(yyvsp[0].code);}
break;
case 23:
#line 235 "yea.y"
{printf("%s %s %s\n{\n",yyvsp[-1].code,functionName,yyvsp[-3].code);strcpy(returnType,yyvsp[-1].code);}
break;
case 24:
#line 236 "yea.y"
{printf("\n");}
break;
case 25:
#line 239 "yea.y"
{getData(yyvsp[0].code);strcpy(functionName,data);
														printf("void %s",functionName);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														symbolTable[SP].len=0;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
break;
case 26:
#line 246 "yea.y"
{printf("%s\n{\n",yyvsp[0].code);returnType[0]='\0';free(yyvsp[0].code);}
break;
case 28:
#line 250 "yea.y"
{strcpy(parameters,"");}
break;
case 29:
#line 252 "yea.y"
{yyval.code=malloc(1+5+strlen(parameters));
														sprintf(data,"(%s)",parameters);
														strcpy( yyval.code, data);}
break;
case 31:
#line 261 "yea.y"
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
case 32:
#line 297 "yea.y"
{strcat(parameters,", ");}
break;
case 33:
#line 300 "yea.y"
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
case 34:
#line 337 "yea.y"
{if(turnOfCompoundStart==+1) {printf("\n");turnOfCompoundStart=-1;}
														else {printf("{\n");tabCounter++;}
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 35:
#line 342 "yea.y"
{
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
break;
case 36:
#line 357 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 39:
#line 365 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 41:
#line 371 "yea.y"
{printf(" = ");}
break;
case 42:
#line 372 "yea.y"
{printf(" ;");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 43:
#line 376 "yea.y"
{printf(" ;\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 45:
#line 383 "yea.y"
{counter=tabCounter;
														/*printf(">");*/
														/*while(counter--) printf("P\t");*/
														printf("if (");}
break;
case 46:
#line 388 "yea.y"
{tabCounter++;printf(" )\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 47:
#line 391 "yea.y"
{tabCounter--;}
break;
case 48:
#line 392 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");
														printf("else\n");tabCounter++;counter=tabCounter;
														while(counter--) printf("\t");
														}
break;
case 49:
#line 397 "yea.y"
{tabCounter--;}
break;
case 50:
#line 399 "yea.y"
{counter=tabCounter-1;
														while(counter--) printf("\t");
														printf("while( ");}
break;
case 51:
#line 403 "yea.y"
{printf(" )");}
break;
case 53:
#line 407 "yea.y"
{ getData(yyvsp[0].code); if(strcmp(data,symbolTable[SP].name)==0)	printf("__%s",data);
																			else	printf("%s",data);	}
break;
case 54:
#line 410 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 55:
#line 411 "yea.y"
{printf("[");}
break;
case 56:
#line 412 "yea.y"
{getData(yyvsp[-4].code);
														counter=totalSymbol;
														/*showSymbolTable();*/
														/*printf(">>>>%d",totalSymbol);*/
														for(;counter>0;counter--)
														{
															/*printf("X%sX ? X%sX\n",data,symbolTable[counter].name);*/
															if( symbolTable[counter].low==-1 ||
																strcmp(data,symbolTable[counter].name)!=0 )
																	continue;
															printf("-%d",symbolTable[counter].low);
															break;
														}}
break;
case 57:
#line 425 "yea.y"
{printf("]");}
break;
case 58:
#line 429 "yea.y"
{printf("%s()",yyvsp[0].code);}
break;
case 59:
#line 431 "yea.y"
{getData(yyvsp[0].code);
														printf("%s",data);}
break;
case 60:
#line 433 "yea.y"
{printf("( ");}
break;
case 61:
#line 435 "yea.y"
{printf(" )");}
break;
case 63:
#line 441 "yea.y"
{printf(", ");}
break;
case 66:
#line 449 "yea.y"
{strcpy(data,yyvsp[0].code);
														/*printf("::%s",data);*/
														if(strcmp(data,"=")==0)
															printf("==");
														else if(strcmp(data,"<>")==0)
															printf("!=");
														else
															printf("%s",data);}
break;
case 69:
#line 464 "yea.y"
{printf("%s(",yyvsp[0].code);}
break;
case 70:
#line 465 "yea.y"
{printf(" )");}
break;
case 72:
#line 473 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 73:
#line 475 "yea.y"
{printf("||");}
break;
case 75:
#line 481 "yea.y"
{strcpy(data,yyvsp[0].code);
														if(strcmp(data,"mod")==0)
															printf("%%");
														else if(strcmp(data,"and")==0)
															printf("&&");
														else if(strcmp(data,"div")==0)
															printf("/");
														else
															printf("%s",data);}
break;
case 77:
#line 493 "yea.y"
{ getData(yyvsp[0].code); if(strcmp(data,symbolTable[SP].name)==0)	printf("__%s",data);
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
break;
case 78:
#line 511 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 79:
#line 512 "yea.y"
{printf("(");}
break;
case 80:
#line 514 "yea.y"
{printf(" )");}
break;
case 81:
#line 516 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 82:
#line 518 "yea.y"
{printf("(");}
break;
case 83:
#line 520 "yea.y"
{printf(" )");}
break;
case 84:
#line 522 "yea.y"
{printf("!( ");}
break;
case 85:
#line 523 "yea.y"
{printf(" )");}
break;
#line 1045 "y.tab.c"
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
