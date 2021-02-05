#ifndef __OURPLAYER_H__
#define __OURPLAYER_H__

#include "OthelloPlayer.h"
#include "Position.h"



class OurPlayer: public OthelloPlayer
{
public:
	OurPlayer(OthelloBoard* board,STATE turn, int depth);
	
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	
private:
	int depth;
	bool ourTurn;
	Position * position;
	
	int alphabeta(Position * position, int depth, int alpha, int beta);
	MOVE firstAlphabeta(Position * position, int depth, int alpha, int beta);
	int evaluation(Position * postion);
	
	//int lookup(Position *position, int depth, int *alpha, int *beta, int *hashvalue);
	//void store(Position *position, int depth, int bestvalue, int alpha, int beta);	

};

#endif
