#include "OthelloBoard.h"

#include <QGraphicsEllipseItem>

OthelloBoard::OthelloBoard(OthelloController * controller):QGraphicsRectItem()
{
	this->controller = controller;
	
	setRect(0,0,GAMESIZE * ITEM_WIDTH,GAMESIZE * ITEM_WIDTH);
	setBrush(QBrush(QColor::fromRgb(52,101,164)));

	for(int i=0; i<GAMESIZE; i++)
	{
		items.append( QList<OthelloItem*> ());
		for (int j=0; j<GAMESIZE; j++)
			items[i].append(new OthelloItem(this, i, j));
	}

	delayDuration = 0;
}

OthelloAbstractBoard OthelloBoard::getState()
{
	OthelloAbstractBoard currentBoard;
	
		for(int i=0; i<GAMESIZE; i++)
		{
			currentBoard.items.append(QList< STATE >());
			for(int j=0; j<GAMESIZE; j++)
				currentBoard.items[i].append(items[i][j]->state);
		}	
			
	return currentBoard;
}

void OthelloBoard::setState(OthelloAbstractBoard abstractBoard, STATE currentTurn)
{
		this->currentTurn = currentTurn;
		for(int i=0; i<GAMESIZE; i++)
			for(int j=0; j<GAMESIZE; j++)
			{
				if (items[i][j]->state==HOLE)
						items[i][j]->changeTo(EMPTY);
		
				if (items[i][j]->state!=abstractBoard.items[i][j])
				{
					if (abstractBoard.items[i][j]!=HOLE) //we paint the holes after all
						items[i][j]->changeTo(abstractBoard.items[i][j]);
						
					if (abstractBoard.items[i][j]==BLACK || abstractBoard.items[i][j]==WHITE)
							delayDuration+=80;
				}
			}		
		for(int i=0; i<GAMESIZE; i++)
			for(int j=0; j<GAMESIZE; j++)
				{ //painting the holes now that we have the delayDuration
					if (abstractBoard.items[i][j]==HOLE)
						items[i][j]->changeTo(abstractBoard.items[i][j]);
				}
}
