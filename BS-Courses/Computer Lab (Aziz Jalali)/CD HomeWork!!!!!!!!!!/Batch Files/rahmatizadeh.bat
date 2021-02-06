@echo off

set /p a="PLEASE ENTER YOUR DIRECTORY :" 

if not exist  %a% (echo %a% does not exist) else (echo %a% exists


set /p b="PLEASE ENTER YOUR DIRECTORY :"

)

copy %a% %b%

if exist %b% echo %b% was successfully copied!

pause

