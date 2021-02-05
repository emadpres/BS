
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
	//ÓÇÒäÏå Çí ˜å ˜äÊÑáÑ æ ÇäÏÇÒå ÊÎÊå ÑÇ ãííÑÏ
	OthelloBoard(GameController* control,int size);
	
	//Çíä ÊÇÈÚ æÖÚíÊ ˜äæäí ÊÎÊå ÑÇ ÈÑãíÑÏÇäÏ
	BOARD state();
	//Çíä ÊÇÈÚ ÇäÏÇÒå ÊÎÊå ÑÇ ÈÑãíÑÏÇäÏ
	int size();
//ãÊæÏ åÇí ÒíÑ ÇÒ ÏíÏ ÈÇÒí˜ä äåÇä ÎæÇåäÏ ÈæÏ	
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


