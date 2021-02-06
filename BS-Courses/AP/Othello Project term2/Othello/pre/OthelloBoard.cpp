#include "OthelloBoard.h"
#include "OthelloItem.h"

#define WHITE 1
#define BLACK 0

OthelloBoard::OthelloBoard():QGraphicsRectItem(){}
void OthelloBoard::clicked(int row, int column)
{
	
}
void OthelloBoard::Initialize()
{
	items[3][3]-> SetState(WHITE);
	items[4][4]-> SetState(WHITE);
	items[3][4]-> SetState(BLACK);
	items[4][3]-> SetState(BLACK);
	
	for(int i=0;i<GAMESIZE;i++)	
		for(int j=0;j<GAMESIZE;j++)
			items[i][j]->AmIAHole();
	
}
