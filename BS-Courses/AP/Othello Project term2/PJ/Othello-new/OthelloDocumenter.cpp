#include "OthelloDocumenter.h"

OthelloDocumenter::OthelloDocumenter ()
{
}

void OthelloDocumenter::outputMove( int x , int y)
{
	cout << x+1 << " " << y+1 << "\n";
}

void OthelloDocumenter::outputTurn(STATE turn)
{
	if (turn == WHITE)
		cout << "White's Move: ";
	if (turn == BLACK)
		cout << "Black's Move: ";
}

void OthelloDocumenter::outputNoMove(STATE turn)
{
	if (turn == WHITE)
		cout << "There is no move for White.\n";
	if (turn == BLACK)
		cout << "There is no move for Black.\n";
}

void OthelloDocumenter::outputBoard(OthelloAbstractBoard abstractBoard)
{
	cout << "   ";
		for (int i=1; i<=GAMESIZE; i++)
			cout <<  "  "<< i << "  "; 
		cout << "\n\n";

		for (int i=1; i<=GAMESIZE; i++)	
		{	
			cout  << i << "  ";
			for(int j=1;j<=GAMESIZE;j++)
				switch(abstractBoard.items[i-1][j-1])
				{
					case EMPTY:
						cout << "  .  "; 
						break;
					case BLACK:
						cout << "  B  ";
						break;
					case WHITE:
						cout << "  W  ";
						break;
					case HOLE:
						cout << "  ?  "	;
						break;
				}
			cout << "\n\n";
		}
}

void OthelloDocumenter::outputScore(OthelloAbstractBoard abstractBoard)
{
	int whiteScore = abstractBoard.scoreUnit(WHITE);
	int blackScore = abstractBoard.scoreUnit(BLACK);
	
	cout << "White Score: " << whiteScore << "\n";
	cout << "Black Score: " << blackScore << "\n";	
}

void OthelloDocumenter::outputWinner(OthelloAbstractBoard abstractBoard)
{
	cout << "End of the Game!\n";
	int winner = abstractBoard.winner();

			if (winner == WHITE) 
				cout << "White is the Winner!\n";
			else if (winner == BLACK)
				cout << "Black is the Winner!\n";
			else if (winner==EMPTY)
				cout  << "Draw, Tied Up!\n";
}
