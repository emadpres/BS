#define _HAS_EXCEPTIONS 0	// because of cl.exe warning. more: http://stackoverflow.com/questions/552695/how-can-i-switch-off-exception-handling-in-msvc
#include <iostream>

extern "C" 
int StartParsing(char inputFile[100]);


extern "C" 
void cppFunc()
{
}

void main(int arg_count,char ** arg_values)
{
	if(arg_count<=1)
		printf("No input cpp file !\n");
	else
		StartParsing(arg_values[1]);
}