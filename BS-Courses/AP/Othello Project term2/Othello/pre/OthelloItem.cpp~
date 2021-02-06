#include "OthelloItem.h"
#include "OthelloBoard.h"

#include "OthelloFunctions.cpp"

#define WHITE 1
#define BLACK 0
#define HOLE -1
#define EMPTY -2


OthelloItem::OthelloItem(OthelloBoard* parent,int row,int column):QGraphicsEllipseItem(column*ITEMW,row*ITEMW,ITEMW,ITEMW,parent)
{
	board = parent;
	this->row = row;
	this->column = column;
	setBrush(QBrush(QColor(Qt::red)));
	state=EMPTY;
}
void OthelloItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{	
//	board->clicked(row,column);
	if (state==HOLE)
	{
		int turn = Turn_Unit();
		for (int i=row-1; i<= row+1 ; i++)
			for (int j=column-1; j<=column+1; j++)
			{
				if ((i==row && j==column) || i>=GAMESIZE || j>=GAMESIZE || i<0 || j<0) 
					continue;
				if (board->items[i][j]->GetState() == (turn==BLACK?WHITE:BLACK))
					board->items[i][j]->FillThePath(row,column);

			}
		state = turn;
		if (turn == BLACK)
			setBrush(QBrush(QColor(Qt::black)));
		if (turn == WHITE)
			setBrush(QBrush(QColor(Qt::white)));	

		Turn_Unit(true);
		for(int i=0;i<GAMESIZE;i++)	
			for(int j=0;j<GAMESIZE;j++)	
				if(board->items[i][j]->GetState() == HOLE)
					board->items[i][j]->SetState(EMPTY);
		for(int i=0;i<GAMESIZE;i++)	
			for(int j=0;j<GAMESIZE;j++)
				board->items[i][j]->AmIAHole();	
	}
	else
	{
	}
}
void OthelloItem::AmIAHole()
{
	if (state==EMPTY)
	{
		int turn = Turn_Unit();
		for (int i=row-1; i<= row+1 ; i++)
			for (int j=column-1; j<=column+1; j++)
				{
					if ((i==row && j==column) || i>=GAMESIZE || j>=GAMESIZE || i<0 || j<0) 
						continue;
					if (board->items[i][j]->GetState() == (turn==BLACK?WHITE:BLACK))
						if (board->items[i][j]->IsAPath(row,column))
						{
							state = HOLE;
							setBrush(QBrush(QColor(Qt::blue)));
						}
							
				}
	}

}
bool OthelloItem::IsAPath(int preRow, int preColumn)
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
	
	int nextState = board->items[nextRow][nextColumn]->GetState();
	
	if (nextState==(state==BLACK?WHITE:BLACK))
		return true;
	if (nextState==state)
		return board->items[nextRow][nextColumn]->IsAPath(row,column);
	if (nextState==EMPTY)
		return false;

	return false;
}
bool OthelloItem::FillThePath(int preRow, int preColumn)
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
	
	int nextState = board->items[nextRow][nextColumn]->GetState();
	
	if (nextState==(state==BLACK?WHITE:BLACK) 
		||  ( (nextState==state) &&  board->items[nextRow][nextColumn]->FillThePath(row,column)))
	{
		int turn = Turn_Unit();
		state = turn;
		if (state == BLACK)
			setBrush(QBrush(QColor(Qt::black)));
		if (state == WHITE)
			setBrush(QBrush(QColor(Qt::white)));
		return true;
	}
	return false;

}	
int OthelloItem::GetState()
{
	return state;
}

void OthelloItem::SetState(int state)
{
	this->state=state;
	if (state == BLACK)
		setBrush(QBrush(QColor(Qt::black)));
	if (state == WHITE)
		setBrush(QBrush(QColor(Qt::white)));
	if (state == EMPTY)
		setBrush(QBrush(QColor(Qt::red)));		
	
}
