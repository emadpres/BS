#include "OurPlayer.h"
#include "OthelloBoard.h"
#include "MainTasks.cpp"
#include <QDateTime>

OurPlayer::OurPlayer(OthelloBoard* board,STATE turn, int depth):OthelloPlayer(board,turn)
{
	qsrand((int)QDateTime::currentDateTime().toTime_t());
	ourTurn=turn;
	this->depth=depth;
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
	OthelloAbstractBoard abstractBoard = board->getState();
	//BOARD board=board->getState();
	
	position->turn=ourTurn;
	
	if (ourTurn==WHITE)
		position->remainingMoves--;


	position->key = 0;
	//later move this part to position->update(board)
	for(int i=0;i<GAMESIZE;i++)
		for(int j=0;j<GAMESIZE;j++)
		{
			if(abstractBoard.items[i][j]!=HOLE) //BOTH HOLE, WHITE HOLE, BLACKHOLE
				position->board[i][j]=abstractBoard.items[i][j];
				position->key ^= position->hashNumbers[i][j][abstractBoard.items[i][j]]; // Then change it
		}
//				position.board[i][j]=board[i][j];



	MOVE bestMove;
	bestMove = firstAlphabeta(position,depth, -INFINITY, INFINITY);

	if (ourTurn==WHITE)
		position->remainingMoves--;
	else //if ourTurn==BLACK
		position->remainingMoves+=2;
		
	//cout << "best move here: \n" << bestMove.x << "\n" << " and\n "<< bestMove.y << "\n"; 
   return QPair<int,int>(bestMove.x,bestMove.y);//bestMove.x,bestMove.y);

}


