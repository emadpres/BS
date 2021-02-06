#ifndef __OthelloItem_H__
#define __OthelloItem_H__

#include "OthelloBoard.h"

class OthelloItem
{
	enum CellStatus {W,B,E};
	CellStatus status;

public:
	friend class OthelloBoard;	// cause , wanna change a private property of c[8][8] !!
	OthelloItem();

};

#endif