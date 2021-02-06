#include <QApplication>
#include <QMainWindow>
#include <QStatusBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPainter>

#include "OthelloController.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	QWidget * mainWidget = new QWidget;
	QMainWindow * mainWindow = new QMainWindow();
	
	QGraphicsScene * scene = new QGraphicsScene;
	QGraphicsView * view = new QGraphicsView(scene);
	view->setRenderHint(QPainter::Antialiasing, true);	

	QStatusBar * statusBar = new QStatusBar;
	OthelloController * controller = new OthelloController(statusBar);
	scene->addItem(controller->getBoard());
	
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
