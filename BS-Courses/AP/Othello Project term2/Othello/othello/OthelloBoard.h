
#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "MBasics.h"

class OthelloItem;
class GameController;
class OthelloBoard:public QGraphicsRectItem{
public:
	//������ �� �� ������ � ������ ���� �� �����
	OthelloBoard(GameController* control,int size);
	
	//��� ���� ����� ����� ���� �� ���������
	BOARD state();
	//��� ���� ������ ���� �� ���������
	int size();
//���� ��� ��� �� ��� ����� ����� ������ ���	
private:
	QList< QList<OthelloItem*> > items;
	QGraphicsTextItem *whitemark, *blackmark;
	int _size;
	GameController* control;
	
	TURN currentHumanPlayer();
	void clicked(int row, int column);
	void setState(BOARD x);
	
	friend class OthelloItem;
	friend class GameController;
	friend class SillyPlayer;
};


