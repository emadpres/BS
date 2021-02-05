#ifndef __OTHELLOABSTRACTBOARD_H__
#define __OTHELLOABSTRACTBOARD_H__

#include "BASICS.h"

class OthelloAbstractBoard
{
	public:
		OthelloAbstractBoard();
		BOARD items;
		void clearLastHoles();
		void createHoles(STATE currentTurn);
		bool noMove();
		void IsHole(int x, int y, STATE currentTurn);
		void play(int x, int y, STATE currentTurn);
		bool canPlay(int x, int y);
		int scoreUnit(STATE turn);
		STATE winner();
		BOARD getItems(); // can be used by OthelloPlayer
	private:	
		bool checkPath(int x, int y, int i, int j, STATE currentTurn, bool apply = false);
};

#endif
