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
   17,   18,   14,   19,   20,   14,   22,   16,   16,   21,
   23,   21,   25,    5,   24,   24,   26,   28,   26,   31,
   27,   27,   27,   33,   34,   35,   36,   27,   37,   38,
   27,   29,   39,   40,   41,   29,   32,   42,   44,   32,
   43,   45,   43,   30,   47,   30,   46,   49,   46,   46,
   50,   50,   48,   52,   48,   51,   53,   54,   51,   51,
   55,   51,   56,   51,
};
short yylen[] = {                                         2,
    0,    0,   12,    0,    1,    3,    0,    7,    0,    1,
    0,    0,   10,    1,    1,    0,    4,    0,    0,    4,
    0,    0,    8,    0,    0,    6,    0,    4,    0,    3,
    0,    6,    0,    4,    1,    0,    1,    0,    4,    0,
    4,    1,    1,    0,    0,    0,    0,   10,    0,    0,
    6,    1,    0,    0,    0,    7,    1,    0,    0,    6,
    1,    0,    4,    1,    0,    4,    1,    0,    3,    3,
    1,    1,    1,    0,    4,    1,    0,    0,    6,    1,
    0,    4,    0,    3,
};
short yydefred[] = {                                      0,
    1,    0,    0,    0,    0,    5,    0,    0,    0,    9,
    6,    0,    0,    0,    0,    0,    0,    0,   33,    0,
    0,    0,    0,   19,    0,   14,   15,    7,   10,    0,
    3,   21,   24,   17,    9,    0,    0,    0,   44,   49,
   43,    0,    0,   37,    0,   42,    0,    0,    0,   11,
    8,    0,    0,    0,    0,   34,   38,   40,   27,    0,
   25,   20,    0,   54,   59,    0,   80,   68,   83,   81,
    0,    0,    0,   73,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   45,   65,   71,
   72,    0,   74,   50,   39,   41,    0,    0,   22,   26,
   12,   55,   61,    0,   78,    0,   84,    0,    0,    0,
    0,    0,    0,    0,   28,   31,    0,    0,    0,   60,
   62,    0,   82,   46,    0,   75,   51,   30,    0,   23,
    0,   56,    0,    0,    0,    0,    0,   63,   79,   47,
    0,   13,    0,   32,   48,
};
short yydgoto[] = {                                       2,
    3,    7,   12,   14,   41,   16,   28,   37,   29,   63,
  118,   23,   17,   24,   35,   60,   47,  117,   48,   80,
   98,   78,  129,   42,   30,   43,   44,   76,   45,  103,
   77,   46,   54,  109,  135,  143,   55,  113,   52,   82,
  119,   53,  104,   83,  133,   72,  110,   73,   85,   92,
   74,  112,   84,  122,   87,   86,
};
short yysindex[] = {                                   -244,
    0,    0, -237,   13, -194,    0,  -27,   19, -172,    0,
    0, -177, -194,    0,  -26, -173, -197, -193,    0,   48,
 -160, -159,   40,    0,    9,    0,    0,    0,    0, -247,
    0,    0,    0,    0,    0, -157,   43,    0,    0,    0,
    0, -166,   45,    0, -171,    0,   66,   66, -225,    0,
    0,   17,   69,  -40,  -40,    0,    0,    0,    0,   52,
    0,    0, -151,    0,    0,    0,    0,    0,    0,    0,
 -156, -218, -167,    0, -158, -247,  -40, -194, -174,   55,
 -140,  -40,  -40,   79,  -38,  -38,  -40,    0,    0,    0,
    0,  -38,    0,    0,    0,    0,  -19,  -30,    0,    0,
    0,    0,    0,    7,    0, -167,    0,   80, -247,  -40,
 -167,  -38, -247, -193,    0,    0,   61,   29,   30,    0,
    0,  -40,    0,    0, -185,    0,    0,    0, -194,    0,
 -139,    0,  -40,   33, -147,   -8, -174,    0,    0,    0,
 -193,    0, -247,    0,    0,
};
short yyrindex[] = {                                    126,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -186,    0, -179,    0,    0,    0,    0,    0,    0,
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
    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  -12,   95,    0,   -9,    0,  -95,    0,  -70,    0,
    0,    0,    0,    0,    0,   84,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -68,    0,    0,  -49,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   11,    0,    0,   24,    0,  -36,    0,    0,
  -82,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 294
short yytable[] = {                                      70,
   15,   70,   58,  107,   71,   75,   20,   95,   99,   38,
  115,   77,   76,    8,    1,   76,    9,    9,  128,    4,
   19,   57,   39,   67,    9,   40,   67,   96,  116,  126,
   76,   18,  102,   69,   13,    9,   69,  108,  114,   62,
  124,   67,   19,   70,  127,  144,   70,  120,  106,  141,
  121,   69,    5,   53,   64,  111,   89,   64,   90,   91,
   66,   70,    6,   66,   76,   97,  142,   25,   21,   22,
   26,   27,   64,  139,  145,   67,  121,   10,   66,   18,
   18,   18,   13,  138,   11,   69,   16,   16,    2,   26,
   27,   90,   91,   31,   19,   70,   32,   33,   34,   36,
   50,   51,   56,   57,   58,   59,   64,   64,   65,   79,
   81,   93,   66,  100,   88,   94,  136,  101,  105,  130,
  123,  131,  132,  137,  140,    4,   36,   35,   29,   49,
   29,   61,  134,  125,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   66,   67,   66,   67,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   57,    0,    0,   57,    0,   68,    0,   52,   69,
   76,   69,   76,   76,    0,   76,   76,    0,   76,   76,
   76,   67,    0,   67,   67,    0,   67,   67,    0,   67,
   67,   69,    0,   69,   69,    0,   69,   69,    0,   69,
   69,   70,    0,   70,   70,    0,   70,   70,    0,   70,
   70,    0,   64,    0,   64,   64,    0,   64,   66,    0,
   66,   66,    0,   66,
};
short yycheck[] = {                                      40,
   13,   40,   40,   86,   54,   55,   16,   76,   79,  257,
   41,   40,   41,   41,  259,   44,   44,   44,  114,  257,
  268,   59,  270,   41,   44,  273,   44,   77,   59,  112,
   59,   58,   82,   41,  260,   44,   44,   87,   58,   49,
  109,   59,  268,   41,  113,  141,   44,   41,   85,   58,
   44,   59,   40,   91,   41,   92,  275,   44,  277,  278,
   41,   59,  257,   44,   93,   78,  137,  261,  266,  267,
  264,  265,   59,   41,  143,   93,   44,   59,   59,  266,
  267,  268,  260,  133,  257,   93,  266,  267,  268,  264,
  265,  277,  278,   46,  268,   93,  257,  257,   59,   91,
  258,   59,  269,   59,  276,   40,   93,   91,   40,   58,
  262,  279,   93,   59,  271,  274,  129,  258,   40,   59,
   41,   93,   93,  263,  272,    0,  269,  269,   58,   35,
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
"subprogram_head : S_FUNCTION ID $$8 arguments ':' standard_type $$9 ';'",
"$$10 :",
"$$11 :",
"subprogram_head : S_PROCEDURE ID $$10 arguments $$11 ';'",
"$$12 :",
"arguments : '(' $$12 parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"$$13 :",
"parameter_list : parameter_list ';' $$13 identifier_list ':' type",
"$$14 :",
"compound_statement : S_BEGIN $$14 optional_statements S_END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"$$15 :",
"statement_list : statement_list ';' $$15 statement",
"$$16 :",
"statement : variable S_ASSIGN $$16 expression",
"statement : procedure_statement",
"statement : compound_statement",
"$$17 :",
"$$18 :",
"$$19 :",
"$$20 :",
"statement : S_IF $$17 expression S_THEN $$18 statement $$19 S_ELSE $$20 statement",
"$$21 :",
"$$22 :",
"statement : S_WHILE $$21 expression S_DO $$22 statement",
"variable : ID",
"$$23 :",
"$$24 :",
"$$25 :",
"variable : ID $$23 '[' $$24 expression $$25 ']'",
"procedure_statement : ID",
"$$26 :",
"$$27 :",
"procedure_statement : ID $$26 '(' $$27 expression_list ')'",
"expression_list : expression",
"$$28 :",
"expression_list : expression_list ',' $$28 expression",
"expression : simple_expression",
"$$29 :",
"expression : simple_expression S_RELOP $$29 simple_expression",
"simple_expression : term",
"$$30 :",
"simple_expression : S_PLUSMIN $$30 term",
"simple_expression : simple_expression addOp term",
"addOp : S_PLUSMIN",
"addOp : S_OR",
"term : factor",
"$$31 :",
"term : term S_MULOP $$31 factor",
"factor : ID",
"$$32 :",
"$$33 :",
"factor : ID $$32 '(' $$33 expression_list ')'",
"factor : NUM",
"$$34 :",
"factor : '(' $$34 expression ')'",
"$$35 :",
"factor : S_NOT $$35 factor",
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
#line 526 "yea.y"


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
#line 416 "y.tab.c"
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
{if(SHOW_TABLE==+1)	showSymbolTable();}
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
															
														} }
