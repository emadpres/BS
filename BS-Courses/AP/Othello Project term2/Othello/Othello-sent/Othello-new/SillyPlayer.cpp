#include "SillyPlayer.h"
#include "OthelloBoard.h"
#include <QDateTime>

SillyPlayer::SillyPlayer(OthelloBoard* board,STATE turn):OthelloPlayer(board,turn)
{
	qsrand((int)QDateTime::currentDateTime().toTime_t());
}

QString SillyPlayer::getName()
{
	return "The Same Simple Player but changed a little!";
}

QList<QString> SillyPlayer::getAuthors()
{
	return QList<QString>() <<"A Very Simple Author!!!";
}

QPair<int,int> SillyPlayer::nextPlay()
{
	OthelloAbstractBoard abstractBoard = board->getState();
	for(int i=0;i<GAMESIZE;i++)
		for(int j=0;j<GAMESIZE;j++)
			if(abstractBoard.canPlay(i,j))
				return QPair<int,int>(i,j);
	return QPair<int,int>(0,0);
}
