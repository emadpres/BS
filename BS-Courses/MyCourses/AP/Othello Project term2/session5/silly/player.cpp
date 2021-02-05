#include "player.h"
#include "OthelloBoard.h"
#include "OthelloLogic.h"
#include <QDateTime>


player::player():OthelloPlayer(){
	qsrand(QDateTime::currentDateTime().toTime_t());
}

player::~player()
{

}


void player::init(OthelloBoard* b,TURN t){
	OthelloPlayer::init(b,t);
}

QString player::getName()
{
	return "Silly Team";
}

QList<QString> player::getAuthors()
{
	return QList<QString>() << "Dr. Adel Torkaman Rahmani" << "Meisam Ahmadi(88922049)" ;
}

QPair<int,int>	player::nextPlay()
{
	BOARD b = board->state();
	int forsat = 0;
	for(int i=0;i<b.size();i++)
		for(int j=0;j<b.size();j++)
			if((b[i][j]==OthelloLogic::HoleOf(turn))||(b[i][j]==BOTHHOLE))
				forsat++;
	int r = forsat*qrand()/RAND_MAX +1;
	forsat = 0;
	for(int i=0;i<b.size();i++)
		for(int j=0;j<b.size();j++)
			if((b[i][j]==OthelloLogic::HoleOf(turn))||(b[i][j]==BOTHHOLE))
			{
				forsat++;
				if(forsat==r)
					return QPair<int,int>(i,j);
			}
	return QPair<int,int>(0,0);
}


extern "C"{
__declspec(dllexport) void* getNewInstance()
{
	return (void*) ((OthelloPlayer*)new player());
}
}