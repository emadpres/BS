#include "Othelloboard.h"
#include "OthelloItem.h"
#define BLACK 0
#define WHITE 1
#define EMPTY 2

OthelloBoard::OthelloBoard():QGraphicsRectItem(){

	whitemark = new QGraphicsTextItem("white:0",this);
	whitemark->setPos(0,-ITEMW);
	whitemark->setDefaultTextColor(QColor(Qt::red));
	blackmark = new QGraphicsTextItem("black:0",this);
	blackmark->setPos(GAMESIZE*ITEMW,-ITEMW);
	blackmark->setDefaultTextColor(QColor(Qt::red));
	turn = BLACK;

}
void OthelloBoard::clicked(int row, int column){

	
		items[row][column]->setBrush(QBrush(QColor(Qt::black)));
	
	}

void OthelloBoard::initial()
{
	items[3][3]->setBrush(QBrush(QColor(Qt::black)));
	items[4][4]->setBrush(QBrush(QColor(Qt::black)));
	items[3][4]->setBrush(QBrush(QColor(Qt::white)));
	items[4][3]->setBrush(QBrush(QColor(Qt::white)));
}

