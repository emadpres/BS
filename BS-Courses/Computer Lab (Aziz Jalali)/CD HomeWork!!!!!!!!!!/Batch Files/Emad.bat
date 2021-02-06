
@echo off

set /P sourcefile= Enter source file Address :
if not exist %sourcefile% (%0)



set /P destinationfile= Enter destination file Address:


echo we want to copy from : 
SET sourcefile
echo To :
SET destinationfile


Pause
copy %sourcefile% %destinationfile%
