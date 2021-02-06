#include "cprojectmanagement.h"


CProjectManagement::CProjectManagement(QObject* QMLroot ,QObject *parent) :
    QObject(parent)
{
    root = QMLroot;

	reminder = new QDeclarativeView();

	ReminderModel *model = new ReminderModel();
	reminder->rootContext()->setContextProperty("dummyModel", model);


	//viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	reminder->setSource(QUrl("qml/reminderMain.qml"));


    connect(QMLroot,SIGNAL(addProject(QString,QString,QString,QString)),this,SLOT(addItem(QString,QString,QString,QString)));
	connect(QMLroot,SIGNAL(chart(QString)),this,SLOT(showChart( QString)));
	connect(QMLroot,SIGNAL(showReminder()),this,SLOT(showReminder()));
}

void CProjectManagement::addItem(QString name, QString path, QString type,QString url)
{
	if (type == "nothing")
	{
		newProject(name,path,url,type);
		type = "git";
	}
    CProjectItem item1(root);
    item1.addItem(name,path,type,url);

    emit signalForInsertToAppConfigFileFile(name,path,type,url);

	
}

void CProjectManagement::newProject(QString name, QString path, QString url, QString type)
{
    CCommandManager comMan;

	QString execFile = "ruby config/git/clone.rb";

	QStringList arg ;
	arg << path;
	arg << name;
	arg << url;

	comMan.doCommand(execFile,arg);
}

void CProjectManagement::showChart( QString path )
{
	QDir dir(path);
	QMap<QString,int> result;
	QStringList all = dir.entryList();

	for (int i =2 ; i<all.size() ; i++)
	{
		if (!QFileInfo(all[i]).isDir())
		{
			qsrand(i);
			result[QFileInfo(all[i]).fileName()] =( qrand() % 10 ) + 1;
		}
	}

	CChart *chart = new CChart(result);
	chart->show();
}

void CProjectManagement::showReminder()
{
	reminder->show();
}
