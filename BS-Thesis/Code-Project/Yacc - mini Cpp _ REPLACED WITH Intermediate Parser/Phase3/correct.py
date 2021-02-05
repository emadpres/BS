f = open("y.tab.h",'r')
filedata = f.read()
f.close()

newdata = filedata.replace("} YYSTYPE;","};")

f = open("y.tab.h",'w')
f.write(newdata)
f.close()