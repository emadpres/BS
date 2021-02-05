#ifndef __OURPLAYER_H__
#define __OURPLAYER_H__

#include "OthelloPlayer.h"

class OurPlayer: public OthelloPlayer
{
public:
	OurPlayer(OthelloBoard* board,STATE turn);
	
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	
};

#endif
