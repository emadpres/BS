#ifndef __OTHELLOITEM_H__
#define __OTHELLOITEM_H__


#include <QGraphicsEllipseItem>
#include "OthelloBoard.h"

class OthelloBoard;

class OthelloItem: public QGraphicsEllipseItem
{
	friend class OthelloBoard;

	public:
		OthelloItem(OthelloBoard * board, int row, int column);
	private:
		void initializeStar();
		void initializeCircle();
		void changeTo(int turn);
		void paintEmpty();
		void paintWhite();
		void paintBlack();	

		OthelloBoard * board;
		int row;
		int column;
		int state;

		QGraphicsPolygonItem * polygon;
		QGraphicsEllipseItem * circle;

		void IsAHole();
		void play();
		bool IsAPath(int i, int j, bool play = false);

		void mousePressEvent ( QGraphicsSceneMouseEvent * event );
};

#endif
