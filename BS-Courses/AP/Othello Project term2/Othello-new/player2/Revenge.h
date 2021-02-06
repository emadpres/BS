#ifndef __REVENGE_H__
#define __REVENGE_H__

#include "OthelloPlayer.h"
#include "RevPosition.h"

class Revenge: public OthelloPlayer
{
public:
	Revenge(OthelloBoard* board,STATE turn, int depth);
	
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	
private:
	int depth;
	bool ourTurn;
	RevPosition * position;
	
	int alphabeta(RevPosition * position, int depth, int alpha, int beta);
	MOVE firstAlphabeta(RevPosition * position, int depth, int alpha, int beta);
	int evaluation(RevPosition * postion);
	
};

#endif
