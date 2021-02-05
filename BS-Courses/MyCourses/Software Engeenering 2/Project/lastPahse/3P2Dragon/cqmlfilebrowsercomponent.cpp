#include "cqmlfilebrowsercomponent.h"

CQmlFileBrowserComponent::CQmlFileBrowserComponent(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
   mBrowser = new CFileBrowser();
   mProxy = new QGraphicsProxyWidget(this);
   mProxy->setWidget(mBrowser);
   mProxy->setPos(-mBrowser->sizeHint().width()/2, -mBrowser->sizeHint().height()/2);

   connect(mBrowser,SIGNAL(sendCommand(QStringList)),this,SLOT(doSendCommand(QStringList)));
}

void CQmlFileBrowserComponent::doSendCommand( QStringList args )//type , command name , path
{
	CCommandManager comMan;
	CRepositoryManager repMan;

	QString exec = repMan.getExcuteFile(args[0]) + " " + repMan.getFilePath(args[0],args[1]);
	QStringList execArgs;

	QStringList retArgs = repMan.getExecArgs(args[0],args[1]);

	while (retArgs.size() > 0)
	{
		QString temp = retArgs.first();

		if (temp == "PATH")
		{
			execArgs.append(mProjectPath);
		}
		else if (temp == "FILE")
		{
			execArgs.append(args[2]);
		}
		else if (temp == "PROJECTNAME")
		{
			execArgs.append(mProjectName);
		}

		retArgs.removeOne(temp);
	}

	comMan.doCommand(exec,execArgs);
}
