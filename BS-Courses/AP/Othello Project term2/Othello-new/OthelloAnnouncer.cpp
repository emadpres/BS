#include "OthelloAnnouncer.h"

OthelloAnnouncer::OthelloAnnouncer(QStatusBar * statusBar)
{
	this->statusBar = statusBar;
	scoreLabel = new QLabel("Dark:2 Light:2");
	turnLabel = new QLabel("Dark's Move");
	scoreLabel->setAlignment(Qt::AlignRight);
	statusBar->addWidget(turnLabel);
	statusBar->addWidget(scoreLabel,1);
	statusBar->setFont(QFont("Verdana", 10));
}

void OthelloAnnouncer::showTurn(STATE currentTurn)
{
	if (currentTurn == WHITE)
		turnLabel->setText("Light's Move");
	if (currentTurn == BLACK)
		turnLabel->setText("Dark's Move");
}

void OthelloAnnouncer::announceEndOfGame(OthelloAbstractBoard abstractBoard)
{
		STATE winner = abstractBoard.winner();
		
		if (winner==WHITE)
			turnLabel->setText("Light is the Winner!");
		else if (winner==BLACK)
			turnLabel->setText("Dark is the Winner!");
		else if (winner==EMPTY)
			turnLabel->setText("Draw, Tied Up!");
}

void OthelloAnnouncer::showScore(OthelloAbstractBoard abstractBoard)
{
	int whiteScore= abstractBoard.scoreUnit(WHITE);
	int blackScore= abstractBoard.scoreUnit(BLACK);

	QString string;
	string.append("Dark:" + QString::number(blackScore));
	string.append(" Light:" + QString::number(whiteScore));
	scoreLabel->setText(string);
}
