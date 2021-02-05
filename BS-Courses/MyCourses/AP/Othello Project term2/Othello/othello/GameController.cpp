#include "GameController.h"
#include <iostream>
#include "OthelloBoard.h"
#include "OthelloLogic.h"
#include "OthelloPlayer.h"
#include "SillyPlayer.h"

GameController::GameController(QGraphicsScene* scene){
	this->scene = scene;
	
	int size = GAMESIZE;
	currentTurn = WHITE;
	
	
	board = new OthelloBoard(this,size);
	player = new SillyPlayer(board,(int)(currentTurn == WHITE)? BLACK:WHITE);
	
	QList< QList<TURN> > x;
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
		
		QPair<int,int> r;
		do{
			r = player->nextPlay();
			std::cout << "PC play:" << r.first << "," << r.second << "," << currentTurn << std::endl;
		}while((!OthelloLogic::canPlay(b,currentTurn))||(!OthelloLogic::play(b,r.first,r.second,currentTurn)));
		
		board->setState(b);
		currentTurn = (currentTurn == WHITE)? BLACK:WHITE;
		
	}
}
