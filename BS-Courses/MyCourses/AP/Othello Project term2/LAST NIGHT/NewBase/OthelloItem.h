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
	//� ���� �� ��� ����� ������
	OthelloItem(OthelloBoard* parent,int row,int column);
	//����� ����� ���� �� ���������
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

