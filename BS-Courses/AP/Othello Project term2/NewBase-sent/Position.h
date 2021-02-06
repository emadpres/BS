#ifndef __POSITION_H__
#define __POSITION_H__

#include "OurBasics.h"
#include "mbasics.h"
#include <iostream>
#include <fstream>
class Position
{	
	public:
		Position(bool ourTurn);
		void makeMoveList(MOVE list[], int& moveCounter, int & opponentMoveCounter);
		int makeMoveList(MOVE list[]);
		void doMove(MOVE * move);
		void undoMove(MOVE * move);
		void potentialMobility(int & ourFrontier, int & opponentFrontier);
		
		int board[GAMESIZE][GAMESIZE];
		int turn;  // Dynamic turn :?EA Yes it is EA
	
		int remainingMoves;
		int whiteScore,blackScore;


		//void showBoard();
		//std::ofstream LOG;
		
		bool blackHasCornerUpLeft;
		bool blackHasCornerUpRight;
		bool blackHasCornerDownRight;
		bool blackHasCornerDownLeft;
		bool whiteHasCornerUpLeft;
		bool whiteHasCornerUpRight;
		bool whiteHasCornerDownRight;
		bool whiteHasCornerDownLeft;
		
		
};
#endif
