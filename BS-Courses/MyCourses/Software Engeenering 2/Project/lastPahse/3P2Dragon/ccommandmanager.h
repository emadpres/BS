#ifndef CCOMMANDMANAGER_H
#define CCOMMANDMANAGER_H

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QtDeclarative>


class CCommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CCommandManager(QObject *parent = 0);
    //************************************
    // Method:    doCommand
    // FullName:  CCommandManager::doCommand
    // Access:    public 
    // Returns:   QT_NAMESPACE::QString
    // Qualifier:
    // Parameter: QString exeFile
    // Parameter: QStringList args
    //************************************
    QString doCommand(QString exeFile , QStringList args);
signals:
    
public slots:

private:

    
};

#endif // CCOMMANDMANAGER_H
