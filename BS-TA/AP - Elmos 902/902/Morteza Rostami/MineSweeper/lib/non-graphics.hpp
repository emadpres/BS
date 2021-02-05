#include <stdlib.h>

using namespace std;

void FirstMove(int,int,int,int,int,int);
void MapAnalyser(int,int,int);
int MineChecker(int,int,int,int,int);
void MineLayer(int,int,int,int);

///////////////////////////////////////////////////////////////////////////////////////

void MineLayer(int minenum,int x,int y,int bmap[30][16])
{
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			bmap[i][j]=0;
	int counter=0;
	srand(time(0));
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
		{
			int m,n;
			m=random()%x;
			n=random()%y;
			if(bmap[m][n]!=-1)
			{
				bmap[m][n]=-1;
				counter++;
				if(counter>=minenum)
					return;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////////////////

int MineChecker(int xpos,int ypos,int x,int y,int bmap[30][16])
{
	int counter=0;
	if(bmap[xpos][ypos]==-1)
		return -1;
	else
		for(int p=xpos-1;p<xpos+2;p++)
			for(int q=ypos-1;q<ypos+2;q++)
				if(bmap[p][q]==-1 && p>=0 && p<=x-1 && q>=0 && q<=y-1)
					counter++;
		return counter;
}

//////////////////////////////////////////////////////////////////////////////////////

void MapAnalyser(int x,int y,int bmap[30][16])
{
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			bmap[i][j]=MineChecker(i,j,x,y,bmap);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////

void FirstMove(int xpos,int ypos,int x,int y,int bmap[30][16],int minenum)
{
	MineLayer(minenum,x,y,bmap);
	MapAnalyser(x,y,bmap);
	if(bmap[xpos][ypos]!=-1)
		return;
	else
		FirstMove(xpos,ypos,x,y,bmap,minenum);
}