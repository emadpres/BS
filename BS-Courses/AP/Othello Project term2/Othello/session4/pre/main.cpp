#include <QtGui/QApplication>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "OthelloItem.h"
#include "OthelloBoard.h"




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QMainWindow* win = new QMainWindow();
	win->showMaximized();
	
	QGraphicsScene* gscene = new QGraphicsScene();
	QGraphicsView* gview = new QGraphicsView(gscene);
	

	OthelloBoard* board = new OthelloBoard();
	board->setRect(0,0,GAMESIZE*ITEMW,GAMESIZE*ITEMW);
	gscene->addItem(board);
	for(int i=0;i<GAMESIZE;i++){
		board->items.append(QList<OthelloItem*>());
		for(int j=0;j<GAMESIZE; j++){
			board->items[i].append(new OthelloItem(board,i,j));
		}
	}
	
	QPushButton* exitBtn = new QPushButton("Exit");
	win->connect(exitBtn,SIGNAL(clicked()),win,SLOT(myQuit()));
	
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(gview);
	layout->addWidget(exitBtn);
	
	QFrame* mainWidget = new QFrame();
	
	mainWidget->setLayout(layout);
	win->setCentralWidget(mainWidget);
	
	return a.exec();
}
 
