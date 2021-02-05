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
	QPolygonF polygon;
	int starwidth = ITEM_WIDTH * 0.6;
	polygon << QPointF(starwidth, starwidth/2);
	for (int i = 1; i <5; ++i)
   		polygon << QPointF(starwidth/2 + starwidth/2 * cos(0.8 * i * 3.14), starwidth/2 + starwidth/2 * sin(0.8 * i * 3.14));
	starPolygon = new QGraphicsPolygonItem (polygon,this);
	int offSet = 0.2 * ITEM_WIDTH;
   starPolygon->translate(column*ITEM_WIDTH + offSet, row*ITEM_WIDTH +  offSet);
	starPolygon->setPen(QPen(Qt::NoPen));
	starPolygon->setBrush(QBrush(QColor(Qt::yellow)));
	starPolygon->setFillRule(Qt::WindingFill);
	starPolygon->hide();
}

void OthelloItem::initializeCircle()
{
	QPolygonF polygon;
	int width = ITEM_WIDTH * 0.7;
	polygon << QPointF(width, width/2);
	for (int i = 1; i <10; ++i)
   		polygon << QPointF(width/2 + width/2 * cos(0.6 * i * 3.14), width/2 + width/2 * sin(0.6 * i * 3.14));
	tenPolygon = new QGraphicsPolygonItem (polygon, this);
	int offSet = 0.15 * ITEM_WIDTH;
  	tenPolygon->translate(column*ITEM_WIDTH + offSet, row*ITEM_WIDTH +  offSet);
	tenPolygon->setPen(QPen(Qt::NoPen));
	tenPolygon->setBrush(QBrush(QColor::fromRgb(220,210,40)));
	tenPolygon->setFillRule(Qt::WindingFill);
	tenPolygon->hide();	
	
	circle = new QGraphicsEllipseItem(tenPolygon);
	int circlewidth = ITEM_WIDTH * 0.5;
	int circleOffSet = ITEM_WIDTH * 0.1;
	circle->setRect(circleOffSet, circleOffSet, circlewidth , circlewidth);
	circle->setPen(QPen(Qt::NoPen));
	circle->setBrush(QBrush(QColor::fromRgb(245,205,30)));
	//circle->hide();
}

void OthelloItem::changeTo(int state)
{
	switch(state)
	{
		case WHITE:
			QTimer::singleShot(board->delayDuration, this, SLOT(paintWhite()));
			this->state = WHITE;
			break;						
		case BLACK:
			QTimer::singleShot(board->delayDuration, this, SLOT(paintBlack()));
			this->state = BLACK;
			break;
		case EMPTY:
			this->state = EMPTY;
			paintEmpty();
			break;
		case HOLE:
			this->state = HOLE;
			paintEmpty(); // Later I draw a shape for hole positions
	}
}

void OthelloItem::paintEmpty()
{
	starPolygon->hide();
	//circle->hide();
	tenPolygon->hide();
	setBrush(QBrush(QColor::fromRgb(52,101,164)));
	setPen(QPen(Qt::NoPen));
	//this->hide();
}
void OthelloItem::paintWhite()
{
	//this->show();
	starPolygon->hide();
	tenPolygon->show();
//	circle->show();
	setBrush(QBrush(Qt::white));
	setPen(QPen(Qt::NoPen));
}
void OthelloItem::paintBlack()	
{
	//this->show();
	//circle->hide();
	tenPolygon->hide();
	starPolygon->show();
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
		{	
			board->delayDuration += 170;
			changeTo(board->currentTurn);
		}
		return true;

	}

	return false;
}

void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{

	//setTransform(QTransform(1,0.12345,0.000000001,0.2,1,0.00000001,0,0,1));
	if (state == HOLE )
		play();
}

void OthelloItem::play()
{
	board->delayDuration = 0;
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
