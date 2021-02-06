#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#pragma once
#include <QGraphicsRectItem>


class OthelloItem;
class OthelloBoard:public QGraphicsRectItem{
public:
	OthelloBoard();
	QList< QList<OthelloItem*> > items;
	void clicked(int row, int column);
};


