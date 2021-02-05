#include "crepositorymanager.h"

CRepositoryManager::CRepositoryManager(QObject *parent) :
    QObject(parent)
{
	readRepInfo();
}

void CRepositoryManager::readRepInfo()
{
	mAppRepository.clear();

    QDir appDir("config");

    QStringList foldersName = appDir.entryList();

    qDebug() << foldersName;

    if (foldersName.size() <= 3)
        return;

    for (int i=3 ; i<foldersName.size() ; i++ )
        initAppRepository(foldersName[i]);
}

void CRepositoryManager::initAppRepository(QString type)
{
    QFile repConfigFile(QString("config/") + type + "/config.xml");
    if(!repConfigFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "cant open " <<"config/"<<  type << "/config.xml";
        return;
    }

    QDomDocument doc("config");

    if (!doc.setContent(&repConfigFile))
    {
        repConfigFile.close();
        qDebug() << "cant set domFile  " <<"config/"<<  type << "/config.xml";
        return ;

    }
    repConfigFile.close();

    QString executeFile;
    QList<menuInfo> menues;

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            if (e.tagName() == "execute")
            {
                executeFile = e.text();
                qDebug() << "execute file is" << executeFile;
            }
            else if (e.tagName() == "menu")
            {
                menuInfo myMenu;

                QString name;
                QString filePath;
                QStringList args;
                QString iconPath;

                name = e.attribute("name","error");
                filePath = e.attribute("file","error");
                iconPath = e.attribute("icon","error");

                QDomNode arg = e.firstChild();
                while (!arg.isNull())
                {
                    QDomElement argElement = arg.toElement();
                    if (!argElement.isNull())
                        args.append(argElement.text());

                    arg = arg.nextSibling();
                }

                if (name != "error" && filePath != "error" && iconPath != "error" && args.size() > 0)
                {
                    myMenu.args = args;
                    myMenu.filePath = filePath;
                    myMenu.iconPath = iconPath;
                    myMenu.name = name;

                    menues.append(myMenu);

                    qDebug() << name <<filePath <<iconPath <<args ;
                }
            }
            //qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
           // qDebug() << e.attribute("name");
        }
        n = n.nextSibling();
    }

    repInfo info;
    info.executeFile = executeFile;
    info.menus = menues;

    mAppRepository[type] = info;


}

QList<menuInfo> CRepositoryManager::getMenuesInfo( QString type )
{
	if (mAppRepository.contains(type))
	{
		return mAppRepository[type].menus;
	}
	else
	{
		QList<menuInfo> error;
		return error;
	}
}

QString CRepositoryManager::getExcuteFile( QString type )
{
	if (mAppRepository.contains(type))
	{
		return mAppRepository[type].executeFile;
	}
	else
	{
		return "";
	}
}

QString CRepositoryManager::getFilePath( QString type , QString name )
{
	if (mAppRepository.contains(type))
	{
		QList<menuInfo> allMenu = mAppRepository[type].menus;

		for (int i = 0; i<allMenu.size() ; i++ )
		{
			if (allMenu[i].name == name)
			{
				return allMenu[i].filePath;
			}
		}
		return "";
	}
	else
	{
		return "";
	}
}

QStringList CRepositoryManager::getExecArgs( QString type , QString name )
{
	if (mAppRepository.contains(type))
	{
		QList<menuInfo> allMenu = mAppRepository[type].menus;

		for (int i = 0; i<allMenu.size() ; i++ )
		{
			if (allMenu[i].name == name)
			{
				return allMenu[i].args;
			}
		}

		return QStringList();
	}
	else
	{
		return QStringList();
	}
}
