#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
#line 21 "ea.y"
typedef union
{
	char *code;
} YYSTYPE;
#line 27 "ea.y"
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
char name[NAME_MAX_LENGTH];	/* We prefer to not use dynamic-allocation,  because struct has no destuctor and freeing mem will be hard.*/
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


#line 71 "y.tab.c"
#define ID 257
#define NUM 258
#define S_VOID 259
#define S_BOOL 260
#define S_INT 261
#define S_FLOAT 262
#define S_TEXT 263
#define S_TRUE 264
#define S_FALSE 265
#define S_STRING 266
#define S_NEW 267
#define S_RETURN 268
#define S_TYPE 269
#define S_VAR 270
#define S_FUNCTION 271
#define S_MAIN 272
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    4,    2,    6,    2,    8,    2,    5,
    9,    9,   10,   10,   11,   11,    3,   13,   13,   12,
   12,   14,   14,   17,   18,   18,   15,   20,   20,   16,
   16,   22,   22,   22,   22,    7,   23,   25,   25,   26,
   26,   19,   24,   24,   27,   27,   29,   29,   28,   31,
   31,   30,   30,   30,   30,   30,   32,   32,   32,   32,
   33,   34,   35,   36,   36,   21,   21,   21,   37,   39,
   38,   40,   41,   41,
};
short yylen[] = {                                         2,
    1,    2,    0,    0,    2,    0,    2,    0,    2,    7,
    2,    0,    2,    0,    1,    1,    7,    1,    1,    1,
    1,    2,    0,    2,    3,    0,    3,    2,    0,    1,
    1,    1,    1,    1,    1,    3,    3,    2,    0,    4,
    0,    3,    3,    0,    3,    0,    1,    0,    2,    2,
    0,    2,    1,    1,    1,    1,    1,    1,    1,    0,
    4,    3,    4,    2,    0,    1,    1,    1,    1,    3,
    3,    2,    2,    0,
};
short yydefred[] = {                                      0,
    0,    1,    0,    0,    0,    0,    2,    0,    5,    0,
    7,    0,    9,   31,   20,   33,   32,   34,   35,    0,
   21,   30,    0,    0,   19,   18,    0,    0,    0,    0,
    0,   36,    0,    0,   11,    0,   38,    0,    0,    0,
    0,    0,    0,   16,   15,    0,    0,    0,   37,    0,
   42,    0,   24,    0,   22,    0,   13,   43,    0,    0,
   17,    0,   10,    0,    0,    0,   66,    0,    0,   67,
   68,   69,   25,   40,    0,    0,    0,    0,   57,   58,
   59,    0,   53,   56,   54,   55,   47,    0,    0,   27,
   28,    0,    0,    0,    0,    0,   71,    0,   52,   70,
    0,   49,    0,   64,    0,    0,   62,   73,   72,   50,
    0,   63,   61,   45,
};
short yydgoto[] = {                                       1,
    2,    3,   44,    4,   11,    5,   45,    6,   29,   46,
   47,   20,   27,   41,   61,   42,   43,   55,   31,   68,
   69,   22,   32,   39,   33,   51,  104,   87,   88,   89,
  102,   78,   79,   80,   81,   93,   70,   71,   72,   97,
   98,
};
short yysindex[] = {                                      0,
    0,    0,    0, -269, -245, -244,    0, -217,    0, -211,
    0, -209,    0,    0,    0,    0,    0,    0,    0, -241,
    0,    0,  -11,    8,    0,    0,   22, -191,  -56,    8,
   24,    0, -188, -209,    0, -234,    0,    8,   14,  -17,
   34,    8,   32,    0,    0,  -48, -234,   24,    0, -180,
    0,  -44,    0, -209,    0,   21,    0,    0,  -12, -238,
    0,   32,    0,  -17,  -35, -193,    0,  -43, -238,    0,
    0,    0,    0,    0, -193, -193, -174,   23,    0,    0,
    0,  -35,    0,    0,    0,    0,    0,   26,   44,    0,
    0,   43,   47,   -4,  -35, -193,    0,   31,    0,    0,
 -193,    0, -193,    0,  -35,  -35,    0,    0,    0,    0,
   43,    0,    0,    0,
};
short yyrindex[] = {                                      1,
    0,    0,    1,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -31, -166,    0,    0,    0,    0,    0, -166,
   35,    0,    0,   52,    0,  -30,    0, -166,    0,  -24,
    0, -166,   55,    0,    0,    0,  -30,   35,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -28,
    0,   55,    0,  -24,   -1,   39,    0,    0,  -28,    0,
    0,    0,    0,    0,   58,    0,    0,   41,    0,    0,
    0,  -34,    0,    0,    0,    0,    0,    0,  -32,    0,
    0,   60,    0,    0,  -38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -38,  -38,    0,    0,    0,    0,
   60,    0,    0,    0,
};
short yygindex[] = {                                      0,
   99,    0,  100,    0,    0,    0,   -6,    0,    0,   56,
    0,    0,    0,    0,    0,   10,   51,   45,   -9,   37,
    0,    0,    0,   61,   78,   46,    2,  -62,    0,   11,
    0,  -67,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
#define YYTABLESIZE 272
short yytable[] = {                                      13,
    3,    8,   60,   60,   75,   60,   60,   60,   51,   60,
   77,   51,   92,   94,   99,   25,   41,   21,   65,   41,
   60,   24,   60,   10,   60,   12,   51,  107,   48,   66,
   26,   12,   53,  108,   41,   12,    8,  112,  113,   14,
  111,   15,   16,   17,   18,   23,   28,   14,   19,   30,
   16,   17,   18,   67,   60,   76,   19,   60,   60,   60,
   51,   34,   67,   82,   83,   35,   36,   38,   40,   84,
   85,   86,   49,   50,   52,   54,   56,   59,   60,   63,
   64,   90,   95,   96,  100,  101,  103,  105,  106,  109,
   39,   12,   23,   44,   14,   26,   29,   48,   65,   74,
   46,    7,   57,    9,   62,   91,   73,   37,   58,   74,
    0,  110,  114,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    6,
    8,    4,
};
short yycheck[] = {                                       6,
    0,  271,   41,   42,   40,   44,   41,   42,   41,   44,
   46,   44,   75,   76,   82,  257,   41,    8,  257,   44,
   59,   12,   61,  269,   59,  270,   59,   95,   38,  268,
  272,  270,   42,   96,   59,  270,  271,  105,  106,  257,
  103,  259,  260,  261,  262,  257,   58,  257,  266,   42,
  260,  261,  262,   60,   93,   91,  266,   59,   93,   61,
   93,   40,   69,  257,  258,  257,  123,   44,  257,  263,
  264,  265,   59,   91,   41,   44,  125,  258,  123,   59,
   93,  125,  257,   61,   59,   42,   44,   41,   93,   59,
  257,  123,   41,   59,  125,   41,  125,   59,   41,   59,
   41,    3,   47,    4,   54,   69,   62,   30,   48,   64,
   -1,  101,  111,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  269,
  270,  271,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 272
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'",0,"','",0,"'.'",0,0,0,0,0,0,0,0,0,0,0,"':'","';'",
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"ID","NUM","S_VOID","S_BOOL","S_INT","S_FLOAT","S_TEXT","S_TRUE",
"S_FALSE","S_STRING","S_NEW","S_RETURN","S_TYPE","S_VAR","S_FUNCTION","S_MAIN",
};
char *yyrule[] = {
"$accept : Program",
"Program : DeclarationList",
"DeclarationList : Declaration DeclarationList",
"DeclarationList :",
"$$1 :",
"Declaration : $$1 FunctionDeclaration",
"$$2 :",
"Declaration : $$2 TypeDeclaration",
"$$3 :",
"Declaration : $$3 VariableDeclaration",
"TypeDeclaration : S_TYPE ID OptionalSuperclass '{' MemberDeclarationList '}' ';'",
"OptionalSuperclass : ':' ID",
"OptionalSuperclass :",
"MemberDeclarationList : MemberDeclaration MemberDeclarationList",
"MemberDeclarationList :",
"MemberDeclaration : VariableDeclaration",
"MemberDeclaration : FunctionDeclaration",
"FunctionDeclaration : S_FUNCTION FunctionType FunctionName '(' OptionalParameterList ')' Block",
"FunctionName : S_MAIN",
"FunctionName : ID",
"FunctionType : S_VOID",
"FunctionType : TypeName",
"OptionalParameterList : Parameter MoreParameters",
"OptionalParameterList :",
"Parameter : TypeName Variable",
"MoreParameters : ',' Parameter MoreParameters",
"MoreParameters :",
"Block : '{' DeclarationOrStatementList '}'",
"DeclarationOrStatementList : DeclarationOrStatement DeclarationOrStatementList",
"DeclarationOrStatementList :",
"TypeName : PrimitiveType",
"TypeName : ID",
"PrimitiveType : S_INT",
"PrimitiveType : S_BOOL",
"PrimitiveType : S_FLOAT",
"PrimitiveType : S_STRING",
"VariableDeclaration : S_VAR TypeName RestOfVariableDeclaration",
"RestOfVariableDeclaration : Variable MoreVariables ';'",
"OptionalPointer : '*' OptionalPointer",
"OptionalPointer :",
"Dimensions : '[' NUM ']' Dimensions",
"Dimensions :",
"Variable : OptionalPointer ID Dimensions",
"MoreVariables : ',' Variable MoreVariables",
"MoreVariables :",
"MoreExpressions : ',' Expression MoreExpressions",
"MoreExpressions :",
"OptionalExpression : Expression",
"OptionalExpression :",
"Expression : Primary MoreOperand",
"MoreOperand : '*' Primary",
"MoreOperand :",
"Primary : ID MorePrimary",
"Primary : NUM",
"Primary : S_TRUE",
"Primary : S_FALSE",
"Primary : S_TEXT",
"MorePrimary : ArrayAccess",
"MorePrimary : FieldAccess",
"MorePrimary : FunctionCall",
"MorePrimary :",
"ArrayAccess : '[' Expression ']' MorePrimary",
"FieldAccess : '.' ID MorePrimary",
"FunctionCall : '(' OptionalArgumentList ')' MorePrimary",
"OptionalArgumentList : Expression MoreExpressions",
"OptionalArgumentList :",
"DeclarationOrStatement : VariableDeclaration",
"DeclarationOrStatement : KeywordStatement",
"DeclarationOrStatement : OtherStatement",
"KeywordStatement : Jump",
"Jump : S_RETURN OptionalExpression ';'",
"OtherStatement : ID MorePrimary RestOfExpressionStatement",
"RestOfExpressionStatement : OptionalAssignment ';'",
"OptionalAssignment : '=' Expression",
"OptionalAssignment :",
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
#line 279 "ea.y"


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
#line 386 "y.tab.c"
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
case 4:
#line 98 "ea.y"
{ printf("Function\n");}
break;
case 6:
#line 100 "ea.y"
{ printf("Type\n");}
break;
case 8:
#line 102 "ea.y"
{ printf("Var\n");}
break;
case 18:
#line 133 "ea.y"
{printf("<MAIN\n");}
break;
case 19:
#line 134 "ea.y"
{printf("<%s>\n",yyvsp[0].code);}
break;
case 64:
#line 247 "ea.y"
{printf(" F(...)\n");}
break;
case 65:
#line 248 "ea.y"
{printf(" F()\n");}
break;
#line 554 "y.tab.c"
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
