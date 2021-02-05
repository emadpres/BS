#include <QtGui/QApplication>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "GameController.h"

//Main Function of program
int main(int argc, char *argv[])
{
	//typically we should create an application
	QApplication a(argc, argv);
	
	//this would be our main window
	QMainWindow* win = new QMainWindow();
	//show the window maximized
	win->showMaximized();
	
	//for a graphics application we should create a model(scene) and a widget for this model(view)
	QGraphicsScene* gscene = new QGraphicsScene();
	QGraphicsView* gview = new QGraphicsView(gscene);
	
	// GameController is mine, it is for controlling othello game
	GameController* control = new GameController(gscene);
	
	//exit button
	QPushButton* exitBtn = new QPushButton("Exit");
	win->connect(exitBtn,SIGNAL(clicked()),win,SLOT(close()));

	//laying out view and button vertically
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(gview);
	layout->addWidget(exitBtn);
	
	//this is main widget of window
	QFrame* mainWidget = new QFrame();
	
	mainWidget->setLayout(layout);

	win->setCentralWidget(mainWidget);
	
	//from here the main loop of program will start
	return a.exec();
}
 
