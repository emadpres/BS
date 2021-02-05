#include "player.h"
#include "OthelloBoard.h"
#include "OthelloLogic.h"
#include <QDateTime>


player::player():OthelloPlayer(){

}

player::~player()
{

}


void player::init(OthelloBoard* b,TURN t){
	OthelloPlayer::init(b,t);
	scoreBoard = new float *[8];
	myTurn = t;
	for(int i=0;i<8;i++)
	{
		scoreBoard[i]=new float[8];
	}
	scoreBoard[0][0]=scoreBoard[0][7]=scoreBoard[7][0]=scoreBoard[7][7]=1000;

	scoreBoard[0][1]=scoreBoard[0][6]=scoreBoard[1][0]=scoreBoard[1][7]=2;///

	scoreBoard[1][3]=scoreBoard[1][4]=scoreBoard[3][1]=scoreBoard[3][6]=1;

	scoreBoard[4][1]=scoreBoard[4][6]=scoreBoard[6][3]=scoreBoard[6][4]=1;

	scoreBoard[6][0]=scoreBoard[6][7]=scoreBoard[7][1]=scoreBoard[7][6]=2;////

	scoreBoard[1][2]=scoreBoard[1][5]=scoreBoard[2][1]=scoreBoard[2][6]=2;

	scoreBoard[5][1]=scoreBoard[5][6]=scoreBoard[6][2]=scoreBoard[6][5]=2;

	scoreBoard[2][3]=scoreBoard[2][4]=scoreBoard[3][2]=scoreBoard[3][5]=3;

	scoreBoard[4][2]=scoreBoard[4][5]=scoreBoard[5][3]=scoreBoard[5][4]=3;

	scoreBoard[2][2]=scoreBoard[2][5]=scoreBoard[5][2]=scoreBoard[5][5]=4;

	scoreBoard[0][3]=scoreBoard[0][4]=scoreBoard[7][3]=scoreBoard[7][4]=5;

	scoreBoard[3][0]=scoreBoard[3][7]=scoreBoard[4][0]=scoreBoard[4][7]=5;

	scoreBoard[0][2]=scoreBoard[0][5]=scoreBoard[2][0]=scoreBoard[2][7]=6;

	scoreBoard[5][0]=scoreBoard[5][7]=scoreBoard[7][2]=scoreBoard[7][5]=6;

	scoreBoard[1][1]=scoreBoard[1][6]=scoreBoard[6][6]=scoreBoard[6][1]=-0.9;

}

QString player::getName()
{
	//return "BARCA++";
	return "newBarca";
}

QList<QString> player::getAuthors()
{
	return QList<QString>() << "HOSSEIN" << "MOSTAFA" ;
}

