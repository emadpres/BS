#ifndef __OTHELLOCONTROLLER_H__
#define __OTHELLOCONTROLLER_H__

#include "BASICS.h"
#include "OthelloBoard.h"
#include "OthelloAbstractBoard.h"
#include "OthelloAnnouncer.h"
#include "OthelloDocumenter.h"
#include "SillyPlayer.h"

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
		SillyPlayer * player;
		STATE currentTurn;
		void initializeGame();
		void changeTurn();	
	private slots:
		void computerPlay();
};

#endif
