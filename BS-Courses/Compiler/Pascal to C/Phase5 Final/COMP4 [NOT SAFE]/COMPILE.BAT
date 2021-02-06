flex lea.l
move/y lex.yy.c lex.c

yacc yea.y
move/y y.tab.c y.c

yacc -d yea.y
move/y y.tab.h y.h

echo "Delte enum..code form y.h ! Then press any key :D"
y.h
pause

cl  y.c