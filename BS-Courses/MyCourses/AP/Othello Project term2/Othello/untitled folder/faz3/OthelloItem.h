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
		void Turn_Unit();
		void checkUnit(int turn,int whiteScore,int blackScore,OthelloBoard* parent);
		
		void setState(int);
		int getState();
		
		bool canUnit(int x,int y);
		void holeUnit();
		bool colorUnit(int x, int y);
		void mousePressEvent ( QGraphicsSceneMouseEvent * event );

private:
	
		
	
	int row,column;
	int state;
	OthelloBoard* board;
};

