#include "Position.h"

#include <iostream>
using std::cout;


/*void Position::showBoard()
{
	LOG << "   ";
		for (int i=1; i<=GAMESIZE; i++)
			LOG <<  "  "<< i << "  "; 
		LOG << "\n\n";

		for (int i=1; i<=GAMESIZE; i++)	
		{	
			LOG  << i << "  ";
			for(int j=1;j<=GAMESIZE;j++)
				switch(board[i-1][j-1])
				{
					case EMPTY:
						LOG << "  .  "; 
						break;
					case BLACK:
						LOG << "  B  ";
						break;
					case WHITE:
						LOG << "  W  ";
						break;
				
				}
			LOG << "\n\n";
		}
}*/

Position::Position(bool ourTurn)
{
	blackHasCornerUpLeft=false;
	blackHasCornerUpRight=false;
	blackHasCornerDownRight=false;
	blackHasCornerDownLeft=false;
	whiteHasCornerUpLeft=false;
	whiteHasCornerUpRight=false;
	whiteHasCornerDownRight=false;
	whiteHasCornerDownLeft=false;
	
	//LOG.open("Log34.log");
	remainingMoves=60;
	blackScore=whiteScore=2;
	for (int i=0; i<GAMESIZE; i++)
		for (int j=0; j<GAMESIZE; j++)
		{
			board[i][j] = EMPTY;
		}
	
	turn=ourTurn;
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
								if(i==0)
									list[moveCounter].capturedDiscs[directionCounter]=(((n-y)>0)?(n-y-1):(-(n-y)-1));
								else 
									list[moveCounter].capturedDiscs[directionCounter]=(((m-x)>0)?(m-x-1):(-(m-x)-1)); 
							}

							
						}//end of while
						directionCounter++;
					}//End of 8 Direction for
					
					if(list[moveCounter].x==x && list[moveCounter].y==y)
						moveCounter++; // for the next hole
			}//End of WHITE IF

		}//End of 64 for
	
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
								if(i==0)
									list[moveCounter].capturedDiscs[directionCounter]=(((n-y)>0)?(n-y-1):(-(n-y)-1));
								else 
									list[moveCounter].capturedDiscs[directionCounter]=(((m-x)>0)?(m-x-1):(-(m-x)-1)); 
							}
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
								opponentMoveCounter++;
								continueOpponentMoveCounting=0;
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
	int m, n;
	int directionCounter=0;
	board[move->x][move->y]=turn;
	if(turn==WHITE)
		whiteScore++;
	else
		blackScore++;
	if (turn==WHITE)
	{
		if (move->x == 0 && move->y == 0)
			whiteHasCornerUpLeft = true;
		else if (move->x == 0 && move->y == GAMESIZE-1)
			whiteHasCornerUpRight = true;
		else if (move->x == GAMESIZE-1 && move->y == 0)
			whiteHasCornerDownLeft = true;
		else if (move->x == GAMESIZE-1 && move->y == GAMESIZE-1)
			whiteHasCornerDownRight = true;
	}
	else
	{
		if (move->x == 0 && move->y == 0)
			blackHasCornerUpLeft = true;
		else if (move->x == 0 && move->y == GAMESIZE-1)
			blackHasCornerUpRight = true;
		else if (move->x == GAMESIZE-1 && move->y == 0)
			blackHasCornerDownLeft = true;
		else if (move->x == GAMESIZE-1 && move->y == GAMESIZE-1)
			blackHasCornerDownRight = true;
	}
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
	if (turn==WHITE)
	{
		if (move->x == 0 && move->y == 0)
			whiteHasCornerUpLeft = false;
		else if (move->x == 0 && move->y == GAMESIZE-1)
			whiteHasCornerUpRight = false;
		else if (move->x == GAMESIZE-1 && move->y == 0)
			whiteHasCornerDownLeft = false;
		else if (move->x == GAMESIZE-1 && move->y == GAMESIZE-1)
			whiteHasCornerDownRight = false;
	}
	else
	{
		if (move->x == 0 && move->y == 0)
			blackHasCornerUpLeft = false;
		else if (move->x == 0 && move->y == GAMESIZE-1)
			blackHasCornerUpRight = false;
		else if (move->x == GAMESIZE-1 && move->y == 0)
			blackHasCornerDownLeft = false;
		else if (move->x == GAMESIZE-1 && move->y == GAMESIZE-1)
			blackHasCornerDownRight = false;
	}
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
}
