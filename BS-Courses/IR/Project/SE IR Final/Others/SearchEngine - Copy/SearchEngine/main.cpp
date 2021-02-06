#include <QtGui/QApplication>
#include "window.h"
#include "Searcher/searcher.h"
#include "cluster.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
/*	CWindow w;
	w.show();*/

	CSearcher *s = new CSearcher();
	s->MakeIndex();

	CCluster *cluster = new CCluster(s);
	cluster->Cluster(73);

	return a.exec();
}