break;
case 8:
#line 171 "yea.y"
{printf(" ;\n");}
break;
case 10:
#line 175 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );
														low=-1;high=-1;}
break;
case 11:
#line 181 "yea.y"
{low = atoi(yyvsp[0].code);}
break;
case 12:
#line 183 "yea.y"
{high = atoi(yyvsp[0].code);}
break;
case 13:
#line 186 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, yyvsp[0].code );}
break;
case 14:
#line 190 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "int");}
break;
case 15:
#line 192 "yea.y"
{yyval.code=malloc(1+strlen(yyvsp[0].code));
														strcpy( yyval.code, "float");}
break;
case 16:
#line 196 "yea.y"
{printf("\n");tabCounter++;turnOfCompoundStart=+1;
														/*showSymbolTable();*/
														}
break;
case 19:
#line 204 "yea.y"
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
#line 219 "yea.y"
{ if(SHOW_TABLE==-1) totalSymbol -= (symbolTable[SP].len+1) ;}
break;
case 21:
#line 224 "yea.y"
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
{printf("%s %s %s\n{\n",yyvsp[0].code,functionName,yyvsp[-2].code);strcpy(returnType,yyvsp[0].code);}
break;
case 23:
#line 234 "yea.y"
{printf("\n");}
break;
case 24:
#line 237 "yea.y"
{getData(yyvsp[0].code);strcpy(functionName,data);
														printf("void %s",functionName);
														SP=totalSymbol;
														symbolTable[SP].low=-1;
														symbolTable[SP].len=0;
														strcpy(symbolTable[SP].name,functionName);
														totalSymbol++;}
