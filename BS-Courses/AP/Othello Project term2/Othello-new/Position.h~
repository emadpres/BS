#include "OurBasics.h"
#include "BASICS.h"

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
		bool turn;
		int remainingMoves;

		int hashNumbers[GAMESIZE][GAMESIZE][2];
		int key;
};

