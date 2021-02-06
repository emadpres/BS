#include "BASICS.h"
#include "OthelloAbstractBoard.h"

#include <iostream>
using std::cout;


class OthelloDocumenter
{
	public:
		OthelloDocumenter ();
		void outputMove(int x , int y);
		void outputBoard(OthelloAbstractBoard);
		void outputScore(OthelloAbstractBoard);
		void outputTurn(STATE turn);
		void outputNoMove(STATE turn);
		void outputWinner(OthelloAbstractBoard);
	private:
		
};
