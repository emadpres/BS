#ifndef PLAYER_H
#define PLAYER_H

#include "player_global.h"
#include "OthelloPlayer.h"

class PLAYER_EXPORT player:OthelloPlayer
{
public:
	player();
	~player();

	void init(OthelloBoard* b,TURN t);
	QString getName();
	QList<QString> getAuthors();
	QPair<int,int> nextPlay();	

private:

};
extern "C"__declspec(dllexport) void* getNewInstance();
#endif // PLAYER_H
