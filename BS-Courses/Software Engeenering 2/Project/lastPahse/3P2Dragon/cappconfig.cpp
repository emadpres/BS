#include "cappconfig.h"

CAppConfig::CAppConfig(QObject *qmlRoot, QObject *parent) :
    QObject(parent)
{
    //new
    mProjectManager = new CProjectManagement(qmlRoot);
    mAppSeting = new QSettings("config/appConfig.ini",QSettings::IniFormat);

    readSetting();

    //connect
    connect(mProjectManager,SIGNAL(signalForInsertToAppConfigFileFile(QString,QString,QString,QString)),this,SLOT(addProject(QString,QString,QString,QString)));
}

void CAppConfig::addProject(QString name, QString path, QString type, QString url)
{
    if (mLastProjectNumber == 1)
        return;


    mAppSeting->setValue(QString("project%1/name").arg(mLastProjectNumber),name);
    mAppSeting->setValue(QString("project%1/path").arg(mLastProjectNumber),path);
    mAppSeting->setValue(QString("project%1/type").arg(mLastProjectNumber),type);
	mAppSeting->setValue(QString("project%1/url").arg(mLastProjectNumber),url);

//    QFile configFile("config/appConfig.ini");
//    if (!configFile.open(QIODevice::Append | QIODevice::Text))
//    {
//        qDebug() << "cant open QFile ";
//        return;
//    }

//    QTextStream out(&configFile);
//    out << QString("[") + QString("project%1").arg(mLastProjectNumber) + QString("]") << endl;
//    out << QString("name = ") + name << endl;
//    out << QString("path = ") + path << endl;
//    out << QString("type = ") + type << endl;
//    out << endl;

//    configFile.close();

    return;

}

void CAppConfig::readSetting()
{
    int i=1;

    while (true)
    {
        QString projectName = mAppSeting->value(QString("project%1/name").arg(i),"error").toString();
        QString projectPath = mAppSeting->value(QString("project%1/path").arg(i),"error").toString();
        QString projectType = mAppSeting->value(QString("project%1/type").arg(i),"error").toString();
		QString url = mAppSeting->value(QString("project%1/url").arg(i),"error").toString();

        if (projectName == "error" || projectPath == "error" || projectType == "error" || url == "error")
        {
            qDebug() << "at index " << i << "config finished" << projectName << projectPath<< projectType << url <<QString("project%1/type").arg(i) ;
            mLastProjectNumber = i;
            return;
        }
        else
        {
            mProjectManager->addItem(projectName,projectPath,projectType,url);
        }

        i++;
    }
}
