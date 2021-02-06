#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

const int ITEMW = 50;
const int GAMESIZE=8;

class OthelloBoard;

class OthelloItem:public QGraphicsEllipseItem{
public:
		OthelloItem(OthelloBoard* parent,int row,int column);
private:
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	int row,column;
	int state;
	OthelloBoard* board;
};

