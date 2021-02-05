#ifndef __OthelloBoard_H__
#define __OthelloBoard_H__


#include <iostream>
using namespace std;
#include "OthelloItem.h"
class OthelloItem;

class OthelloBoard
{

	OthelloItem c[8][8];
	int whiteScore,blackScore;
	void change(int row,int colume);

public:
	//friend class OthelloItem; //Cause wanna use ''Change'' Func from that !
	OthelloBoard();
	bool isAnyMove();
	void Score();
	
	void show();
};

#endif