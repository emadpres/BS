#include "GameController.h"
#include <iostream>
#include "OthelloBoard.h"
#include "OthelloLogic.h"
#include "OthelloPlayer.h"
#include "SillyPlayer.h"
#include "OurPlayer.h"

GameController::GameController(QGraphicsScene* scene){
	this->scene = scene;
	
	int size = GAMESIZE;
	currentTurn = WHITE;
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(agentTimer()));
	
	
	board = new OthelloBoard(this,size);
	player = new OurPlayer(board,(int)(currentTurn == WHITE)? BLACK:WHITE);
	
	QList<QList<TURN> > x;
	x = board->state();
	x[size/2-1][size/2-1] = WHITE;
	x[size/2][size/2] = WHITE;
	x[size/2][size/2-1] = BLACK;
	x[size/2-1][size/2] = BLACK;
	board->setState(x);
	
	scene->addItem(board);
}


void GameController::humanPlay(int x, int y){

		std::cout << "Human play:" << x << "," << y << "," << currentTurn << std::endl;
		QList<QList<TURN> > b = board->state();
		if((OthelloLogic::play(b,x,y,currentTurn)) || (!OthelloLogic::canPlay(b,currentTurn))){
			board->setState(b);
			currentTurn = (currentTurn == WHITE)? BLACK:WHITE;
			
			timer->setSingleShot(1000);
			timer->start();
		}

}

void GameController::agentTimer(){
	QList< QList<TURN> > b = board->state();
	if((!OthelloLogic::canPlay(b,currentTurn))&&(!OthelloLogic::canPlay(b,(currentTurn == WHITE)? BLACK:WHITE))){
		std::cout << "finished" << std::endl;
		return;
	}
	if(!OthelloLogic::canPlay(b,currentTurn)){
		currentTurn = (currentTurn == WHITE)? BLACK:WHITE;
		return;
	}

	QPair<int,int> r;

	OthelloPlayer* nowplayer = player;

	r = nowplayer->nextPlay();
	std::cout << "PC play:" << r.first << "," << r.second << "," << currentTurn << std::endl;
	if((!OthelloLogic::canPlay(b,currentTurn))||(!OthelloLogic::play(b,r.first,r.second,currentTurn)))
	{
		timer->setSingleShot(10);
		timer->start();
		return;
	}
	
	board->setState(b);
	currentTurn = (currentTurn == WHITE)? BLACK:WHITE;
}