QPair<int,int>	player::nextPlay()
{
	/*BOARD b = board->state();
	
	for(int i=0;i<b.size();i++)
		for(int j=0;j<b[i].size();j++)
			if((b[i][j]==BOTHHOLE)||(b[i][j]==OthelloLogic::HoleOf(turn)))
				return QPair<int,int>(i,j);
	return QPair<int,int>(0,0);*/
		int holeRaghibScore = 0 ;
		int raghibScore=0;
		int holeRaghibCounter=0;
		holeCounter=0;
		int row=0 ,column=0;// two variable  for save i and j of final selected point.
		baseBoardScore = examBoardScore= 0;
		float sideScore[8][8];
		float savePlace[8][8];// a matrix for save total score of all points.
		float pointScore[8][8];
		for(int i = 0;i<8;i++)

			for(int j = 0;j<8;j++)
			{
				savePlace[i][j] = pointScore[i][j] = sideScore[i][j] = 0 ;
			}
		BOARD base = board->state();
		BOARD exam = board->state();
		for(int i=0;i<8;i++)
		{
			for(int j=0 ;j<8 ; j++)
			{
				if(base[i][j] == myTurn)
					baseBoardScore++;
			}
		}
		
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if( (exam[i][j] == OthelloLogic::HoleOf(myTurn) ) || ( exam[i][j] == BOTHHOLE) )
				{
					if( (i==0 && j==1 && exam[0][0]==myTurn) || (i==0 && j==6 && exam[0][7]==myTurn) ||
						(i==1 && j==0 && exam[0][0]==myTurn) || (i==1 && j==7 && exam[0][7]==myTurn) ||
						(i==6 && j==0 && exam[7][0]==myTurn) || (i==6 && j==7 && exam[7][7]==myTurn) ||
						(i==7 && j==1 && exam[7][0]==myTurn) || (i==7 && j==6 && exam[7][7]==myTurn)  )
					{
						sideScore[i][j] = 20;
					}
					raghibScore=0;
					holeCounter++;
					examBoardScore = 0;
					OthelloLogic::play(exam,i,j,myTurn);
					for(int m=0;m<8;m++)
					{	
						for(int n=0;n<8;n++)
						{
							if(exam[m][n] == myTurn)
								examBoardScore++;
						}
					}
					OthelloLogic::createHoles(exam);
					if( (exam[0][0] == OthelloLogic::HoleOf( (myTurn == BLACK)?WHITE:BLACK)   || ( exam[0][0] == BOTHHOLE)) ||
						(exam[0][7] == OthelloLogic::HoleOf( (myTurn == BLACK)?WHITE:BLACK)   || ( exam[0][7] == BOTHHOLE)) ||
						(exam[7][0] == OthelloLogic::HoleOf( (myTurn == BLACK)?WHITE:BLACK)   || ( exam[7][0] == BOTHHOLE)) ||
						(exam[7][7] == OthelloLogic::HoleOf( (myTurn == BLACK)?WHITE:BLACK)   || ( exam[7][7] == BOTHHOLE)) 
						)
					{
						raghibScore = -10;
					}
						
					//OthelloLogic::createHoles(exam);
					for(int m=0;m<8;m++)
					{	
						for(int n=0;n<8;n++)
						{
							if(exam[m][n] ==  OthelloLogic::HoleOf( (myTurn == BLACK)?WHITE:BLACK))
								holeRaghibCounter++;
						}
					}
					if(holeRaghibCounter == 0)
						holeRaghibScore = 20;
					else if(holeRaghibCounter == 1)
						holeRaghibScore = 5;
					else if(holeRaghibCounter == 2)
						holeRaghibScore = 3;
					
					pointScore[i][j] = (examBoardScore-baseBoardScore-1);
					savePlace[i][j]=(2*pointScore[i][j])+(3*scoreBoard[i][j])+(2*raghibScore)+(holeRaghibScore) + (sideScore[i][j]) ;
					exam = board->state();
				}
			}
		}
	
		QList<QPair<int ,int>> list ;
		int max = -1000;
		for(int i = 0;i<8;i++)
		{
				for(int j = 0;j<8;j++)
				{
					if((exam[i][j] == OthelloLogic::HoleOf(myTurn)) || exam[i][j]==BOTHHOLE)
					{
					
						if(savePlace[i][j] > max)
						{
							max=savePlace[i][j];
							
							list.clear();
							list.append(QPair<int,int>(i,j));
						}
						else if(max == savePlace[i][j])
						{
							list.append(QPair<int,int>(i,j));
						}
					}
				}
				if(list.size() > 1)
				{
					int mymax = 0;
					for(int i=0;i< (list.size()-1);i++)
						if(scoreBoard[list[i].first][list[i].second] >= scoreBoard[list[i+1].first][list[i+1].second])
						{
			    			mymax=scoreBoard[list[i].first][list[i].second] ;
							row = list[i].first;
							column = list[i].second;

						}
				}
				else if(list.size() == 1)
				{
					row = list[0].first;
					column = list[0].second;
				}
		}
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
				
			{
				cout<<savePlace[i][j]<<" ";
			}
			cout<<endl;
		}
		

		return QPair<int,int> (row,column);

	
}


extern "C"{
__declspec(dllexport) void* getNewInstance()
{
	return (void*) ((OthelloPlayer*)new player());
}
}