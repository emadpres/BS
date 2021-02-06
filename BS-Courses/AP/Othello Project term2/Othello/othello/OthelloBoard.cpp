#include "OthelloBoard.h"
#include "OthelloItem.h"
#include "OthelloLogic.h"
#include "GameController.h"

OthelloBoard::OthelloBoard(GameController* control,int size):QGraphicsRectItem(){
	this->control = control;
	_size = size;
	setRect(0,0,_size*ITEMW,_size*ITEMW);
	setBrush(QBrush(QColor(Qt::gray)));
	for(int i=0;i<_size;i++){
		items.append(QList<OthelloItem*>());
		for(int j=0;j<_size; j++)
			items[i].append(new OthelloItem(this,i,j));
	}
	whitemark = new QGraphicsTextItem("white:0",this);
	whitemark->setPos(0,-ITEMW);
	whitemark->setDefaultTextColor(QColor(Qt::red));
	blackmark = new QGraphicsTextItem("black:0",this);
	blackmark->setPos(_size*ITEMW,-ITEMW);
	blackmark->setDefaultTextColor(QColor(Qt::red));
}

void OthelloBoard::clicked(int row, int column){
	control->humanPlay(row,column);
}

TURN OthelloBoard::currentHumanPlayer(){
	return WHITE;
}

int OthelloBoard::size(){
	return items.size();
}

void OthelloBoard::setState(BOARD x){
	int bm = 0;
	int wm = 0;
	OthelloLogic::createHoles(x);
	for(int i=0;i<x.size();i++)
		for(int j=0;j<x[0].size();j++){
			if(x[i][j]==WHITE)
				wm++;
			if(x[i][j]==BLACK)
				bm++;
			items[i][j]->changeTo(x[i][j]);
		}
		whitemark->setPlainText("White:"+QString::number(wm));
		blackmark->setPlainText("Black:"+QString::number(bm));

	cout << "set state:" << endl;
	for(int i=0;i<items.size();i++){
		x.append(QList<TURN>());
		for(int j=0;j<items[i].size();j++){
			
			cout << (int)items[i][j]->turn() << "\t";
		}
		cout << endl;
	}

}

BOARD  OthelloBoard::state(){
	
	BOARD x;
	for(int i=0;i<items.size();i++){
		x.append(QList<TURN>());
		for(int j=0;j<items[i].size();j++)
			x[i].append(items[i][j]->turn());
	}
	OthelloLogic::createHoles(x);
	cout << "get state:" << endl;
	for(int i=0;i<items.size();i++){
		cout << "\t" ;
		for(int j=0;j<items[i].size();j++){
			cout << (int)items[i][j]->turn() << "\t";
		}
		cout << endl;
	}
	return x;
}	
