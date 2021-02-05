
#define BLACK 0
#define WHITE 1

int Turn_Unit(bool change = false)
{
	static int turn = BLACK; //this variable saves the turn, WHITE starts the game
 
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
