#include "OthelloFunctions.cpp"

#define SIZE 8

int main()
{
	int Board[SIZE][SIZE];
	int x , y;
	
	int WhiteScore=2;
	int BlackScore=2;

	Initial_Unit(Board); //Initializes the Board
	Hole_Unit(Board); //Finds the Holes
	Draw_Unit(Board,WhiteScore,BlackScore); // Shows the Board

	do
	{
		do
		{
			Input_Unit(x,y); // Gets a move from user
		}while(RightMove(Board, x, y)==false); //checks if the move is allowed
		Color_Unit(Board,x,y); //Applies the move
		
		Clear_Holes(Board); //Clears the holes for the last turn	
		Turn_Unit(true); //Changes the turn
		Hole_Unit(Board); //Finds holes for the new turn
		
		WhiteScore=Score_Unit(Board,WHITE);
		BlackScore=Score_Unit(Board,BLACK);
		Draw_Unit(Board,WhiteScore,BlackScore); //Shows the Board and Scores

	}while (!Final_Unit(Board)); // While the game is not over	
	return 0;
}
