#ifndef CPROJECTMANAGEMENT_H
#define CPROJECTMANAGEMENT_H

#include "cfilebrowser.h"
#include "CQmlFileBrowserComponent.h"
#include "cprojectitem.h"
#include "ccommandmanager.h"
#include "CChart.h"
#include "ReminderModel.h"

#include <QDeclarativeItem>
#include <QtGui>
#include <Qtcore>

class CProjectManagement : public QObject
{
    Q_OBJECT
public:
    explicit CProjectManagement(QObject* QMLroot ,QObject *parent = 0);
    
signals:
    //************************************
    // Method:    signalForInsertToAppConfigFileFile
    // FullName:  CProjectManagement::signalForInsertToAppConfigFileFile
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString
    // Parameter: QString
    // Parameter: QString
    // Parameter: QString
    //************************************
    void signalForInsertToAppConfigFileFile(QString,QString,QString,QString);
public slots:
    //************************************
    // Method:    addItem
    // FullName:  CProjectManagement::addItem
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString name
    // Parameter: QString path
    // Parameter: QString type
    // Parameter: QString url
    //************************************
    void addItem(QString name,QString path , QString type,QString url);
    //************************************
    // Method:    newProject
    // FullName:  CProjectManagement::newProject
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString name
    // Parameter: QString path
    // Parameter: QString typr
    // Parameter: QString url
    //************************************
    void newProject(QString name,QString path ,QString typr ,QString url);
	//************************************
	// Method:    showChart
	// FullName:  CProjectManagement::showChart
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: QString path
	//************************************
	void showChart(QString path);
	//************************************
	// Method:    showReminder
	// FullName:  CProjectManagement::showReminder
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void showReminder();
private:
    QObject* root;
	QDeclarativeView *reminder;
};

#endif // CPROJECTMANAGEMENT_H
