#ifndef __MAINTASKS_CPP
#define __MAINTASK_CPP

#define MAXMOVES 59
#define INFINITY 1000

#include "BASICS.h"
#include <iostream>
using std::cout;

bool OURTURN;

struct POSITION 
{	
	int board[GAMESIZE][GAMESIZE];
	bool turn;
};


struct MOVE
{
	int x, y;
	int capturedDiscs[8];
};

int makeMoveList(POSITION * position, MOVE list[])
{
	int moveCounter = 0;
	int m, n;
	int directionCounter=0;
	
	for (int x=0; x<GAMESIZE; x++)
		for (int y=0; y<GAMESIZE; y++)
		{
			if(position->board[x][y] == EMPTY)
			{
				directionCounter = 0;
				for (int i=-1; i<=1; i++)
					for (int j=-1; j<=1; j++)
					{		
						m=x+i;
						n=y+j;
						list[moveCounter].capturedDiscs[directionCounter]=0;
						if (i==0 && j==0)
							continue;
						if (m>=GAMESIZE ||n>=GAMESIZE || m<0 || n<0)						
						{
							directionCounter++;
							continue;		
						}
						while (position->board[m][n] == (position->turn==BLACK?WHITE:BLACK))
						{
				
							m+=i;	
							n+=j;
							if (m>=GAMESIZE ||n>=GAMESIZE || m<0 || n<0)
								break;
							if(position->board[m][n]==position->turn)
							{	
								// so This is Hole
								list[moveCounter].x=x;
								list[moveCounter].y=y;
									cout << "x=" << x << " y=" << y << "\n";
								if(i==0)
									list[moveCounter].capturedDiscs[directionCounter]=(((n-y)>0)?(n-y-1):(-(n-y)-1));
								else 
									list[moveCounter].capturedDiscs[directionCounter]=(((m-x)>0)?(m-x-1):(-(m-x)-1)); 
														
								
								//cout << x+1 << " "<< y+1 << "\n n";
							}
							
							cout <<"makeMoveList: number oof captured disk for X: "<< x <<" Y: " << y <<" and DIR: "<< directionCounter <<" => "<< list[moveCounter].capturedDiscs[directionCounter] << "\n";
						}//end of while
						directionCounter++;
					}
					if(list[moveCounter].x==x && list[moveCounter].y==y)
						moveCounter++; // for the next hole
			}

		}
	//cout << moveCounter << "\n";
	return moveCounter;
}

void doMove(POSITION * position, MOVE * move)
{
	int m, n;
	int directionCounter=0;
	position->board[move->x][move->y]=position->turn;
	for (int i=-1; i<=1; i++)
			for (int j=-1; j<=1; j++)
			{		
				if(i==0&&j==0)
					continue;
				m=move->x;
				n=move->y;
				cout <<"number of captured disk for X: "<< move->x <<" Y: " << move->y <<" and DIR: "<< directionCounter <<" => " <<move->capturedDiscs[directionCounter] << "\n";
				for (int k=0;k<move->capturedDiscs[directionCounter];k++)
				{

					m+=i;	
					n+=j;
					//cout << "m = " << m << " n = " << n << "\n";
					position->board[m][n]=position->turn;
				}
				directionCounter++;
			}
	position->turn=!position->turn;
}

void undoMove(POSITION * position, MOVE * move)
{
	int m,n;
	int directionCounter=0;
	position->board[move->x][move->y]=EMPTY;
	for (int i=-1; i<=1; i++)
			for (int j=-1; j<=1; j++)
			{		
				if(i==0&&j==0)
					continue;
				m=move->x;
				n=move->y;
				for (int k=0;k<move->capturedDiscs[directionCounter];k++)
				{
					m+=i;	
					n+=j;
					position->board[m][n]=position->turn;
				}
				directionCounter++;
			}
	position->turn=!position->turn;
}

int evaluation(POSITION * position)
{
	////int dummy[]={23,45,2,3,44,53,67,56,78,7,5,43,-2,34,-4,-5,12};
	//static int counter = -1;
	//counter++;
	//if (counter >= 17 ) counter = 0;
	//return -dummy[counter];
	//return counter;
	MOVE list[MAXMOVES];
	int evaluation;
	int numberOfMoves;
	numberOfMoves = makeMoveList(position,list);
	if (position->turn==OURTURN)
		evaluation = numberOfMoves;
	else
		evaluation = -numberOfMoves;
	
	return -evaluation;
}

