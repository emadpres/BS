#ifndef __REVPOSITION_H__
#define __REVPOSITION_H__

#include "OurBasics.h"
#include "BASICS.h"
class RevPosition
{	
	public:
		RevPosition(bool ourTurn);
		int makeMoveList(MOVE list[]);
		void doMove(MOVE * move);
		void undoMove(MOVE * move);
		
		int board[GAMESIZE][GAMESIZE];
		bool turn;
		int remainingMoves;
};

#endif
