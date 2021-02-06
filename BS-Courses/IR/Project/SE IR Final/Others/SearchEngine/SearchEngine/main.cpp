#include <QtGui/QApplication>
#include "window.h"
#include "Searcher/searcher.h"
#include "centroidCluster.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
/*	CWindow w;
	w.show();*/

	CSearcher *s = new CSearcher();
	s->MakeIndex();

	CCentroidCluster *obj = new CCentroidCluster(s);
	obj->Cluster(31);

	return a.exec();
}
