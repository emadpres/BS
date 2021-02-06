#include <QApplication>

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QtTest>

#include "cfilebrowser.h"
#include "CQmlFileBrowserComponent.h"
#include "cprojectitem.h"
#include "cprojectmanagement.h"
#include "cappconfig.h"
#include "ccommandmanager.h"
#include "crepositorymanager.h"
#include "cchart.h"

#include <QtDeclarative>
#include <QDeclarativeView>

void myMessageOutput(QtMsgType type, const char *msg)
{
	FILE *f;
	f = fopen("app.log", "w");
	switch (type) {
	case QtDebugMsg:
		fprintf(f, "time: %s Debug: %s\n", QTime::currentTime().toString("hh:mm:ss").toLocal8Bit().data(),msg);
		break;
	case QtWarningMsg:
		fprintf(f, "time: %s Warning: %s\n", QTime::currentTime().toString("hh:mm:ss").toLocal8Bit().data(),msg);
		break;
	case QtCriticalMsg:
		fprintf(f, "time: %s Critical: %s\n", QTime::currentTime().toString("hh:mm:ss").toLocal8Bit().data(),msg);
		break;
	case QtFatalMsg:
		fprintf(f, "time: %s Fatal: %s\n", QTime::currentTime().toString("hh:mm:ss").toLocal8Bit().data(),msg);
		abort();
	}
	fclose(f);
}

int main(int argc, char *argv[])
{
	//qInstallMsgHandler(myMessageOutput);
    QApplication app(argc,argv);

    qDebug() << "alo";

    //    CFileBrowser w;
    //    w.show();

    qmlRegisterType<CQmlFileBrowserComponent>("FileBrowserComponent", 1, 0, "FileBrowser");
    QDeclarativeView *view = new QDeclarativeView();
    view->setSource(QUrl::fromLocalFile("qml/main.qml"));
    view->show();

	CAppConfig appConfig(view->rootObject());
    //test
    /*CProjectItem item1(view->rootObject());
    item1.addItem("vali","c:\\","svn");

    CProjectManagement manager(view->rootObject());
        CAppConfig appConfig(view->rootObject());

        QStringList args ;
        args << "c:/gholy12/googooli2" << "khoobi" << "https://github.com/alirezabe/narm2.git";
        CCommandManager cMan;
        qDebug() << "SALAM PROCESS " <<  cMan.doCommand("ruby D:/gitTest/clone.rb",args);


    CRepositoryManager r;
    r.readRepInfo();

		QMap<QString,int> ali;
		ali["ali"] = 10;
		ali["ali2"] = 8;
		ali["ali3"] = 18;
		ali["ali4"] = 11;
		CChart ch(ali);
		ch.show();*/

    //end test

		//test
		//QTest::keyClick(view, Qt::Key_registered);

		/*for (int i = 0 ; i < 100000 ; i++)
		{
			QPoint pos;
			qsrand(i);
			pos.setX(qrand()% 800);
			qsrand(i+1);
			pos.setY(qrand()%800);
			QTest::mouseClick(view,Qt::LeftButton,0,pos);
		}*/

		/*QTEST_MAIN(CProjectItem)
		#include "CProjectItem.moc"*/
		//end test

    //    QDomDocument doc("mydocument");
    //    QFile file("C:\\Users\\ALIREZA\\Downloads\\CGit.rb");
    //    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    //        qDebug() << "error";

    //    if (!doc.setContent(&file)) {
    //         file.close();

    //     }
    //     file.close();


    //     QDomElement docElem = doc.documentElement();

    //      QDomNode n = docElem.firstChild();
    //      qDebug() << "alo";
    //      while(!n.isNull()) {
    //          qDebug() << "first child";
    //          QDomElement e = n.toElement(); // try to convert the node to an element.
    //          if(!e.isNull()) {
    //              qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
    //          }
    //          n = n.nextSibling();
    //      }



    app.exec();
}
