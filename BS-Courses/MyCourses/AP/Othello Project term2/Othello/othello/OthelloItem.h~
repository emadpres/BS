#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "mbasics.h"

class OthelloBoard;

class OthelloItem:public QGraphicsEllipseItem{
public:
	//Ìò ¬Ì „ œ— „Õ· „‘Œ’Ì „Ì”«“œ
	OthelloItem(OthelloBoard* parent,int row,int column);
	//Ê÷⁄Ì  ò‰Ê‰Ì Œ«‰Â —« »—„Ìê—œ«‰œ
	TURN turn();
private:
	void changeTo(TURN color);
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	int row,column;
	int state;
	TURN _turn;
	OthelloBoard* board;
	friend class OthelloBoard;
};

