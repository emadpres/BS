#ifndef __OTHELLOITEM_H__
#define __OTHELLOITEM_H__

#include <QGraphicsEllipseItem>
#include "OthelloBoard.h"
#include "BASICS.h"

class OthelloBoard;

class OthelloItem: public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
	friend class OthelloBoard;

	public:
		OthelloItem(OthelloBoard * board, int row, int column);
	private:
		void initializeStar();
		void initializeCircle();
		void changeTo(int turn);
		void paintEmpty();
	
		OthelloBoard * board;
		int row;
		int column;
		STATE state;

		QGraphicsPolygonItem * starPolygon;
		QGraphicsPolygonItem * tenPolygon;
		QGraphicsEllipseItem * circle;

		void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	private slots:
		void paintWhite();
		void paintBlack();
		void paintHole();
};

#endif
