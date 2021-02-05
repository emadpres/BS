#include "cprojectitem.h"

CProjectItem::CProjectItem(QObject *parent) :
    QObject(parent)
{
}

bool CProjectItem::addItem(QString name, QString path, QString type,QString url)
{
    QObject* obj = parent()->findChild<QObject*>("Flickable");
    if (!obj)
    {
        qDebug() << "cant create project item in c++";
        return false;
    }

    QMetaObject::invokeMethod(obj,"createProjectItem",Q_ARG(QVariant,name),Q_ARG(QVariant,name),Q_ARG(QVariant,path),Q_ARG(QVariant,type),Q_ARG(QVariant,url));

    return true;
}

void CProjectItem::testAddItem_data()
{
	QTest::addColumn<QString>("name");
	QTest::addColumn<QString>("path");
	QTest::addColumn<QString>("type");
	QTest::addColumn<QString>("url");
	QTest::addColumn<bool>("result");

	QTest::newRow("test1") << "ali" << "c:" << "svn" << "jydsgfgsfhd" << false ;
	QTest::newRow("test2") << "vali" << "asdsdads" << "git" << false;
	QTest::newRow("test3") << "alireza" << "C:" << "svn" << "https://github.com/alirezabe/narm2.git" << true;
}

void CProjectItem::testAddItem()
{
	
	QFETCH(QString, name);
	QFETCH(QString, path);
	QFETCH(QString, type);
	QFETCH(QString, url);
	QFETCH(bool, result);

	QCOMPARE(this->addItem(name,path,type,url), result);
}
