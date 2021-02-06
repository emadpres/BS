#include "OthelloBoard.h"
#include "OthelloItem.h"

OthelloBoard::OthelloBoard():QGraphicsRectItem(){}
void OthelloBoard::clicked(int row, int column){
		items[row][column]->setBrush(QBrush(QColor(Qt::white)));
	}

