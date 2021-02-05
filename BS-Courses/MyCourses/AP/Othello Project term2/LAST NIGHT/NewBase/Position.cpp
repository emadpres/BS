#include "Position.h"

#include <iostream>
using std::cout;

#include <ctime>
#include <cstdlib>
using std::rand;
using std::time;
using std::srand;

Position::Position(bool ourTurn)
{

	remainingMoves=60;
	blackScore=whiteScore=2;
	srand(time(0));
	for (int i=0; i<GAMESIZE; i++)
		for (int j=0; j<GAMESIZE; j++)
		{
			board[i][j] = EMPTY;
		}
	
	turn=ourTurn;
	
	for (int i=0; i<GAMESIZE; i++)
		for (int j=0; j<GAMESIZE; j++)
			for (int k=0; k<2; k++)
			{
				hashNumbers[i][j][k]=rand();
			}
}

int Position::makeMoveList(MOVE list[])
{
	int moveCounter = 0;
	int m, n;
	int directionCounter=0;
	
	for (int x=0; x<GAMESIZE; x++)
		for (int y=0; y<GAMESIZE; y++)
		{
			if(board[x][y] == EMPTY)
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
						while (board[m][n] == ((turn==BLACK)?WHITE:BLACK))
						{
				
							m+=i;	
							n+=j;
							if (m>=GAMESIZE ||n>=GAMESIZE || m<0 || n<0)
								break;
							if(board[m][n]==turn)
							{	
								// so This is Hole
								list[moveCounter].x=x;
								list[moveCounter].y=y;
									//cout << "x=" << x << " y=" << y << "\n";
								if(i==0)
									list[moveCounter].capturedDiscs[directionCounter]=(((n-y)>0)?(n-y-1):(-(n-y)-1));
								else 
									list[moveCounter].capturedDiscs[directionCounter]=(((m-x)>0)?(m-x-1):(-(m-x)-1)); 
														
								
								////cout << x+1 << " "<< y+1 << "\n n";
							}
							
							//cout <<"makeMoveList: number oof captured disk for X: "<< x <<" Y: " << y <<" and DIR: "<< directionCounter <<" => "<< list[moveCounter].capturedDiscs[directionCounter] << "\n";
						}//end of while
						directionCounter++;
					}
					if(list[moveCounter].x==x && list[moveCounter].y==y)
						moveCounter++; // for the next hole
			}

		}
	////cout << moveCounter << "\n";
	return moveCounter;
}

void Position::makeMoveList(MOVE list[], int & moveCounter,int & opponentMoveCounter)
{

	moveCounter = 0;
	opponentMoveCounter=0;
	int m, n; 
	int continueOpponentMoveCounting=0;
	int directionCounter=0;
	
	for (int x=0; x<GAMESIZE; x++)
		for (int y=0; y<GAMESIZE; y++)
		{
			if(board[x][y] == EMPTY)
			{
				directionCounter = 0;
				continueOpponentMoveCounting=0;
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
						while (board[m][n] == (turn==BLACK?WHITE:BLACK))
						{
				
							m+=i;	
							n+=j;
							if (m>=GAMESIZE ||n>=GAMESIZE || m<0 || n<0)
								break;
							if(board[m][n]==turn)
							{	
								// so This is Hole
								list[moveCounter].x=x;
								list[moveCounter].y=y;
									//cout << "x=" << x << " y=" << y << "\n";
								if(i==0)
									list[moveCounter].capturedDiscs[directionCounter]=(((n-y)>0)?(n-y-1):(-(n-y)-1));
								else 
									list[moveCounter].capturedDiscs[directionCounter]=(((m-x)>0)?(m-x-1):(-(m-x)-1)); 
								////cout << x+1 << " "<< y+1 << "\n n";
							}
							
							//cout <<"makeMoveList: number oof captured disk for X: "<< x <<" Y: " << y <<" and DIR: "<< directionCounter <<" => "<< list[moveCounter].capturedDiscs[directionCounter] << "\n";
						}//end of while
						m=x+i;
						n=y+j;
						while (continueOpponentMoveCounting && board[m][n] == turn)
						{
							m+=i;	
							n+=j;
							if (m>=GAMESIZE ||n>=GAMESIZE || m<0 || n<0)
								break;
							if(board[m][n]==(turn==BLACK?WHITE:BLACK))
							{	
								// so This is Hole
								opponentMoveCounter++;
								continueOpponentMoveCounting=0;
								//cout << "opponent x ,y "<< x << ","<< y << "\n";
							}
						}
						directionCounter++;
					}
				if(list[moveCounter].x==x && list[moveCounter].y==y)
				{		
					moveCounter++; // for the next hole
				} 
			}
		}
}

