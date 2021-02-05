#include "ccommandmanager.h"
#include <Windows.h>
CCommandManager::CCommandManager(QObject *parent) :
    QObject(parent)
{
}

QString CCommandManager::doCommand(QString exeFile, QStringList args)
{
    QProcess *process = new QProcess(this);

    QDir dir;
    bool ok = dir.mkdir(args[0]);

    QString msg = exeFile;
	for (int i = 0 ; i < args.size() ; i++)
	{
		msg += " ";
		msg += args[i];
	}

    qDebug() << msg << ok;
	//system(msg.toLatin1().data());
    process->start(msg);
	
	process->waitForStarted();

	process->waitForFinished();

    QByteArray result = process->readAll();

    connect(process,SIGNAL(finished(int)),process,SLOT(deleteLater()));

    return QString(result);
}
