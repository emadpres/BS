#include "OurBasics.h"
#include "BASICS.h"
class Position
{	
	public:
		Position(bool ourTurn);
		int makeMoveList(MOVE list[]);
		void doMove(MOVE * move);
		void undoMove(MOVE * move);
		
		int board[GAMESIZE][GAMESIZE];
		bool turn;
		int remainingMoves;
};
