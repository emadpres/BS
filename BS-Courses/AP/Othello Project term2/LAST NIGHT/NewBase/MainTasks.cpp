#include "mbasics.h"
#include "OurBasics.h"
#include <iostream>
#include <fstream>

using std::cout;
std::ofstream LOG("Log.log");

void showBoard(Position * position)
{
	for(int i=0;i<GAMESIZE;i++)
	{
		for(int j=0;j<GAMESIZE;j++)
		{
			cout<<position->board[i][j];
		}
	cout<<"\n";
	}
}
int OurPlayer::alphabeta(Position * position, int depth, int alpha, int beta)
{
	//LOG << "Entering - Depth: " << depth << endl;
	//static int a =0;
	//a++;
	//cout << "a:" << a << "\n";
	//cout << "depth: " << depth << "\n";
	
	//cout << "start of alphabeta(" << "depth=" << depth << ")\n";
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	//if(checkwin(position)) 
		//return -INFINITY;

	if(depth == 0)	
		{
		int EAeval=evaluation(position);
		showBoard(position);
		cout<<"Depth : "<<depth<<" return evaluation by value : "<<EAeval<<"\n";
		return EAeval;
		}


	numberOfMoves = position->makeMoveList(list);
	if(numberOfMoves == 0) 
	{
	
		position->turn=(position->turn==BLACK?WHITE:BLACK);			// change Turn
		numberOfMoves = position->makeMoveList(list);
		if (numberOfMoves==0)
		{
	//	LOG << "number of moves =0\n";
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
		//		LOG << "DO some Thing guys\n";
			}
		}
	//	LOG << "Exiting - Depth: " << depth << endl;
		return -alphabeta(position,depth-1,-beta,-localalpha);
	}
	
	for(i=0; i<numberOfMoves; i++)
	{
		//cout << "Going for do move depth: " << depth << "\n";
		position->doMove(&list[i]);
		//cout << "calling alphabeta(" << "depth-1=" << depth -1 << ")\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		//cout << "returned from alphabeta(" << "depth-1=" << depth -1 << ")\n";
		//cout << "Going for undo move depth: " << depth << "\n";
		position->undoMove(&list[i]);
		bestvalue = (value>bestvalue)?value:bestvalue;
		if(bestvalue>=beta) 
			break;
		if(bestvalue>localalpha) 
			localalpha=bestvalue;
	}
	return bestvalue;
}

