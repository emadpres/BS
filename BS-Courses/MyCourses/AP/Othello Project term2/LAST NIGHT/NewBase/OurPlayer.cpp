#include "OurPlayer.h"
#include "OthelloBoard.h"
#include "MainTasks.cpp"
#include <QDateTime>

OurPlayer::OurPlayer(OthelloBoard* board,TURN turn):OthelloPlayer(board,turn)
{
	qsrand((int)QDateTime::currentDateTime().toTime_t());
	ourTurn=turn;
	this->firstDepth=8;
	position = new Position(turn);	
}

QString OurPlayer::getName()
{	
	return "Our Player!";
}

QList<QString> OurPlayer::getAuthors()
{
	return QList<QString>() <<"EA & PJ";
}

QPair<int,int> OurPlayer::nextPlay()
{
//	OthelloAbstractBoard abstractBoard = board->getState();
	BOARD abstractBoard=this->board->state();
	
	position->turn=ourTurn;
	
	if (ourTurn==WHITE)
		position->remainingMoves--;

	position->whiteScore=position->blackScore=0;
	position->key = 0;
	//later move this part to position->update(board)
	for(int i=0;i<GAMESIZE;i++)
		for(int j=0;j<GAMESIZE;j++)
		{
			if(abstractBoard[i][j]==WHITE || abstractBoard[i][j]==BLACK ) //BOTH HOLE, WHITE HOLE, BLACKHOLE
			{
				if(abstractBoard[i][j]==WHITE)
					position->whiteScore++;
				else 
					position->blackScore++;
				position->board[i][j]=abstractBoard[i][j];
				position->key ^= position->hashNumbers[i][j][(abstractBoard[i][j]==BLACK)?0:1]; // Then change it
			}
		}

	MOVE bestMove;
	bestMove = firstAlphabeta(position,firstDepth, -INFINITY, INFINITY);

	if (ourTurn==WHITE)
		position->remainingMoves--;
	else //if ourTurn==BLACK
		position->remainingMoves+=2;
		
	//cout << "best move here: \n" << bestMove.x << "\n" << " and\n "<< bestMove.y << "\n"; 
   return QPair<int,int>(bestMove.x,bestMove.y);//bestMove.x,bestMove.y);

}