void Position::potentialMobility(int & ourFrontier, int & opponentFrontier  )
{
	ourFrontier=0, opponentFrontier=0;
	bool found;
	for (int x=0; x<GAMESIZE; x++)
		for (int y=0; y<GAMESIZE; y++)
		{
			if(board[x][y] == BLACK || board[x][y] == WHITE  )
			{
				found = false;
				for (int i=-1; i<=1 && !found; i++)
					for (int j=-1; j<=1; j++)
					{		
						if (i==0 && j==0)
							continue;
						if (x+i>=GAMESIZE ||y+j>=GAMESIZE || x+i<0 || y+j<0)						
							continue;		
						if(board[x+i][y+j]==EMPTY)
						{
							if(board[x][y]==turn)
								ourFrontier++;
							else if ( board[x][y] == (turn==BLACK?WHITE:BLACK) )
								opponentFrontier++;
							found = true;
							break;
						}
					}
			}
		}
}
void Position::doMove(MOVE * move)
{
	//cout << "In do move: " << key << "\n";
	int m, n;
	int directionCounter=0;
	board[move->x][move->y]=turn;
	if(turn==WHITE)
		whiteScore++;
	else
		blackScore++;
	key^=hashNumbers[move->x][move->y][(turn==BLACK)?0:1];
	for (int i=-1; i<=1; i++)
			for (int j=-1; j<=1; j++)
			{		
				if(i==0&&j==0)
					continue;
				m=move->x;
				n=move->y;
				//cout <<"number of captured disk for X: "<< move->x <<" Y: " << move->y <<" and DIR: "<< directionCounter <<" => " <<move->capturedDiscs[directionCounter] << "\n";
				for (int k=0;k<move->capturedDiscs[directionCounter];k++)
				{

					m+=i;	
					n+=j;
					////cout << "m = " << m << " n = " << n << "\n";
					board[m][n]=turn;
					if(turn==WHITE)
					{
						whiteScore++;
						blackScore--;
					}
					else
					{
						blackScore++;
						whiteScore--;
					}
	
					key^=hashNumbers[m][n][(turn==BLACK)?1:0]; //!turn
					key^=hashNumbers[m][n][(turn==BLACK)?0:1]; //turn
				}
				directionCounter++;
			}
	
	turn=((turn==BLACK)?WHITE:BLACK);
	remainingMoves--;
	

}

void Position::undoMove(MOVE * move)
{
	int m,n;
	int directionCounter=0;
	board[move->x][move->y]=EMPTY;
	if(turn==(turn==BLACK)?WHITE:BLACK)
		whiteScore--;
	else
		blackScore--;
	key^=hashNumbers[move->x][move->y][	(turn==BLACK)?1:0]; //!turn
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
					board[m][n]=turn;
					key^=hashNumbers[m][n][	(turn==BLACK)?0:1]; // turn
					key^=hashNumbers[m][n][	(turn==BLACK)?1:0]; //!turn
					if(turn==WHITE)
					{	
						whiteScore++;
						blackScore--;
					}
					else
					{	
						whiteScore--;
						blackScore++;
					}
				}
				directionCounter++;
			}


	turn=(turn==BLACK)?WHITE:BLACK;
	remainingMoves++;
	
	
//	cout << "In undo move: " << key << "\n";
}
