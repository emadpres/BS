	#include "OthelloItem.h"
#include "OthelloBoard.h"
OthelloItem::OthelloItem(OthelloBoard* parent,int row,int column):QGraphicsEllipseItem(column*ITEMW,row*ITEMW,ITEMW,ITEMW,parent){
			board = parent;
			this->row = row;
			this->column = column;
			changeTo(EMPTY);
		}
		
TURN OthelloItem::turn(){
	return _turn;
}		

void OthelloItem::changeTo(TURN color){
	_turn = color;
	
	QPen p;
	p.setStyle(Qt::DashDotLine);
	p.setBrush(Qt::lightGray);

	setBrush(QBrush(QColor(Qt::gray)));
	
	if(color==WHITE)
		setBrush(QBrush(QColor(Qt::white)));
	else if(color==BLACK)
		setBrush(QBrush(QColor(Qt::black)));
	else if(color==WHITEHOLE)
		p.setBrush(Qt::white);
	else if(color==BLACKHOLE)
		p.setBrush(Qt::black);
	else if(color==BOTHHOLE)
		p.setBrush(Qt::green);

	setPen(p);
		
}		
void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ){
		board->clicked(row,column);
	}

