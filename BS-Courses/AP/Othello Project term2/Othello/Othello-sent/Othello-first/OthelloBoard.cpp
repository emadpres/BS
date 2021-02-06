#include "OthelloBoard.h"

#include <QGraphicsEllipseItem>



OthelloBoard::OthelloBoard(QLabel * scoreLabel, QLabel * turnLabel):QGraphicsRectItem()
{
	setRect(0,0,GAMESIZE * ITEM_WIDTH,GAMESIZE * ITEM_WIDTH);
	setBrush(QBrush(QColor::fromRgb(52,101,164)));
	
	this->scoreLabel = scoreLabel;	
	this->turnLabel = turnLabel;
	
	for(int i=0; i<GAMESIZE; i++)
	{
		items.append( QList<OthelloItem*> ());
		for (int j=0; j<GAMESIZE; j++)
			items[i].append(new OthelloItem(this, i, j));
	}

	delayDuration = 0;

	initializeGame();
}

void OthelloBoard::initializeGame()
{
	int size = GAMESIZE;
	currentTurn = BLACK;

	items[size/2-1][size/2-1]->changeTo(WHITE);
	items[size/2][size/2]-> changeTo(WHITE);  
	items[size/2][size/2-1]-> changeTo(BLACK);
	items[size/2-1][size/2]-> changeTo(BLACK);
	
	findHoles();
}

void OthelloBoard::findHoles()
{
	clearLastHoles();
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			items[i][j]->IsAHole();
}

void OthelloBoard::clearLastHoles()
{
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			if (items[i][j]->state==HOLE)
				items[i][j]->changeTo(EMPTY);
}

void OthelloBoard::changeTurn()
{
	if (currentTurn == WHITE)
		currentTurn = BLACK;
	else 
		currentTurn = WHITE;
}

int OthelloBoard::scoreUnit(int turn)
{
	int score =0;
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
		{
			if (items[i][j]->state == turn)
				score++;
		}
	return score;
}

void OthelloBoard::showScore()
{

	int whiteScore= scoreUnit(WHITE);
	int blackScore= scoreUnit(BLACK);

	QString string;
	string.append("Dark:" + QString::number(blackScore));
	string.append(" Light:" + QString::number(whiteScore));
	scoreLabel->setText(string);
}

bool OthelloBoard::noMove()
{
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			if (items[i][j]->state == HOLE)
				return false;
	return true;
}

void OthelloBoard::showTurn()
{
	if (noMove()) // again no move
	{
		int whiteScore = scoreUnit(WHITE);	
		int blackScore = scoreUnit(BLACK);
		
		if (whiteScore > blackScore)
			turnLabel->setText("Light is the Winner!");
		else if (whiteScore < blackScore)
			turnLabel->setText("Dark is the Winner!");
		else // (whiteScore == blackScore)
			turnLabel->setText("Draw, Tied Up!");

		return;
	}
	if (currentTurn == WHITE)
		turnLabel->setText("Light's Move");
	if (currentTurn == BLACK)
		turnLabel->setText("Dark's Move");
}
