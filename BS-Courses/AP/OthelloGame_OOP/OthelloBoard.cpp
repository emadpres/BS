#include "OthelloBoard.h"

OthelloBoard::OthelloBoard()
{
	blackScore=2;
	whiteScore=2;
	//c[3][3].status=c[4][4].status=W;
	//c[3][4].status=c[4][3].status=B;

	
}
void OthelloBoard::Score()
{
	cout<<"\nWhite and Black is :\t"<<whiteScore<<" & "<<blackScore<<endl;
}
bool OthelloBoard::isAnyMove()
{
	return 1;
}

void OthelloBoard::change(int row,int colume)
{
	cout<<"Change";
}
void OthelloBoard::show()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
			cout<<i<<","<<j<<" is "<<c[i][j].status<<"  ";
		cout<<endl;
	}
}