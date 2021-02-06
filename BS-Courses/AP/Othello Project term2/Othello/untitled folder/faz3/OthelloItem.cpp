#include "OthelloItem.h"
#include "othelloboard.h"
#include <QtGui/QApplication>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <iostream>
using namespace std;
#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define HOLE -1

OthelloItem::OthelloItem(OthelloBoard* parent,int row,int column):QGraphicsEllipseItem(column*ITEMW,row*ITEMW,ITEMW,ITEMW,parent)
{
			board = parent;
			this->row = row;
			this->column = column;
			setBrush(QBrush(QColor(Qt::red)));
			state=EMPTY;
		
}

void OthelloItem::Turn_Unit()
{
	 if(board->turn==WHITE)
		board->turn = BLACK;
	else if(board->turn==BLACK)
		board->turn= WHITE;

}
void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event)

	{if (state==HOLE)
	{
		int turn = board->turn;
		for (int i=row-1; i<= row+1 ; i++)
			for (int j=column-1; j<=column+1; j++)
			{
				if ((i==row && j==column) || i>=GAMESIZE || j>=GAMESIZE || i<0 || j<0) 
					continue;
				if (board->items[i][j]->getState() == (turn==BLACK?WHITE:BLACK))
					board->items[i][j]->colorUnit(row,column);

			}
		state = turn;
		if (turn == BLACK)
			setBrush(QBrush(QColor(Qt::black)));
		if (turn == WHITE)
			setBrush(QBrush(QColor(Qt::white)));	

		Turn_Unit();
		for(int i=0;i<GAMESIZE;i++)	
			for(int j=0;j<GAMESIZE;j++)	
				if(board->items[i][j]->getState() == HOLE)
					{
					board->items[i][j]->setState(EMPTY);
					board->items[i][j]->setBrush(QBrush(QColor(Qt::red)));
					}
		for(int i=0;i<GAMESIZE;i++)	
			for(int j=0;j<GAMESIZE;j++)
				board->items[i][j]->holeUnit();	
	}
					
	}

 

void OthelloItem::setState(int turn)
{
	state=turn;	

}
int OthelloItem::getState()
{
	return state;
}

/****/


void OthelloItem::checkUnit(int turn,int whiteScore,int blackScore,OthelloBoard* parent)
{
	int e=0;
	for(int m=0;m<8;++m)
		for(int h=0;h<8;++h)
		{
			
			if(parent->items[m][h]->getState()==EMPTY)
			{
				for(int i=-1;i<2;++i)

					for(int j=-1;j<2;++j)
					{
						
						if(parent->items[m+i][h+j]->getState()!=turn)
						{
							bool applay=true;
							while(applay!=false)
							{
							
								if(((m+i)>7)||((h+j)>7)||((m+i)<0)||((h+j)<0))
								{
									applay=true;
									break;
								}
								
								if(parent->items[m+i][h+j]->getState()==EMPTY)
								{
									applay=true;
									break;
								}
								
								if(parent->items[m+i][h+j]->getState()==turn)
								{
									applay=false;
									e++;
								}
							}
						}
					}
						
							
						
					
			}
		}
		if (e==0)
		{
			if(whiteScore>=blackScore)
				cout<<"WHITE is winner";  
			if(whiteScore<=blackScore)
				cout<<"BLACK is winner";
		}
}





void OthelloItem::holeUnit()
{
	if (state==EMPTY)
	{
		int turn = board->turn;
		for (int i=row-1; i<= row+1 ; i++)
			for (int j=column-1; j<=column+1; j++)
				{
					if ((i==row && j==column) || i>=GAMESIZE || j>=GAMESIZE || i<0 || j<0) 
						continue;
					if (board->items[i][j]->getState() == (turn==BLACK?WHITE:BLACK))
						if (board->items[i][j]->canUnit(row,column))
						{
							state = HOLE;
							setBrush(QBrush(QColor(Qt::blue)));
						}
							
				}
	}

}
bool OthelloItem::canUnit(int preRow, int preColumn)
{
	int nextRow= row;
	int nextColumn = column;
	
	if (row > preRow)
		nextRow++;
	if (column > preColumn)
		nextColumn++;
	if (row < preRow)
		nextRow--;
	if (column < preColumn)
		nextColumn--;
	
	if (nextColumn >= GAMESIZE || nextRow >= GAMESIZE || nextColumn <0 || nextRow <0)
		return false;
	
	int nextState = board->items[nextRow][nextColumn]->getState();
	
	if (nextState==(state==BLACK?WHITE:BLACK))
		return true;
	if (nextState==state)
		return board->items[nextRow][nextColumn]->canUnit(row,column);
	if (nextState==EMPTY)
		return false;

	return false;
}
bool OthelloItem::colorUnit(int preRow, int preColumn)
{
	int nextRow= row;
	int nextColumn = column;
	
	if (row > preRow)
		nextRow++;
	if (column > preColumn)
		nextColumn++;
	if (row < preRow)
		nextRow--;
	if (column < preColumn)
		nextColumn--;
	
	if (nextColumn >= GAMESIZE || nextRow >= GAMESIZE || nextColumn <0 || nextRow <0)
		return false;
	
	int nextState = board->items[nextRow][nextColumn]->getState();
	
	if (nextState==(state==BLACK?WHITE:BLACK) 
		||  ( (nextState==state) &&  board->items[nextRow][nextColumn]->colorUnit(row,column)))
	{
		int turn = board->turn;
		state = turn;
		if (state == BLACK)
			setBrush(QBrush(QColor(Qt::black)));
		if (state == WHITE)
			setBrush(QBrush(QColor(Qt::white)));
		return true;
	}
	return false;


			//Turn_Unit();
			int whiteScore;
			int blackScore;
			for(int r=0;r<8;++r)
				for(int t=0;t<8;++t)
				{
					if(board->items[r][t]->getState()==WHITE)
						whiteScore++;
					if(board->items[r][t]->getState()==BLACK)
						blackScore++;
				}
				
	
			//checkUnit(turn,whiteScore,blackScore,parent);	
	
}
