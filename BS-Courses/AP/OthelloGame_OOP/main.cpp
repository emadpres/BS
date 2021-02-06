#define BOARDSIZE 8


#include <iostream>
#include <windows.h>
#include <conio.h>

#include "OthelloBoard.h"
#include "OthelloItem.h"


using namespace std ;


void gotoxy( short x, short y )
{	
	//Learned from Internet
	// Use windows.h

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD position = { x, y };

	SetConsoleCursorPosition( hStdout, position );

}


int main()
{
	OthelloBoard myBoard;
	myBoard.show();
	myBoard.Score();
	
	
	getch();
	return 0;
	
}