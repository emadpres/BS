#include "OthelloPlayer.h"

class SillyPlayer:public OthelloPlayer{
public:
	SillyPlayer(OthelloBoard* board,TURN turn);
	
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	
};