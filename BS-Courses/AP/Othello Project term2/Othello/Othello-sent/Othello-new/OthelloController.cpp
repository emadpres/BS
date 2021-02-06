#include "OthelloController.h"

OthelloController::OthelloController(QStatusBar * statusBar)
{
	board= new OthelloBoard(this);
	announcer = new OthelloAnnouncer(statusBar);
	documenter = new OthelloDocumenter();
	initializeGame();
}

void OthelloController::initializeGame()
{
	int size = GAMESIZE;
	currentTurn = BLACK; //The game starts with black
	
	player = new SillyPlayer(board,WHITE); // Silly player's turn is set to white
	//If the game started by silly player call computerPlay()
	board->humanTurn= BLACK; // Human turn is set to white
	
	OthelloAbstractBoard initialBoard;
	initialBoard = board->getState();

	initialBoard.items[size/2-1][size/2-1] = WHITE;
	initialBoard.items[size/2][size/2] = WHITE;
	initialBoard.items[size/2][size/2-1] = BLACK;
	initialBoard.items[size/2-1][size/2] = BLACK;
	
	initialBoard.createHoles(currentTurn);
	board->setState(initialBoard, currentTurn);

	documenter->outputBoard(initialBoard);
	documenter->outputScore(initialBoard);
	documenter->outputTurn(currentTurn);	
}

OthelloBoard * OthelloController::getBoard()
{
	return this->board;
}

void OthelloController::humanPlay(int x, int y)
{
	play(x,y);

	//if you want 2 players version comment out the following line:
	QTimer::singleShot(board->delayDuration + 1000, this, SLOT(computerPlay()));
	board->delayDuration=0;
}

void OthelloController::computerPlay()
{
	while(player->getTurn()==currentTurn)
	{	
		OthelloAbstractBoard abstractBoard;
		abstractBoard = board->getState();
	
		QPair<int,int> nextMove;
		do
		{
			nextMove = player->nextPlay();
		}while(!abstractBoard.canPlay(nextMove.first, nextMove.second));
		play(nextMove.first,nextMove.second);
	}
}

void OthelloController::play(int x, int y)
{
	OthelloAbstractBoard abstractBoard;
	abstractBoard = board->getState();
	abstractBoard.play(x,y,currentTurn);
	documenter->outputMove(x, y);

	changeTurn();
	abstractBoard.createHoles(currentTurn);

	if (abstractBoard.noMove())
	{
		//anouncer anounce there was no move and turn changed.
		documenter->outputNoMove(currentTurn);

		changeTurn();
		abstractBoard.createHoles(currentTurn);
		
		if (abstractBoard.noMove()) //again no move
		{
				//anouncer anounce there was no move and turn changed.
				documenter->outputNoMove(currentTurn);
				
				announcer->announceEndOfGame(abstractBoard);
				documenter->outputWinner(abstractBoard);

				currentTurn = EMPTY;				
				board->setState(abstractBoard, currentTurn);
				return; //end of game
		}
	}
	
	board->setState(abstractBoard, currentTurn);
	documenter->outputBoard(abstractBoard);
	
	announcer->showScore(abstractBoard);
	documenter->outputScore(abstractBoard);
	
	announcer->showTurn(currentTurn);
	documenter->outputTurn(currentTurn);	
}

void OthelloController::changeTurn()
{
	if (currentTurn == WHITE)
		currentTurn = BLACK;
	else 
		currentTurn = WHITE;
}