MOVE OurPlayer::firstAlphabeta(Position * position, int depth, int alpha, int beta)
{
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	//if(checkwin(position)) 
		//return -INFINITY;

	numberOfMoves = position->makeMoveList(list);

	//for (int i=0; i<numberOfMoves;i++)
		//cout << list[i].x << "  "<< list[i].y<< "\n";
	////cout << numberOfMoves;
	

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
	//cout << "number of moves: " << numberOfMoves << "\n";
	for(i=0; i<numberOfMoves; i++)
	{
		//cout << "start of for i= " << i << "\n";
		//cout << "Going for do move depth: " << depth << "\n";
		position->doMove(&list[i]);
		//cout << "after do move" << "\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		//cout << "\n for x y : "<< list[i].x<<" " <<list[i].y <<" value = "<< value ; 
		//cout << "return from alphabeta depth" << depth -1 << "\n";
		//cout << "Going for undoMove depth: " << depth << "\n";
		position->undoMove(&list[i]);
		//cout << "after undo move\n";
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
	////cout << list[bestMoveIndex].x << list[bestMoveIndex].y << "\n";
	//a.x = 2;
	//a.y = 4;
//	return a;

	
	//return 
	//cout<<"\n Best move Index is : "<< bestMoveIndex ;
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
	////cout << "\numberOfMoves";
	//makeMoveList(&p, list);
	
	//for (int i=0; i< 21; i++)
		////cout << evaluation(&p) << "\numberOfMoves";
	MOVE bestMove;
	bestMove=firstAlphabeta(&p,4, -INFINITY, +INFINITY);
	//cout << bestMove.x+1 << " " << bestMove.y+1<< "\n";
	doMove(&p, &bestMove);
	bestMove=firstAlphabeta(&p,4, -INFINITY, +INFINITY);
	//cout << bestMove.x+1 << " " << bestMove.y+1<< "\n";
	//makeMoveList(&p, list);
}*/

int OurPlayer::evaluation(Position * position)
{
	int ourMovesCounter=0,opponentMovesCounter=0;
	int ourPotentialMobility=0, opponentPotentialMobility=0;
	int evaluation=0;
	int mobility=0;
	int potentialMobility=0;
	int corner=0;
	int adjacentCorner=0;
	int stable=0;
	
	if (position->board[0][0]==ourTurn)
		corner +=1000;
	else 	if (position->board[0][0]==(ourTurn==BLACK?WHITE:BLACK))
		corner-=1000;
	else
	{
		for (int i = 0; i < 2; i += 1)
		{
			for (int j = 0; j < 2; j += 1)
			{
				if(i==0 && j==0 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=550;
				if(position->board[i][j]==((ourTurn==BLACK)?WHITE:BLACK))
					adjacentCorner+=550;
			}
		}
	} 
	
	if (position->board[0][GAMESIZE-1]==ourTurn)
		corner +=1000;
	else 	if (position->board[0][GAMESIZE-1]==(ourTurn==BLACK?WHITE:BLACK))
		corner-=1000;
	else
	{
		for (int i = 0; i < 2; i += 1)
		{
			for (int j = GAMESIZE-2; j < GAMESIZE; j += 1)
			{
				if(i==0 && j==GAMESIZE-1 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=550;
				if(position->board[i][j]==(ourTurn==BLACK?WHITE:BLACK))
					adjacentCorner+=550;
			}
		}
	}
	
	if (position->board[GAMESIZE-1][0]==ourTurn)
		corner +=1000;
	else 	if (position->board[GAMESIZE-1][0]==(ourTurn==BLACK?WHITE:BLACK))
		corner-=1000;
	else
	{
		for (int j = 0; j <2; j += 1)
		{
			for (int i = GAMESIZE-2; i <  GAMESIZE; i += 1)
			{
				if(i==GAMESIZE-1 && j==0 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=550;
				if(position->board[i][j]==(ourTurn==BLACK?WHITE:BLACK))
					adjacentCorner+=550;
			}
		}
	}
	
	if (position->board[GAMESIZE-1][GAMESIZE-1]==ourTurn)
		corner +=1000;
	else 	if (position->board[GAMESIZE-1][GAMESIZE-1]==(ourTurn==BLACK?WHITE:BLACK))
		corner-=1000;
	else
	{
		for (int i = GAMESIZE-2; i < GAMESIZE; i += 1)
		{
			for (int j = GAMESIZE-2; j < GAMESIZE; j += 1)
			{
				if(i==GAMESIZE-1 && j==GAMESIZE-1 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=550;
				if(position->board[i][j]==(ourTurn==BLACK?WHITE:BLACK))
					adjacentCorner+=550;
			}
		}
	}
	
	MOVE list[MAXMOVES];
	position->makeMoveList(list, ourMovesCounter, opponentMovesCounter);
	position->potentialMobility(ourPotentialMobility, opponentPotentialMobility);
	
	mobility=ourMovesCounter-opponentMovesCounter;
	potentialMobility= ourPotentialMobility - opponentPotentialMobility;
	
	int around=0;
	for(int i=2; i<GAMESIZE-2; i++)
	{
		if (position->board[0][i]==ourTurn)
			around+=20;
		if (position->board[7][i]==ourTurn)
			around+=20;
		if (position->board[i][0]==ourTurn)
			around+=20;
		if (position->board[i][7]==ourTurn)
			around+=20;
	}

	evaluation = mobility + potentialMobility + corner + adjacentCorner + around;

	
		if(position->remainingMoves<=12)
	{
		if(turn==ourTurn)
			evaluation*=(position->whiteScore/position->blackScore);
		else
			evaluation*=(position->blackScore/position->whiteScore);
			
	}
	if (position->turn==ourTurn)
	{
		return -evaluation;
	}
	else
	{
		return evaluation;
	}
}
	
	
