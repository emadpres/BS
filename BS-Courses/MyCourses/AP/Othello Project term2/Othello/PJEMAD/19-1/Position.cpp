#include "Position.h"

Position::Position(bool ourTurn)
{
	remainingMoves=60;
	
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
						directionCounter++;
					}
					if(list[moveCounter].x==x && list[moveCounter].y==y)
						moveCounter++; // for the next hole
			}

		}
	////cout << moveCounter << "\n";
	return moveCounter;
}

void Position::doMove(MOVE * move)
{
	int m, n;
	int directionCounter=0;
	board[move->x][move->y]=turn;
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
				}
				directionCounter++;
			}
	turn=!turn;
	remainingMoves--;
}

void Position::undoMove(MOVE * move)
{
	int m,n;
	int directionCounter=0;
	board[move->x][move->y]=EMPTY;
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
				}
				directionCounter++;
			}
	turn=!turn;
	remainingMoves++;
}
