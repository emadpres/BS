#include "OthelloItem.h"
#include "Othelloboard.h"
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

OthelloItem::OthelloItem(OthelloBoard* parent,int row,int column):QGraphicsEllipseItem(column*ITEMW,row*ITEMW,ITEMW,ITEMW,parent)
{
			board = parent;
			this->row = row;
			this->column = column;
			setBrush(QBrush(QColor(Qt::red)));
			state= EMPTY;
}

void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ){
		holeUnit(row,column,board);
		
	}

 void OthelloItem::Turn_Unit()
{
              if (board->turn==BLACK)
                      board->turn = WHITE;
          else
                  board->turn = BLACK;     
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
			if(board->items[m][h]->state==EMPTY)
			{
				for(int i=-1;i<2;++i)

					for(int j=-1;j<2;++j)
					{
						
						if(board->items[m+i][h+j]->state!=turn)
						{
							bool applay=true;
							while(applay!=false)
							{
							
								if(((m+i)>7)||((h+j)>7)||((m+i)<0)||((h+j)<0))
								{
									applay=true;
									break;
								}
								if(board->items[m+i][h+j]->state==EMPTY)
								{
									applay=true;
									break;
								}
								
								if(board->items[m+i][h+j]->state==turn)
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
				cout<<"WHITE is winner";   //inja ro mikhastam label konam nashod.agar zahmati nist baram dorostesh konin.merC
			if(whiteScore<=blackScore)
				cout<<"BLACK is winner";
		}
}





int OthelloItem::holeUnit(int x,int y,OthelloBoard* parent)
{
	if (board->items[x][y]->state!=EMPTY)
		return false;
	for(int i=-1;i<2;++i)

		for(int j=-1;j<2;++j)
		{
			if(board->items[x+i][y+j]->state!=board->turn)
			{
				if (canUnit(x,y,i,j,board->turn,board,true))				
				{
					//if (board->turn==WHITE)
					//{
						setBrush(QBrush(QColor(Qt::white)));
						setState(WHITE);
					//}
					if (board->turn==BLACK)
					{
						setBrush(QBrush(QColor(Qt::black)));
						setState(BLACK);
					}
				}
			}
		}

}

bool OthelloItem::canUnit(int x,int y,int i,int j,int turn,OthelloBoard* parent,bool applay=true)
{
	
	int m=y;
	int l=x;

			do
			{

				l+=i;
				m+=j;				
				if((l>7)||(m>7)||(l<0)||(m<0))
				{
					applay=true;
					break;
				}
				if(board->items[l][m]->state==EMPTY)
				{
					applay=true;
					break;
				}
				

				if(board->items[l][m]->state==turn)
				{	applay=false;
					break;
				}

			}while(board->items[l][m]->state==(turn==BLACK?WHITE:BLACK));

			while(!((l=x)&&(m=y)))
			{
				if (turn==WHITE)
				{
					board->items[l][m]->setBrush(QBrush(QColor(Qt::white)));
					board->items[l][m]->setState(WHITE);
				}
				if (turn==BLACK)
				{
					board->items[l][m]->setBrush(QBrush(QColor(Qt::black)));
					board->items[l][m]->setState(BLACK);
				}
				l-=i;
				m-=j;
			}
		    board->blackmark->setPlainText("Black:"+QString::number(turn));
		    //board->blackmark->setPlainText("Black:"+QString::number(blackScore));


			Turn_Unit();
			int whiteScore;
			int blackScore;
			for(int r=0;r<8;++r)
				for(int t=0;t<8;++t)
				{
					if(board->items[r][t]->state==WHITE)
						whiteScore++;
					if(board->items[r][t]->state==BLACK)
						blackScore++;
				}
				
			
			board->whitemark->setPlainText("White:"+QString::number(whiteScore));//bara label injuri neveshtam:
																	 //Label *label1,*label2;
																	 //label1->setText(whiteScore);
																	 //label2->setText(blackScore);
																	 //error dad.ino neveshtam inam error mide:(
 
		    board->blackmark->setPlainText("Black:"+QString::number(blackScore));
			checkUnit(turn,whiteScore,blackScore,parent);
		
 return true;	
	
return false;
}
