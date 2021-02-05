#ifndef __MAINTASKS__
#define __MAINTASKS__

#include "mbasics.h"
#include "OurBasics.h"
#include <iostream>
#include <fstream>
#include "OurPlayer.h"
//using std::cout;
int OurPlayer::alphabeta(Position * position, int depth, int alpha, int beta)
{
	//cout << "Start of alphabeta " << "depth:" << depth << "\n";
	//position->//cout << "Remaining depth:" << depth << "\n\n";
	
	MOVE list[MAXMOVES];
	int numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	
	for(int i=0; i<MAXMOVES; i++)
		{
		list[i].x=777;
		list[i].y=777;
		//list[i].capturedDiscs={777,777,777,777,777,777,777,777};
		}
	if(depth == 0)	
	{
		//cout << "returning from alphabeta with depth " << depth << "\n";
		return evaluation(position);
	}	
	numberOfMoves = position->makeMoveList(list);
	if(numberOfMoves == 0) 
	{
		position->turn=(position->turn==BLACK?WHITE:BLACK);			// change Turn
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
				return 0;
			}
		}
		//cout << "returning alphabeta with depth" << depth-1 << "\n";
		return -alphabeta(position,depth-1,-beta,-localalpha);
	}
		
	int selectedMovesIndex[12];
	int offset=0;
	bool cornerFound = false;
	bool normalFound = false;
	int moveCounter = 0;
	int selectedIndexOffset=0;
	if (position->turn == BLACK)
	{
	//cout << "start of black if\n";
		for (moveCounter = 0; moveCounter< numberOfMoves; moveCounter++)
		{
			if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
					(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
						{
							cornerFound = true;
							offset = 0;
							selectedMovesIndex[offset]= moveCounter;
							//cout << "found the first corner breaking\n";
							break; //found the first corner
						}
			if ((!position->blackHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->blackHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->blackHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->blackHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1)))) 			
			{
				//cout << "in the if for adjacents\n";
				selectedMovesIndex[offset] = moveCounter;
				offset++;
			}
			else
			{
				//cout << "normal found breaking \n";
				normalFound = true;
				break;
			}
		
		} // end of first move section
		if (normalFound && !cornerFound) //we don't set normalfound true again! :-D ha ha 
		{
			//cout << "start of normal found and not corner found\n";
			
			for (moveCounter++; moveCounter< numberOfMoves; moveCounter++)
			{
				//cout << "start for\n";
				if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
						(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
							{
								//cout << "found the first corner second one breaking\n";
								cornerFound = true;
								offset = 0;
								selectedMovesIndex[offset]= moveCounter;
								break; //found the first corner
							}
				//cout << "still in the for after checking corners\n";
				if ((!position->blackHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) || 
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->blackHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->blackHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->blackHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1)))) 			
				{
					//cout << "adjacent if\n";
					selectedMovesIndex[offset] = moveCounter;
					offset++;
				} 
			//cout << "end of for\n";
			}
		//cout << "out of for\n";
		} // end of normalfound move section
	}//end of black section
	else //if (position->turn == WHITE)	
	{
		//cout << "start of white if\n";
		for (moveCounter = 0; moveCounter< numberOfMoves; moveCounter++)
		{
			if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
					(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
						{
							//cout << "found the first corner breaking \n";
							cornerFound = true;
							offset = 0;
							selectedMovesIndex[offset]= moveCounter;
							break; //found the first corner
						}
			if ((!position->whiteHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->whiteHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->whiteHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->whiteHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1))))
			{
				//cout << "adjacent if \n";
				selectedMovesIndex[offset] = moveCounter;
				offset++;
			}
			else
			{
					//cout << "normal found breaking\n";
				normalFound = true;
				break;
			}
		
		} // end of first move section
		if (normalFound && !cornerFound) //we don't set normalfound true again! :-D ha ha 
		{
			//cout << "start of normal found and corner not found if\n";
			for (moveCounter++; moveCounter< numberOfMoves; moveCounter++)
			{
				if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
						(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
							{
								//cout << "found the first corner second one breaking\n";
								cornerFound = true;
								offset = 0;
								selectedMovesIndex[offset]= moveCounter;
								break; //found the first corner
							}
				if ((!position->whiteHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->whiteHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->whiteHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->whiteHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1))))
				{
					//cout << "adjacent if\n";
					selectedMovesIndex[offset] = moveCounter;
					offset++;
				}
			}
		} // end of normalfound move section
	}//end of white section
	if (cornerFound) //search for the other corners
	{
		//cout << "search for other corners\n";
		for (int i = (selectedMovesIndex[offset]+1); i<numberOfMoves; i++)
		{
			//cout << "in the for \n";
			if ((list[i].x == 0 && list[i].y == 0) || 
					(list[i].x == GAMESIZE-1 && list[i].y == 0) ||
					(list[i].x == 0 && list[i].y == GAMESIZE-1) ||
					(list[i].x == GAMESIZE-1 && list[i].y == GAMESIZE-1 ))
						{
							//cout << "if another corner found offset++\n";
							offset++;
							selectedMovesIndex[offset]= i;
						}
		}
		for(int i=0; i<=offset; i++) //search found corners
		{
			//cout << "search found corners\n";
			position->doMove(&list[selectedMovesIndex[offset]]);
			//cout << "calling alphabeta with depth: " << ((depth>1)?1:depth-1) << "\n";
			value = -alphabeta(position,(depth>1)?1:depth-1,-beta,-localalpha);
			//cout << "after returning\n";
			position->undoMove(&list[selectedMovesIndex[offset]]);
			bestvalue = (value>bestvalue)?value:bestvalue;
			if(bestvalue>=beta) 
				break;
			if(bestvalue>localalpha) 
				localalpha=bestvalue;
			//cout << "end of for\n";
		}
				//cout << "returning inf/2\n";
			return bestvalue + INFINITY/2;
	} // end of corner section
	
	else if(normalFound)
	{
		//cout << "else if normal found\n";
	
		for(int i=0; i<numberOfMoves; i++)
		{
			//cout << "start of for which wants to skip adjacents\n";
			if (i == selectedMovesIndex[selectedIndexOffset])
			{
				//cout << "in the if\n";
				if (selectedIndexOffset<offset-1)
				{	
					//cout << "selectedIndexOffset++\n";
					selectedIndexOffset++;
				}
				else
				{
					//break; run for without this part
				}
				//cout << "continuing\n";
				continue;
			}
			//cout << "out of if\n";
			position->doMove(&list[i]);
			//cout << "calling alphabeta with depth" << depth-1 << "\n";
			value = -alphabeta(position,depth-1,-beta,-localalpha);
			//cout << "now here continuning in alphabeta depth:" << depth << "\n";
			position->undoMove(&list[i]);
			bestvalue = (value>bestvalue)?value:bestvalue;
			if(bestvalue>=beta) 
				break;
			if(bestvalue>localalpha) 
				localalpha=bestvalue;
			//cout << "end of for\n";
		}
		//cout << "out of for, returning bestvalue depth = " << depth << "\n";
		//cout << bestvalue << "\n";
		return bestvalue;

	} //end of normal found
	else //all moves are adjacent
	{
		//cout << "else all moves are adjacent\n";
		for(int i=0; i<numberOfMoves; i++)
		{
		//cout << "in the for\n";
		position->doMove(&list[i]);
		//cout << "calling alphabeta with depth" << depth-1 << "\n";
		value = -alphabeta(position,depth-1,-beta,-localalpha);
		//cout << "now here after returing\n";
		position->undoMove(&list[i]);
		bestvalue = (value>bestvalue)?value:bestvalue;
		if(bestvalue>=beta) 
			break;
		if(bestvalue>localalpha) 
			localalpha=bestvalue;
		//cout << "end of for2\n";
		}
		//cout << "returning -inf/2\n";
		return bestvalue - INFINITY/2;
	}
}
MOVE OurPlayer::firstAlphabeta(Position * position, int depth, int alpha, int beta)
{
	MOVE list[MAXMOVES];
	int i,numberOfMoves,value,localalpha=alpha,bestvalue=-INFINITY;
	int bestMoveIndex=0;
	numberOfMoves = position->makeMoveList(list);
	
	int selectedMovesIndex[12];
	int offset=0;
	bool cornerFound = false;
	bool normalFound = false;
	int moveCounter = 0;
	if (position->turn == BLACK)
	{
		for (moveCounter = 0; moveCounter< numberOfMoves; moveCounter++)
		{
			if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
					(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
						{
							cornerFound = true;
							offset = 0;
							selectedMovesIndex[offset]= moveCounter;
							break; //found the first corner
						}
			if ((!position->blackHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->blackHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->blackHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->blackHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1))))
			{
				selectedMovesIndex[offset] = moveCounter;
				offset++;
			}
			else
			{
				normalFound = true;
				break;
			}
	
		} // end of first move section
		if (normalFound && !cornerFound) //we don't set normalfound true again! :-D ha ha 
		{
			for (moveCounter++; moveCounter< numberOfMoves; moveCounter++)
			{
				if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
						(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
							{
								cornerFound = true;
								offset = 0;
								selectedMovesIndex[offset]= moveCounter;
								break; //found the first corner
							}
			if ((!position->blackHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->blackHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->blackHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->blackHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1)))) 								
				{
					selectedMovesIndex[offset] = moveCounter;
					offset++;
				}
			}
		} // end of normalfound move section
	} // end of black part
	else //if (position->turn ==WHITE)
	{
				for (moveCounter = 0; moveCounter< numberOfMoves; moveCounter++)
		{
			if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
					(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
					(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
						{
							cornerFound = true;
							offset = 0;
							selectedMovesIndex[offset]= moveCounter;
							break; //found the first corner
						}
			if ((!position->whiteHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->whiteHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->whiteHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->whiteHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1)))) 								
			{
				selectedMovesIndex[offset] = moveCounter;
				offset++;
			}
			else
			{
				normalFound = true;
				break;
			}
	
		} // end of first move section
		if (normalFound && !cornerFound) //we don't set normalfound true again! :-D ha ha 
		{
			for (moveCounter++; moveCounter< numberOfMoves; moveCounter++)
			{
				if ((list[moveCounter].x == 0 && list[moveCounter].y == 0) || 
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 0) ||
						(list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-1) ||
						(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-1 ))
							{
								cornerFound = true;
								offset = 0;
								selectedMovesIndex[offset]= moveCounter;
								break; //found the first corner
							}
				if ((!position->whiteHasCornerUpLeft && ((list[moveCounter].x == 0 && list[moveCounter].y == 1) ||
														(list[moveCounter].x == 1 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == 1 && list[moveCounter].y == 1)))
															
					||(!position->whiteHasCornerUpRight && ((list[moveCounter].x == 0 && list[moveCounter].y == GAMESIZE-2) ||				
															(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == 1 && list[moveCounter].y == GAMESIZE-1)))
																
					||(!position->whiteHasCornerDownLeft && ((list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 0) ||
															(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == 1) ||
																(list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == 1)))
																
					||(!position->whiteHasCornerDownRight &&	((list[moveCounter].x == GAMESIZE-1 && list[moveCounter].y == GAMESIZE-2) ||
																(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-2) ||
																	(list[moveCounter].x == GAMESIZE-2 && list[moveCounter].y == GAMESIZE-1))))
				{
					selectedMovesIndex[offset] = moveCounter;
					offset++;
				}
			}
		} // end of normalfound move section
	} //end of white part
	
	if (cornerFound) //search for the other corners
	{
		for (int i = (selectedMovesIndex[offset]+1); i<numberOfMoves; i++)
		{
			if ((list[i].x == 0 && list[i].y == 0) || 
					(list[i].x == GAMESIZE-1 && list[i].y == 0) ||
					(list[i].x == 0 && list[i].y == GAMESIZE-1) ||
					(list[i].x == GAMESIZE-1 && list[i].y == GAMESIZE-1 ))
						{
							offset++;
							selectedMovesIndex[offset]= i;
						}
		}
		for(int i=0; i<=offset; i++) //search found corners
		{
			position->doMove(&list[selectedMovesIndex[offset]]);
			//cout << "calling alphabeta with depth" << ((depth>1)?1:depth-1 )<< "\n";
			value = -alphabeta(position,(depth>1)?1:depth-1,-beta,-localalpha);
			//cout << "now here after alphabeta 4\n";
			position->undoMove(&list[selectedMovesIndex[offset]]);
			if (value > bestvalue)
			{
				bestvalue = value;
				bestMoveIndex = selectedMovesIndex[offset];
			}
			if(bestvalue>=beta) 
				break;
			if(bestvalue>localalpha) 
				localalpha=bestvalue;
			return list[bestMoveIndex];
		}
	} // end of corner section
	
	else if(normalFound)
	{
		int selectedIndexOffset=0;
		for(i=0; i<numberOfMoves; i++)
		{
			if(i == selectedMovesIndex[selectedIndexOffset])
			{
				if (selectedIndexOffset<offset-1)
				{	
					selectedIndexOffset++;
				}
				else
				{
					//break; run for without this part
				}
				continue;
			}
			position->doMove(&list[i]);
						//cout << "calling alphabeta with depth" << depth-1 << "\n";
			value = -alphabeta(position,depth-1,-beta,-localalpha);
			//cout << "now here after alphabeta 5\n";
			position->undoMove(&list[i]);
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
	
		return list[bestMoveIndex];
	} //end of normal found
				
	else //all moves are adjacent
	{
		for(i=0; i<numberOfMoves; i++)
		{
			position->doMove(&list[i]);
						//cout << "calling alphabeta with depth" << depth-1 << "\n";
			value = -alphabeta(position,depth-1,-beta,-localalpha);
			//cout << "now here after alphabeta 6\n";
			position->undoMove(&list[i]);
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
	
		return list[bestMoveIndex];
	}
}

int OurPlayer::evaluation(Position * position)
{
	int ourMovesCounter=0,opponentMovesCounter=0;
	int ourPotentialMobility=0, opponentPotentialMobility=0;
	int evaluation=0;
	int mobility=0;
	int potentialMobility=0;
	//int corner=0;
	//int adjacentCorner=0;
	int stable=0;
	
	if (ourTurn==BLACK)
	{
		if (position->blackHasCornerUpLeft && position->board[1][1]==ourTurn)
			stable++;
		if (position->blackHasCornerUpRight && position->board[1][GAMESIZE-2]==ourTurn)
			stable++;
		if (position->blackHasCornerDownLeft && position->board[GAMESIZE-2][1]==ourTurn)
			stable++;
		if (position->blackHasCornerDownRight && position->board[GAMESIZE-2][GAMESIZE-2]==ourTurn)
			stable++;
	}
	else
	{
		if (position->whiteHasCornerUpLeft && position->board[1][1]==ourTurn)
			stable++;
		if (position->whiteHasCornerUpRight && position->board[1][GAMESIZE-2]==ourTurn)
			stable++;
		if (position->whiteHasCornerDownLeft && position->board[GAMESIZE-2][1]==ourTurn)
			stable++;
		if (position->whiteHasCornerDownRight && position->board[GAMESIZE-2][GAMESIZE-2]==ourTurn)
			stable++;
	}
	
	
	MOVE list[MAXMOVES];
	position->makeMoveList(list, ourMovesCounter, opponentMovesCounter);
	position->potentialMobility(ourPotentialMobility, opponentPotentialMobility);
	
	mobility=ourMovesCounter-opponentMovesCounter;
	potentialMobility= ourPotentialMobility - opponentPotentialMobility;
	int around=0;
	for(int i=2; i<GAMESIZE-2; i++)
	{
		if (position->board[0][i]==(ourTurn==BLACK)?WHITE:BLACK)
			around-=2;
		if (position->board[0][i]==ourTurn)
			around+=5;
		if (position->board[GAMESIZE-1][i]==(ourTurn==BLACK)?WHITE:BLACK)
			around-=2;
		if (position->board[GAMESIZE-1][i]==ourTurn)
			around+=5;

		if (position->board[i][0]==(ourTurn==BLACK)?WHITE:BLACK)
			around-=2;
		if (position->board[i][0]==ourTurn)
			around+=5;
		if (position->board[i][GAMESIZE-1]==(ourTurn==BLACK)?WHITE:BLACK)
			around-=2;
		if (position->board[i][GAMESIZE-1]==ourTurn)
			around+=5;
	} 
	
	int i = 0;
	int j = GAMESIZE - 1;
	while (i<GAMESIZE && position->board[0][i]==ourTurn)
	{
		stable++;		
		i++;
	}
	if (i!=GAMESIZE)
	{
		while (j>=0 && position->board[0][j]==ourTurn)
		{
			stable++;		
			j--;
		}
	}

	i = 0;
	j = GAMESIZE-1;
	while (i<GAMESIZE && position->board[GAMESIZE-1][i]==ourTurn)
	{
		stable++;		
		i++;
	}
	if (i!=GAMESIZE)
	{
		while (j>=0 && position->board[GAMESIZE-1][j]==ourTurn)
		{
			stable++;		
			j--;
		}
	}
	
	i = 0;
	j = GAMESIZE-1;
	while (i<GAMESIZE && position->board[i][0]==ourTurn)
	{
		stable++;		
		i++;
	}
	if (i!=GAMESIZE)
	{
		while (j>=0 && position->board[j][0]==ourTurn)
		{
			stable++;		
			j--;
		}
	}

	i = 0;
	j = GAMESIZE-1;
	while (i<GAMESIZE && position->board[i][GAMESIZE -1]==ourTurn)
	{
		stable++;		
		i++;
	}
	if (i!=GAMESIZE)
	{
		while (j>=0 && position->board[j][GAMESIZE-1]==ourTurn)
		{
			stable++;		
			j--;
		}
	}	
	evaluation = mobility + potentialMobility + stable * 20 + around *100;
	
	if(position->remainingMoves<=15)
	{
		if(turn==ourTurn)
			evaluation*=position->whiteScore/position->blackScore;
		else
			evaluation*=position->blackScore/position->whiteScore;
	} 
	
	if (position->turn==ourTurn)
	{
		return evaluation;
	}
	else
	{
		return -evaluation;
	}
}
#endif
