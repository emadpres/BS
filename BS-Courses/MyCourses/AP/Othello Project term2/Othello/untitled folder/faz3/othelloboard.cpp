#include "othelloboard.h"
#include "OthelloItem.h"
#define BLACK 0
#define WHITE 1
#define EMPTY 2

#include <iostream>

OthelloBoard::OthelloBoard():QGraphicsRectItem(){
turn =BLACK;
}
void OthelloBoard::clicked(int row, int column){
	
	
		items[row][column]->setBrush(QBrush(QColor(Qt::black)));
	
	
}

void OthelloBoard::initial()
{
	items[3][3]->setBrush(QBrush(QColor(Qt::black)));
	items[3][3]->setState(BLACK);

	items[4][4]->setBrush(QBrush(QColor(Qt::black)));
	items[4][4]->setState(BLACK);

	items[3][4]->setBrush(QBrush(QColor(Qt::white)));
	items[3][4]->setState(WHITE);
	
	items[4][3]->setBrush(QBrush(QColor(Qt::white)));
	items[4][3]->setState(WHITE);
	
	for(int i=0;i<GAMESIZE;i++)	
		for(int j=0;j<GAMESIZE;j++)
			items[i][j]->holeUnit();
}

