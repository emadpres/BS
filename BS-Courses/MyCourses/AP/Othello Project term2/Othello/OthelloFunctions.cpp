#define BLACK 0
#define WHITE 1
#define HOLE -1
#define EMPTY -2

#define WHITE_WINS -30
#define BLACK_WINS -40
#define DRAW -50

#define NOT_A_HOLE -60

#define SIZE 8

#include <iostream>
using std::cout;
using std::cin;


void Initial_Unit(int Board[][SIZE]);
/*
Function: Initializes the Board
Gets: Board
Returns: -
*/
void Draw_Unit(int Borad[][SIZE],int WhiteScore, int BlackScore);
/*
Function: Draws the Board and prints Scores
Gets: Board, Score of White and Black playes
Returns: -
*/
int Turn_Unit(bool change=false);
/*
Function: Returns and Changes the turn
Gets: A boolean, if the boolean is true it changes the turn, Otherwise it only returns the turn
Returns: Turn of the current player
	
note: this function saves the turn using a static variable
*/
void Hole_Unit(int Board[][SIZE]);
/*
Function: Finds the holes
Gets: Board
Returns: -
*/
void Input_Unit(int & x, int &y);
/*
Function: Gets the next move from user
Gets: -
Returns: x and y which are output parameters
*/
bool RightMove(int Board[][SIZE], int x, int y);
/*
Function: Checks if (x,y) is a hole for the current turn
Gets: Board, (x,y)
Returns: ture if (x,y) is a hole, otherwise false
*/
void Color_Unit(int Board[][SIZE],int x, int y);
/*
Function: finds the paths to be colored around (x,y) and sends to Apply_Color to color them
Gets: Board, (x,y)
Returns: -
*/
void Apply_Color(int Board[][SIZE], int x1, int y1, int x2, int y2);
/*
Function: Applies color Of the current turn from (x1,y1) to (x2,y2)
Gets: Board and (x1,y1), (x2,y2)
Returns: -
*/
void Clear_Holes(int Board[][SIZE]);
/*
Function: Clears the holes from Board after each move
Gets: Board
Returns: -
*/
int Score_Unit(int Board[][SIZE], int turn);
/*
Function: Returns score of the given turn
Gets: Board, and turn
Returns: Score
*/
bool Final_Unit(int Board[][SIZE]);
/*
Function: 
	Uses the function ThereIsNoMove to see if the game continues
	Uses the function Winner_Unit to find the winner when there is no move
Gets: Board
Returns: -
*/
bool ThereIsNoMove(int Board[][SIZE]);
/*
Function: Sees if there is any holes left in the board for the current turn
Gets: Board
Returns: true if there is no move, otherwise false
*/
int Winner_Unit(int Board[][SIZE]);
/*
Function: Returns which player has more disks or the players are equal
Gets: Board
Returns: WHITE_WINS or BLACK_WINS or DRAW
*/
void Initial_Unit(int Board[][SIZE])
{
	for (int i=0; i<SIZE; i++)	
		for(int j=0;j<SIZE;j++)
			Board[i][j]=EMPTY;
	Board[3][3]=Board[4][4]=WHITE;
	Board[3][4]=Board[4][3]=BLACK;
}
void Draw_Unit(int Board[][SIZE], int WhiteScore, int BlackScore)
{
	cout << "   ";
	for (int i=0; i<SIZE; i++)
		cout <<  "  "<< i << "  "; 
	cout << "\n\n";

	for (int i=0; i<SIZE; i++)	
	{	
		cout  << i << "  ";
		for(int j=0;j<SIZE;j++)
			switch(Board[i][j])
			{
				case EMPTY:
					cout << "  .  "; 
					break;
				case BLACK:
					cout << "  B  ";
					break;
				case WHITE:
					cout << "  W  ";
					break;
				case HOLE:
					cout << "  ?  "	;
					break;
			}
		cout << "\n\n";
	}
	
	cout << "White Score: " << WhiteScore << "\n";
	cout << "Black Score: " << BlackScore << "\n";	
}
int Turn_Unit(bool change)
{
	static int turn = WHITE; //this variable saves the turn, WHITE starts the game
 
	if (change) // if change == true change the turn
		switch(turn)
		{
			case WHITE:
				turn = BLACK;
				break;
			case BLACK:
				turn = WHITE;
		}
	return turn;	
}
void Hole_Unit(int Board[][SIZE]) //This function finds the holes
{
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
		{
			if (Board[x][y] != EMPTY ) 
				continue;
			
			int turn = Turn_Unit(); //Turn_Unit returns the turn
			
			for (int i=x-1; i<=x+1; i++) // (x-1,y-1) to (x+1,y+1) are all cells around a cell
				for (int j=y-1; j<=y+1; j++)
				{
					if ((i==x && j==y) || i>=SIZE || j>=SIZE || i<0 || j<0)
						continue;  					int m=i, n=j;
					while(Board[m][n] == (turn==BLACK?WHITE:BLACK))
					{
						if (m>x) 
							m++;		
						if (m<x)
							m--;
						if (n>y)
							n++;
						if (n<y)
							n--;
		
						if (m>=SIZE ||n>=SIZE || m<0 || n<0)
							break;
		
						if(Board[m][n]==turn)
						{		
							Board[x][y] = HOLE;
						}
					}
				}
		}
}
void Input_Unit(int & x, int & y)
{
	switch(Turn_Unit())
	{
		case WHITE:
			cout << "WHITE: ";
			break;
		case BLACK:
			cout << "BLACK: ";
	}
	cin >> x >> y;
}
bool RightMove(int Board[][SIZE], int x, int y) // this functions checks if the move is allowed
{	
	if (x>=SIZE || y>=SIZE || x<0 || y<0)	
		return false;
	
	if (Board[x][y] == HOLE)
		return true;
	else 
		return false;	
}
void Color_Unit(int Board[][SIZE],int x, int y) //this functions finds the cells to be colored
{
	int turn = Turn_Unit(); //Turn_Unit returns the turn

	for (int i=x-1; i<=x+1; i++)
		for (int j=y-1; j<=y+1; j++)
		{
			if ((i==x && j==y) || i>=SIZE || j>=SIZE || i<0 || j<0)
				continue;

			int m=i,n=j;

			while(Board[m][n] == (turn==BLACK?WHITE:BLACK))
			{
				if (m>x) 
					m++;
				if (m<x)
					m--;
				if (n>y)
					n++;
				if (n<y)
					n--;
		
				if (m>=SIZE ||n>=SIZE || m<0 || n<0)
					break;
		
				if(Board[m][n]==turn)
				{		
					Apply_Color(Board,x,y,m,n); //changes the color from (x,y) to (m,n)
				}
			}
		}	
}
void Apply_Color(int Board[][SIZE],int x1, int y1, int x2 , int y2) //This functions applies color from (x1,y1) to (x2,y2)
{
	int turn = Turn_Unit();	//Turn_Unit returns the turn
	
	int m=x1;
	int n=y1;

	do 
	{
		Board[m][n] = turn; //applies the color		
		if (!(m==x1 && n==y1))
			{	
				Color_Unit(Board,x1,y1); // as a game rule all the changed cells should be checked again
			}

		if (x2>m) 
			m++;
		if (x2<m)
			m--;
		if (y2>n)
			n++;
		if (y2<n)
			n--;		
	}while(!(m==x2 && n==y2));
}
int Score_Unit(int Board[][SIZE], int turn) //Calculates score of the given turn
{
	int score=0;	
	for (int i=0; i<SIZE; i++)	
		for(int j=0;j<SIZE;j++)
		{
			if(Board[i][j]==turn)
				score++;
		}
 	return score;
}
void Clear_Holes(int Board[][SIZE])
{
	for (int i=0; i<SIZE; i++)	
		for(int j=0;j<SIZE;j++)
			if (Board[i][j]==HOLE)
				Board[i][j]=EMPTY;
	
}
bool Final_Unit(int Board[][SIZE]) //Checks if the game is over
{
	if (ThereIsNoMove(Board)) 
	{
		cout << "There is no move for " << (Turn_Unit()==WHITE? "White.\n":"Black.\n") ; 
	
		Turn_Unit(true); //changes the turn since there is no move for the current turn
		Clear_Holes(Board);
		Hole_Unit(Board); // finds the holes for the new turn
		
		if (ThereIsNoMove(Board)) //if both players have no moves the game is over
		{
			cout << "There is no move for " << (Turn_Unit()==WHITE? "White.\n":"Black.\n") ;
			cout << "End of the Game!\n";

			int winner= Winner_Unit(Board); //Winner_Unit says which player has more disks

			if (winner == WHITE_WINS) 
				cout << "White is the Winner!\n";
			else if (winner == BLACK_WINS)
				cout << "Black is the Winner!\n";
			else if (winner == DRAW)
				cout  << "Draw, Tied Up!\n";

			return true; // true mean there is no move
		}

		int WhiteScore=Score_Unit(Board,WHITE);
		int BlackScore=Score_Unit(Board,BLACK);
		Draw_Unit(Board,WhiteScore,BlackScore); // Since the turn has changed the board should be drawn again

	}
	return false; // false means there is a move
}
bool ThereIsNoMove(int Board[][SIZE])
{
	for (int i=0; i<SIZE; i++)	
		for(int j=0;j<SIZE;j++)
			if (Board[i][j]==HOLE)
			{
				return false; // if a hole is found, there is a move
			}
	return true; //there is no holes, so there is no moves
}
int Winner_Unit(int Board[][8])
{
	int WhiteScore = Score_Unit(Board,WHITE);
	int BlackScore = Score_Unit(Board,BLACK);


	if (WhiteScore > BlackScore)
		return WHITE_WINS;
	else if (BlackScore > WhiteScore)
		return BLACK_WINS;
	else  //BlackScore == WhiteScore
		return DRAW;	
}
