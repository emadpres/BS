#include <QStatusBar>
#include <QLabel>
#include "BASICS.h"
#include "OthelloAbstractBoard.h"
class OthelloAnnouncer
{
	public:
		OthelloAnnouncer (QStatusBar * statusBar);
		void showTurn(STATE currentTurn);
		void showScore(OthelloAbstractBoard abstractBoard);
		void announceEndOfGame(OthelloAbstractBoard abstractBoard);
	private:
		QStatusBar * statusBar;
		QLabel * scoreLabel;
		QLabel * turnLabel;
};
