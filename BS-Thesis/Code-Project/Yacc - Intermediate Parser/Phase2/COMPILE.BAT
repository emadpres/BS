flex ea.l
move/y lex.yy.c lex.c

yacc -d  -v ea.y
python correct.py
move/y y.tab.c y.c
move/y y.tab.h y.h

cl y.c main.cpp tinyxml2.cpp /FecodeAnalyser.exe

del lex.c y.c y.h y.output main.obj y.obj tinyxml2.obj