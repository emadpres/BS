#ifndef __OTHELLOBOARD_H__
#define __OTHELLOBOARD_H__

#include <QGraphicsRectItem>
#include <QTimer>

#include "OthelloItem.h"
#include "OthelloAbstractBoard.h"
#include "OthelloController.h"

class OthelloItem;
class OthelloController;
class OthelloAbstractBoard;

class OthelloBoard: public QObject, public QGraphicsRectItem  
{
	Q_OBJECT	
	friend class OthelloItem;
	friend class OthelloController;
	
	public:
		OthelloBoard(OthelloController * controller);
		OthelloAbstractBoard getState();
			
	private:
		QList< QList<OthelloItem*> > items;

		void setState(OthelloAbstractBoard abstractBoard, STATE currentTurn);
			
		int delayDuration;

		STATE currentTurn;
		STATE humanTurn;
		
		OthelloController * controller;
};

#endif
