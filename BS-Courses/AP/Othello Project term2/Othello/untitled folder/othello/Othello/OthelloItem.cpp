#include "OthelloItem.h"
#include <cmath>
#include <QPolygonF>
#include <QPainter>

OthelloItem::OthelloItem(OthelloBoard * board, int row, int column): QGraphicsEllipseItem(board)
{
	setRect(column*ITEM_WIDTH + 0.075 * ITEM_WIDTH,row*ITEM_WIDTH + 0.075 * ITEM_WIDTH,ITEM_WIDTH*0.85,ITEM_WIDTH*0.85);
	setPen(QPen(Qt::NoPen));
	
	this->board = board;
	this->row = row;
	this->column = column;
	
	initializeStar();
	initializeCircle();

	changeTo(EMPTY);
}

void OthelloItem::initializeStar()
{
	QPolygonF starPolygon;
	int starWidth = ITEM_WIDTH * 0.6;
	starPolygon << QPointF(starWidth, starWidth/2);
	for (int i = 1; i < 5; ++i)
   		starPolygon << QPointF(starWidth/2 + starWidth/2 * cos(0.8 * i * 3.14), starWidth/2 + starWidth/2 * sin(0.8 * i * 3.14));
	polygon = new QGraphicsPolygonItem (starPolygon, this);
	int offSet = 0.2 * ITEM_WIDTH;
   	polygon->translate(column*ITEM_WIDTH + offSet, row*ITEM_WIDTH +  offSet);
	polygon->setPen(QPen(Qt::NoPen));
	polygon->setBrush(QBrush(QColor(Qt::yellow)));
	polygon->setFillRule(Qt::WindingFill);
	polygon->hide();
}

void OthelloItem::initializeCircle()
{
	circle = new QGraphicsEllipseItem(this);
	int circleWidth = ITEM_WIDTH * 0.5;
	int circleOffSet = ITEM_WIDTH * 0.25;
	circle->setRect(column*ITEM_WIDTH + circleOffSet, row*ITEM_WIDTH + circleOffSet, circleWidth , circleWidth);
	circle->setPen(QPen(Qt::NoPen));
	circle->setBrush(QBrush(QColor::fromRgb(245,205,30)));
	circle->hide();
}

void OthelloItem::changeTo(int state)
{
	switch(state)
	{
		case WHITE:
			paintWhite();
			this->state = WHITE;
			break;						
		case BLACK:
			this->state = BLACK;
			paintBlack();
			break;
		case EMPTY:
			this->state = EMPTY;
			paintEmpty();
			break;
		case HOLE:
			this->state = HOLE;
			paintEmpty(); // Later I draw a shape for empty positions
	}
}

void OthelloItem::paintEmpty()
{
	polygon->hide();
	circle->hide();
	setBrush(QBrush(QColor::fromRgb(52,101,164)));
	setPen(QPen(Qt::NoPen));
}
void OthelloItem::paintWhite()
{
	polygon->hide();
	circle->show();
	setBrush(QBrush(Qt::white));
	setPen(QPen(Qt::NoPen));
}
void OthelloItem::paintBlack()	
{
	circle->hide();
	polygon->show();
	setBrush(QBrush(QColor::fromRgb(51,51,51)));
	setPen(QColor::fromRgb(104,104,87));
}

void OthelloItem::IsAHole()
{
	if (state==EMPTY)
	{
		int turn = board->currentTurn;
		for (int i=-1;i<=1;i++)
			for (int j=-1;j<=1; j++)
			{
				if ((i==0 && j==0) || row+i>=GAMESIZE || column+j>=GAMESIZE || row+i<0 || column+j<0) 
					continue;
				if (board->items[row+i][column+j]->state == (turn==BLACK?WHITE:BLACK))
					if (board->items[row+i][column+j]->IsAPath(i,j))
						changeTo(HOLE);

			}
	}
}
bool OthelloItem::IsAPath(int i, int j, bool play)
{
	if (row + i >= GAMESIZE || column + j >= GAMESIZE || column + j <0 || row + i <0)
		return false;
	
	int nextState = board->items[row +i][column+j]->state;
	
	if (nextState==EMPTY)
		return false;	

	if (nextState==(state==BLACK?WHITE:BLACK) ||
		((nextState==state) && board->items[row +i][column + j]->IsAPath(i,j, play)))
	{
		if (play == true)
			changeTo(board->currentTurn);
		return true;
	}

	return false;
}

void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	if (state == HOLE )
		play();
}

void OthelloItem::play()
{
	int turn = board->currentTurn;
	changeTo(turn);
	for (int i=-1;i<=1;i++)
		for (int j=-1;j<=1; j++)
		{
			if ((i==0 && j==0) || row+i>=GAMESIZE || column+j>=GAMESIZE || row+i<0 || column+j<0) 
				continue;
			if (board->items[row+i][column+j]->state == (turn==BLACK?WHITE:BLACK))
				board->items[row+i][column+j] -> IsAPath(i,j,true);
		}
	board->showScore();
	board->changeTurn();
	board->findHoles();
	if (board->noMove())
		{
			board->changeTurn();
			board->findHoles();
		}
	board->showTurn();
}
