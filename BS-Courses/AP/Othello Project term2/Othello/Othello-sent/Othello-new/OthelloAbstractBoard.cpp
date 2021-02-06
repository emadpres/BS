#include <iostream>
using std::cout;

#include "OthelloAbstractBoard.h"
OthelloAbstractBoard::OthelloAbstractBoard()
{

}
		
void OthelloAbstractBoard::createHoles(STATE currentTurn)
{
	clearLastHoles();
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			IsHole(i,j,currentTurn);
}

void OthelloAbstractBoard::clearLastHoles()
{
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			if (items[i][j]==HOLE)
					items[i][j]=EMPTY;
}

BOARD OthelloAbstractBoard::getItems()
{
	return items;
}

void OthelloAbstractBoard::IsHole(int x, int y, STATE currentTurn)
{
	if (items[x][y]==EMPTY)
	{
		for (int i=-1;i<=1;i++)
			for (int j=-1;j<=1; j++)
			{
				if ((i==0 && j==0) || x+i>=GAMESIZE || y+j>=GAMESIZE || x+i<0 || y+j<0) 
					continue;
				if (items[x+i][y+j] == (currentTurn==BLACK?WHITE:BLACK))
					if (checkPath(x+i,y+j,i,j,currentTurn))
						items[x][y] = HOLE; 
			}
	}
}

bool OthelloAbstractBoard::noMove()
{
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
			if (items[i][j] == HOLE)
				return false;
	return true;
}

bool OthelloAbstractBoard::canPlay(int x, int y)
{	
	if (items[x][y] == HOLE)
		return true;
	return false;
}

bool OthelloAbstractBoard::checkPath(int x, int y, int i, int j, STATE currentTurn, bool apply)
{
	if (x + i >= GAMESIZE || y + j >= GAMESIZE || y + j <0 || x + i <0)
		return false;
	
	STATE nextState = items[x+i][y+j];
	
	if (nextState==EMPTY)
		return false;	

	if (nextState==(currentTurn==BLACK?BLACK:WHITE) ||
		((nextState==items[x][y]) && checkPath(x+i,y+j,i,j, currentTurn,apply)))
	{
		if (apply == true)
			items[x][y] = currentTurn;
		return true;
	}
	return false;
}

void OthelloAbstractBoard::play(int x, int y, STATE currentTurn)
{
	if (items[x][y] == HOLE)
	{	
		items[x][y] = currentTurn;

		for (int i=-1;i<=1;i++)
			for (int j=-1;j<=1; j++)
			{
				if ((i==0 && j==0) || x+i>=GAMESIZE || y+j>=GAMESIZE || x+i<0 || y+j<0) 
					continue;
				if (items[x+i][y+j] == (currentTurn==BLACK?WHITE:BLACK))
						checkPath(x+i,y+j,i,j,currentTurn,true);
			}
	}
	else
	{
		//announcer -> announce invalid move (just a message in the status bar)
		//under construction
	}
}

int OthelloAbstractBoard::scoreUnit(STATE turn)
{
	int score =0;
	for(int i=0; i<GAMESIZE; i++)
		for(int j=0; j<GAMESIZE; j++)
		{
			if (items[i][j] == turn)
				score++;
		}
	return score;
}

STATE OthelloAbstractBoard::winner()
{
		int whiteScore = scoreUnit(WHITE);	
		int blackScore = scoreUnit(BLACK);
		
		if (whiteScore > blackScore)
			return WHITE;
		else if (whiteScore < blackScore)
			return BLACK;
		else // (whiteScore == blackScore)
			return EMPTY;
}
