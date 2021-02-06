#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>


class OthelloItem;
class OthelloBoard:public QGraphicsRectItem
{
friend class OthelloItem;
public:
	OthelloBoard();
	QList< QList<OthelloItem*> > items;
	void clicked(int row, int column);
	void initial();
	int turn;
private:
	QGraphicsTextItem *whitemark, *blackmark;

};

