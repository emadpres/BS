#include <QApplication>
#include <QMainWindow>
#include <QStatusBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

#include "OthelloBoard.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	QWidget * mainWidget = new QWidget;
	QMainWindow * mainWindow = new QMainWindow();
	
	QGraphicsScene * scene = new QGraphicsScene;
	QGraphicsView * view = new QGraphicsView(scene);
	view->setRenderHint(QPainter::Antialiasing, true);	
	
	QStatusBar * statusBar = new QStatusBar;
	QLabel * scoreLabel = new QLabel("Dark:2 Light:2");
	QLabel * turnLabel = new QLabel("Dark's Move");
	scoreLabel->setAlignment(Qt::AlignRight);
	statusBar->addWidget(turnLabel);
	statusBar->addWidget(scoreLabel,1);
	statusBar->setFont(QFont("Verdana", 10));
	OthelloBoard * board= new OthelloBoard(scoreLabel, turnLabel);
	scene->addItem(board);
	
	QVBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(view);
	mainWidget->setLayout(layout);

	mainWindow->setCentralWidget(mainWidget);
	mainWindow->setStatusBar(statusBar);
	
	mainWindow->setFixedSize(mainWidget->sizeHint().width(), mainWidget->sizeHint().height()+65);
	mainWindow->move(0,0);
	mainWindow->setWindowTitle("PJ Othello");
	mainWindow->show();

	return app.exec();
};