int alphabeta(POSITION * position, int depth, int alpha, int beta)
{
	cout << "start of alphabeta(" << "depth=" << depth << ")\n";
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	//if(checkwin(position)) 
		//return -INFINITY;

	if(depth == 0)	
		return evaluation(position);


	numberOfMoves = makeMoveList(position,list);
	if(numberOfMoves == 0) 
	{
		position->turn=!position->turn;
		numberOfMoves = makeMoveList(position,list);
		if (numberOfMoves==0)
		{
			int whiteScore=0;
			int blackScore=0;
			for (int i=0; i<GAMESIZE; i++)
				for (int j=0; j<GAMESIZE; j++)
				{
					if (position->board[i][j] == WHITE)
						whiteScore++;
					else if (position->board[i][j] == BLACK)
						blackScore++;
				}
			if (whiteScore>blackScore)
			{
				if (position->turn==WHITE)
					return INFINITY;
				else
					return -INFINITY;
				
			}
			else if (blackScore>whiteScore)
			{
				if (position->turn==WHITE)
					return -INFINITY;
				else
					return INFINITY;
			}
			else 
			{
				//Do Something Guys!
			}
		}
	}
	
	for(i=0; i<numberOfMoves; i++)
		{
		doMove(position, &list[i]);
		cout << "calling alphabeta(" << "depth-1=" << depth -1 << ")\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		cout << "returned from alphabeta(" << "depth-1=" << depth -1 << ")\n";
		undoMove(position, &list[i]);
		bestvalue = (value>bestvalue)?value:bestvalue;
		if(bestvalue>=beta) 
			break;
		if(bestvalue>localalpha) 
			localalpha=bestvalue;
		}
	return bestvalue;
}

MOVE firstAlphabeta(POSITION * position, int depth, int alpha, int beta)
{
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	//if(checkwin(position)) 
		//return -INFINITY;

	numberOfMoves = makeMoveList(position,list);
	for (int i=0; i<numberOfMoves;i++)
		cout << list[i].x << "  "<< list[i].y<< "\n";
	//cout << numberOfMoves;
	
	for (unsigned int i = 0; i < GAMESIZE; i += 1)
	{
		for (unsigned int j = 0; j < GAMESIZE; j += 1)
		{
			cout << position->board[i][j] << "  ";
		}
		cout << "\n";
	}	

	//if(numberOfMoves == 0) 
	//{
		//Here doesn't happen also
//		if (numberOfMoves==0)
	//	{
		// We Have NO movement and never come here !!
		
			/*int whiteScore=0;
			int blackScore=0;
			for (int i=0; i<GAMESIZE; i++)
				for (int j=0; j<GAMESIZE; j++)
				{
					if (position.board[i][j] == WHITE)
						whiteScore++;
					else if (posion.board[i][j] == BLACK)
						blackScore++;
				}
			if (whiteScore>blackScore)
			{
				if (position->turn==WHITE)
					return INFINITY;
				else
					return -INFINITY;
				
			}
			else if (blackScore>whiteScore)
			{
				if (position->turn==WHITE)
					return -INFINITY;
				else
					return INFINITY;
			}
			else 
			{
				//Do Something Guys!
			}*/
		//}
//	}

	int bestMoveIndex=0;
	cout << "number of moves: " << numberOfMoves << "\n";
	for(i=0; i<numberOfMoves; i++)
	{
		cout << "start of for i= " << i << "\n";
		doMove(position, &list[i]);
		cout << "after do move" << "\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		cout << "return from alphabeta depth" << depth -1 << "\n";
		undoMove(position, &list[i]);
		cout << "after undo move\n";
		if (value > bestvalue)
		{
			bestvalue = value;
			bestMoveIndex = i;
		}
		if(bestvalue>=beta) 
			break;
		if(bestvalue>localalpha) 
			localalpha=bestvalue;
	}
	
	//MOVE a;
	//cout << list[bestMoveIndex].x << list[bestMoveIndex].y << "\n";
	//a.x = 2;
	//a.y = 4;
//	return a;

	
	//return 
	return list[bestMoveIndex];
}


/*int main()
{
	POSITION p;
	p.turn= BLACK;
	for (int i=0; i<GAMESIZE; i++)
		for (int j=0; j<GAMESIZE; j++)
		{
			p.board[i][j] = EMPTY;
		}
	p.board[4][4] = p.board[3][3] = WHITE;
	p.board[4][3] = p.board[3][4] = BLACK;
	MOVE list[MAXMOVES];
	
	//makeMoveList(&p, list);
	//doMove(&p, &list[0]);
//	undoMove(&p, &list[0]);
	//cout << "\numberOfMoves";
	//makeMoveList(&p, list);
	
	//for (int i=0; i< 21; i++)
		//cout << evaluation(&p) << "\numberOfMoves";
	MOVE bestMove;
	bestMove=firstAlphabeta(&p,4, -INFINITY, +INFINITY);
	cout << bestMove.x+1 << " " << bestMove.y+1<< "\n";
	doMove(&p, &bestMove);
	bestMove=firstAlphabeta(&p,4, -INFINITY, +INFINITY);
	cout << bestMove.x+1 << " " << bestMove.y+1<< "\n";
	//makeMoveList(&p, list);
}*/

#endif
