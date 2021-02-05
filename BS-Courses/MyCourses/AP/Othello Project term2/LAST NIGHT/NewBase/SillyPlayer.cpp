#include "SillyPlayer.h"
#include "OthelloBoard.h"
#include "OthelloLogic.h"
#include <QDateTime>

SillyPlayer::SillyPlayer(OthelloBoard* board,TURN turn):OthelloPlayer(board,turn){
	qsrand((int)QDateTime::currentDateTime().toTime_t());
}

QString SillyPlayer::getName(){
	return "A Very Simple Player";
}
QList<QString> SillyPlayer::getAuthors(){
	return QList<QString>() <<"A Very Simple Author!!!";
}
QPair<int,int> SillyPlayer::nextPlay(){
	BOARD b = board->state();
	for(int i=0;i<b.size();i++)
		for(int j=0;j<b[i].size();j++)
			if((b[i][j]==BOTHHOLE)||(b[i][j]==OthelloLogic::HoleOf(turn)))
				return QPair<int,int>(i,j);
	return QPair<int,int>(0,0);
}