break;
case 25:
#line 244 "yea.y"
{printf("%s\n{\n",yyvsp[0].code);returnType[0]='\0';}
break;
case 27:
#line 248 "yea.y"
{strcpy(parameters,"");}
break;
case 28:
#line 250 "yea.y"
{yyval.code=malloc(1+5+strlen(parameters));
														sprintf(data,"(%s)",parameters);
														strcpy( yyval.code, data);}
break;
case 30:
#line 259 "yea.y"
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
case 31:
#line 295 "yea.y"
{strcat(parameters,", ");}
break;
case 32:
#line 298 "yea.y"
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
case 33:
#line 335 "yea.y"
{if(turnOfCompoundStart==+1) {printf("\n");turnOfCompoundStart=-1;}
														else {printf("{\n");tabCounter++;}
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 34:
#line 340 "yea.y"
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
case 35:
#line 355 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 38:
#line 363 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 40:
#line 369 "yea.y"
{printf(" = ");}
break;
case 41:
#line 370 "yea.y"
{printf(" ;");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 42:
#line 374 "yea.y"
{printf(" ;\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 44:
#line 381 "yea.y"
{counter=tabCounter;
														/*printf(">");*/
														/*while(counter--) printf("P\t");*/
														printf("if (");}
break;
case 45:
#line 386 "yea.y"
{tabCounter++;printf(" )\n");
														counter=tabCounter;
														while(counter--) printf("\t");}
break;
case 46:
#line 389 "yea.y"
{tabCounter--;}
break;
case 47:
#line 390 "yea.y"
{printf("\n");counter=tabCounter;
														while(counter--) printf("\t");
														printf("else\n");tabCounter++;counter=tabCounter;
														while(counter--) printf("\t");
														}
break;
case 48:
#line 395 "yea.y"
{tabCounter--;}
break;
case 49:
#line 397 "yea.y"
{counter=tabCounter-1;
														while(counter--) printf("\t");
														printf("while( ");}
break;
case 50:
#line 401 "yea.y"
{printf(" )");}
break;
case 52:
#line 405 "yea.y"
{ getData(yyvsp[0].code); if(strcmp(data,symbolTable[SP].name)==0)	printf("__%s",data);
																			else	printf("%s",data);	}
break;
case 53:
#line 408 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 54:
#line 409 "yea.y"
{printf("[");}
break;
case 55:
#line 410 "yea.y"
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
case 56:
#line 423 "yea.y"
{printf("]");}
break;
case 57:
#line 427 "yea.y"
{printf("%s()",yyvsp[0].code);}
break;
case 58:
#line 429 "yea.y"
{getData(yyvsp[0].code);
														printf("%s",data);}
break;
case 59:
#line 431 "yea.y"
{printf("( ");}
break;
case 60:
#line 433 "yea.y"
{printf(" )");}
break;
case 62:
#line 439 "yea.y"
{printf(", ");}
break;
case 65:
#line 447 "yea.y"
{strcpy(data,yyvsp[0].code);
														/*printf("::%s",data);*/
														if(strcmp(data,"=")==0)
															printf("==");
														else if(strcmp(data,"<>")==0)
															printf("!=");
														else
															printf("%s",data);}
break;
case 68:
#line 462 "yea.y"
{printf("%s(",yyvsp[0].code);}
break;
case 69:
#line 463 "yea.y"
{printf(" )");}
break;
case 71:
#line 471 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 72:
#line 473 "yea.y"
{printf("||");}
break;
case 74:
#line 479 "yea.y"
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
case 76:
#line 491 "yea.y"
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
case 77:
#line 509 "yea.y"
{getData(yyvsp[0].code);printf("%s",data);}
break;
case 78:
#line 510 "yea.y"
{printf("(");}
break;
case 79:
#line 512 "yea.y"
{printf(" )");}
break;
case 80:
#line 514 "yea.y"
{printf("%s",yyvsp[0].code);}
break;
case 81:
#line 516 "yea.y"
{printf("(");}
break;
case 82:
#line 518 "yea.y"
{printf(" )");}
break;
case 83:
#line 520 "yea.y"
{printf("!( ");}
break;
case 84:
#line 521 "yea.y"
{printf(" )");}
break;
#line 1038 "y.tab.c"
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
