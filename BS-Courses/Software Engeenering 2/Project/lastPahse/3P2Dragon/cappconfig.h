#ifndef CAPPCONFIG_H
#define CAPPCONFIG_H

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QtDeclarative>

#include "cfilebrowser.h"
#include "CQmlFileBrowserComponent.h"
#include "cprojectitem.h"
#include "cprojectmanagement.h"

#include <QtDeclarative>
#include <QDeclarativeView>

class CAppConfig : public QObject
{
    Q_OBJECT
public:
    explicit CAppConfig(QObject* qmlRoot , QObject *parent = 0);

signals:
    
public slots:
    //************************************
    // Method:    addProject
    // FullName:  CAppConfig::addProject
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString name
    // Parameter: QString path
    // Parameter: QString type
    // Parameter: QString url
    //************************************
    void addProject(QString name,QString path , QString type , QString url);

private:
    //************************************
    // Method:    readSetting
    // FullName:  CAppConfig::readSetting
    // Access:    private 
    // Returns:   void
    // Qualifier:
    //************************************
    void readSetting();

private:
    CProjectManagement *mProjectManager;
    QSettings* mAppSeting;
    int mLastProjectNumber;
};

#endif // CAPPCONFIG_H
