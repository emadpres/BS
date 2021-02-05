flex minicpp.l
move/y lex.yy.c lex.c

yacc -d -v minicpp.y
move/y y.tab.c y.c
move/y y.tab.h y.h

echo "Delete YYSTYPE variable after union form y.h ! Then press any key :D"

cl y.c main.cpp /FecodeAnalyser.exe

del lex.c y.c y.h main.obj y.obj