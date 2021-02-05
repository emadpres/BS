#ifndef __OTHELLOBOARD_H__
#define __OTHELLOBOARD_H__

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPaintEvent>
#include <QLabel>
#include "OthelloItem.h"

#define GAMESIZE 8
#define ITEM_WIDTH 80

enum state {EMPTY =-2, HOLE, BLACK, WHITE};

class OthelloItem;

class OthelloBoard: public QGraphicsRectItem
{
	friend class OthelloItem;
	public:
		OthelloBoard(QLabel * scoreLabel, QLabel * turnLabel);

	private:
		void initializeGame();
		int currentTurn; 
		void changeTurn();
		QList< QList<OthelloItem*> > items;
		void findHoles();
		void clearLastHoles();
		
		void showScore();
		int scoreUnit(int turn);
		QLabel * scoreLabel;

		QLabel * turnLabel;
		void showTurn();
		bool noMove();
};

#endif
