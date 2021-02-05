#ifndef __SILLYPLAYER_H__
#define __SILLYPLAYER_H__

#include "OthelloPlayer.h"

class SillyPlayer:public OthelloPlayer
{
public:
	SillyPlayer(OthelloBoard* board,STATE turn);
	
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	
};

#endif
