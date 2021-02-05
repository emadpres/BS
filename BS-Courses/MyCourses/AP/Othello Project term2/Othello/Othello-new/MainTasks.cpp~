#include "BASICS.h"
#include "OurBasics.h"
#include <iostream>
using std::cout;

int OurPlayer::alphabeta(Position * position, int depth, int alpha, int beta)
{
	static int a =0;
	a++;
	cout << a << "\n";
	//cout << "start of alphabeta(" << "depth=" << depth << ")\n";
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	//if(checkwin(position)) 
		//return -INFINITY;

	if(depth == 0)	
		return evaluation(position);


	numberOfMoves = position->makeMoveList(list);
	if(numberOfMoves == 0) 
	{
		position->turn=!position->turn;
		numberOfMoves = position->makeMoveList(list);
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
		return -alphabeta(position,depth-1,-beta,-localalpha);
	}
	
	for(i=0; i<numberOfMoves; i++)
	{
		position->doMove(&list[i]);
		//cout << "calling alphabeta(" << "depth-1=" << depth -1 << ")\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		//cout << "returned from alphabeta(" << "depth-1=" << depth -1 << ")\n";
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
	
	for (unsigned int i = 0; i < GAMESIZE; i += 1)
	{
		for (unsigned int j = 0; j < GAMESIZE; j += 1)
		{
			//cout << position->board[i][j] << "  ";
		}
		//cout << "\n";
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
	//cout << "number of moves: " << numberOfMoves << "\n";
	for(i=0; i<numberOfMoves; i++)
	{
		//cout << "start of for i= " << i << "\n";
		position->doMove(&list[i]);
		//cout << "after do move" << "\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		//cout << "\n for x y : "<< list[i].x<<" " <<list[i].y <<" value = "<< value ; 
		//cout << "return from alphabeta depth" << depth -1 << "\n";
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
	////int dummy[]={23,45,2,3,44,53,67,56,78,7,5,43,-2,34,-4,-5,12};
	//static int counter = -1;
	//counter++;
	//if (counter >= 17 ) counter = 0;
	//return -dummy[counter];
	//return counter;
	int ourMovesCounter,opponentMovesCounter;
	int ourPotentialMobility, opponentPotentialMobility;
	int evaluation;
	int mobility;
	int potentialMobility;
	int corner=0;
	int adjacentCorner=0;
	
	if (position->board[0][0]==ourTurn)
		corner +=450;
	else 	if (position->board[0][0]==!ourTurn)
		corner-=450;
	else
	{
		for (int i = 0; i < 2; i += 1)
		{
			for (int j = 0; j < 2; j += 1)
			{
				if(i==0 && j==0 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=100;
				if(position->board[i][j]==!ourTurn)
					adjacentCorner+=100;
			}
		}
	} 
	
	if (position->board[0][GAMESIZE-1]==ourTurn)
		corner +=450;
	else 	if (position->board[0][GAMESIZE-1]==!ourTurn)
		corner-=450;
	else
	{
		for (int i = GAMESIZE-2; i < GAMESIZE; i += 1)
		{
			for (int j = 0; j < 2; j += 1)
			{
				if(i==GAMESIZE-1 && j==0 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=100;
				if(position->board[i][j]==!ourTurn)
					adjacentCorner+=100;
			}
		}
	}
	
	if (position->board[GAMESIZE-1][0]==ourTurn)
		corner +=450;
	else 	if (position->board[GAMESIZE-1][0]==!ourTurn)
		corner-=450;
	else
	{
		for (int i = 0; i <2; i += 1)
		{
			for (int j = GAMESIZE-2; j <  GAMESIZE; j += 1)
			{
				if(i==0 && j==GAMESIZE -1 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=100;
				if(position->board[i][j]==!ourTurn)
					adjacentCorner+=100;
			}
		}
	}
	
	if (position->board[GAMESIZE-1][GAMESIZE-1]==ourTurn)
		corner +=450;	
	else 	if (position->board[GAMESIZE-1][GAMESIZE-1]==!ourTurn)
		corner-=450;
	else
	{
		for (int i = GAMESIZE-2; i < GAMESIZE; i += 1)
		{
			for (int j = GAMESIZE-2; j < GAMESIZE; j += 1)
			{
				if(i==GAMESIZE-1 && j==GAMESIZE-1 )
					continue;
				if(position->board[i][j]==ourTurn)
					adjacentCorner-=100;
				if(position->board[i][j]==!ourTurn)
					adjacentCorner+=100;
			}
		}
	}
	
	MOVE list[MAXMOVES];
	position->makeMoveList(list, ourMovesCounter, opponentMovesCounter);
	position->potentialMobility(ourPotentialMobility, opponentPotentialMobility);
	
mobility=ourMovesCounter-opponentMovesCounter;
potentialMobility= ourPotentialMobility - opponentPotentialMobility;


	//cout <<"mobility: "<<mobility<<" potentialMobility: "<<potentialMobility<<" corner: " << corner<<" adjacentCorner: " << adjacentCorner << "\n";
	if (position->turn==ourTurn)
	{
		//mobility=ourMovesCounter-opponentMovesCounter;
		//potentialMobility= ourPotentialMobility - opponentPotentialMobility;
		return (evaluation = mobility + potentialMobility + corner + adjacentCorner);
	}
	else
	{
		//mobility=opponentMovesCounter - ourMovesCounter;
		//potentialMobility=opponentPotentialMobility - ourPotentialMobility;
		return -(evaluation = mobility + potentialMobility + corner + adjacentCorner);
	}
}
	
	/*MOVE list[MAXMOVES];
	position->makeMoveList(list, ourMovesCounter, opponentMovesCounter);
	position->potentialMobility(ourPotentialMobility, opponentPotentialMobility);
	

mobility=ourMovesCounter-opponentMovesCounter;
		potentialMobility= ourPotentialMobility - opponentPotentialMobility;
	//cout <<"mobility: "<<mobility<<" potentialMobility: "<<potentialMobility<<" corner: " << corner<<" adjacentCorner: " << adjacentCorner << "\n";
	if (position->turn==ourTurn)
	{
//		mobility=ourMovesCounter-opponentMovesCounter;
//		potentialMobility= ourPotentialMobility - opponentPotentialMobility;
		return -(evaluation = mobility + potentialMobility - corner - adjacentCorner);
	}
	else
	{
		//mobility=opponentMovesCounter - ourMovesCounter;
//		potentialMobility=opponentPotentialMobility - ourPotentialMobility;
		return evaluation = mobility + potentialMobility - corner - adjacentCorner;
	}
}*/
