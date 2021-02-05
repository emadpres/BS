#ifndef __OTHELLOCONTROLLER_H__
#define __OTHELLOCONTROLLER_H__

#include "BASICS.h"
#include "OthelloBoard.h"
#include "OthelloAbstractBoard.h"
#include "OthelloAnnouncer.h"
#include "OthelloDocumenter.h"
#include "OurPlayer.h"
#include "player2/Revenge.h"

class OthelloBoard;

class OthelloController : public QObject
{
	Q_OBJECT
	
	public:
		OthelloController(QStatusBar * statusBar);
		OthelloBoard * getBoard();
		void humanPlay(int x, int y);
	private:
		void play(int x, int y);
		OthelloBoard * board;
		OthelloAnnouncer * announcer;
		OthelloDocumenter * documenter;
		OurPlayer * player1;
		Revenge * player2;
		STATE currentTurn;
		void initializeGame();
		void changeTurn();	
	private slots:
		void computerPlay();
};

#endif
