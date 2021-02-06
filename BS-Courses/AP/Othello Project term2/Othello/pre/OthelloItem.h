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
const int GAMESIZE= 8;

class OthelloBoard;

class OthelloItem:public QGraphicsEllipseItem{
public:
	OthelloItem(OthelloBoard* parent,int row,int column);
	void AmIAHole();
	int GetState();
	void SetState(int state);
	bool IsAPath(int preRow, int preColumn);
	bool FillThePath(int preRow, int preColumn);
		
private:
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	int row,column;
	int state;
	OthelloBoard* board;
};
