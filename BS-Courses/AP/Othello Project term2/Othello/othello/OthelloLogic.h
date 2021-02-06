#pragma once

#include <QList>
#include "MBasics.h"

class OthelloLogic{
public:
	//í˜ ãÑÍáå ÈÇÒí ÑÇ ÔÈíå ÓÇÒí ãí˜äÏ æ äÊíÌå ÑÇ ÏÑ ÊÎÊå ÇÚãÇá ãí˜äÏ
	static bool play(BOARD& board, int x, int y, TURN turn){
		return OthelloLogic::_play(board,x,y,turn,true,false);
	}

	//í˜ ãÑÍáå ÈÇÒí ÑÇ ÈÑÑÓí ãí˜äÏ ˜å ÂíÇ ãã˜ä ÇÓÊ
	static bool canPlay(BOARD& board, int x, int y, TURN turn){
		return OthelloLogic::_play(board,x,y,turn,false,false);
	}
	
	//˜ ãí˜äÏ ˜å ÂíÇ í˜ ÈÇÒí˜ä ãíÊæÇäÏ ÈÇÒí ˜äÏ
	static bool canPlay(BOARD& board, TURN turn){
		for(int i=0;i<board.size();i++)
			for(int j=0;j<board.size();j++){
				cout << i << j << endl;
				if(((board[i][j]!=WHITE)&&(board[i][j]!=BLACK))&&
					(OthelloLogic::canPlay(board,i,j,turn)))
					return true;
			}
		return false;
	}

	//ÍÇáÇÊ ÈÇÒí ÈÑÇí ÊãÇã ÎÇäå åÇí ÎÇáí ÈÑÑÓí ãí˜äÏ
	static void createHoles(BOARD& board){
		//first we clear all holes
		for(int i=0;i<board.size();i++)
			for(int j=0;j<board[i].size();j++)
				if((board[i][j]!=WHITE)&&(board[i][j]!=BLACK))
					board[i][j] = EMPTY;
		for(int i=0;i<board.size();i++)
			for(int j=0;j<board[i].size();j++)
				if(board[i][j]==EMPTY){
					OthelloLogic::_play(board,i,j,WHITE,false,true);	
					OthelloLogic::_play(board,i,j,BLACK,false,true);	
				}
	}

	static TURN HoleOf(TURN t){
		switch(t){
			case WHITE:
				return WHITEHOLE;
			case BLACK:
				return BLACKHOLE;
			default:
				return BOTHHOLE;
		}
	}
private:
	static bool _play(BOARD& board, int x, int y, TURN turn, bool apply,bool markHole){
		bool r = false;
		if((board[x][y] == WHITE)||(board[x][y] == BLACK))
			return false;
		for(int i=0;i<8;i++)
			r = r | _applyTurnPlay(board,x,y,turn,(DIRECTION)i,apply,true);
		if(r && apply)
			board[x][y] = turn;
		if(r && markHole){
			TURN t = (turn==WHITE)?WHITEHOLE:BLACKHOLE;
			board[x][y] = ((board[x][y]!=EMPTY)&&(board[x][y]!=t))?BOTHHOLE:t;
		}
		return r;					
	}

	static bool _applyTurnPlay(BOARD& board, int x, int y, TURN turn, DIRECTION dir, bool apply, bool first){
		int newx=x,newy=y;
		switch(dir){
			case UP:newy--;break;
			case UPRIGHT:newx++;newy--;break;
			case RIGHT:newx++;break;
			case DOWNRIGHT:newx++;newy++;break;
			case DOWN:newy++;break;
			case DOWNLEFT:newy++;newx--;break;
			case LEFT:newx--;break;
			case UPLEFT:newx--;newy--;break;
		}
		
		if((newx<0)||(newy<0)||(newy>=board[0].size())||(newx>=board.size()))
			return false;
		
		if((board[newx][newy]!=WHITE)&&(board[newx][newy]!=BLACK))
			return false;
		
		if((first)&&
			(turn==board[newx][newy]))
				return false;
		
		if(turn==board[newx][newy])
			return true;
		
		if(_applyTurnPlay(board,newx,newy,turn,dir,apply,false))
		{
			if (apply)
				board[newx][newy] = turn;
			return true;
		}else return false;
	}
};
