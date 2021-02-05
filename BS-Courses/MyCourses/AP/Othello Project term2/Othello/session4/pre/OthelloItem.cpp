#include "OthelloItem.h"
#include "OthelloBoard.h"
OthelloItem::OthelloItem(OthelloBoard* parent,int row,int column):QGraphicsEllipseItem(column*ITEMW,row*ITEMW,ITEMW,ITEMW,parent){
			board = parent;
			this->row = row;
			this->column = column;
			setBrush(QBrush(QColor(Qt::red)));
		}
void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ){
		board->clicked(row,column);
	}

