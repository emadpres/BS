#include "dbwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	dbWindow w;
	w.show();
	return a.exec();
}
