#ifndef CQMLFILEBROWSERCOMPONENT_H
#define CQMLFILEBROWSERCOMPONENT_H

#include <QDeclarativeItem>
#include <QtGui>
#include <Qtcore>

#include "cfilebrowser.h"
#include "ccommandmanager.h"
#include "crepositorymanager.h"

class CQmlFileBrowserComponent : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString mProjectPath READ projectPath WRITE setProjectPath)
	Q_PROPERTY(QString mProjectType READ ProjectType WRITE setProjectType)
	Q_PROPERTY(QString mProjectName READ ProjectName WRITE setProjectName)
public:
    explicit CQmlFileBrowserComponent(QDeclarativeItem *parent = 0);

    //************************************
    // Method:    projectPath
    // FullName:  CQmlFileBrowserComponent::projectPath
    // Access:    public 
    // Returns:   QT_NAMESPACE::QString
    // Qualifier: const
    //************************************
    QString projectPath() const
    {
        qDebug() << "sa";
        return mProjectPath;
    }

    //************************************
    // Method:    setProjectPath
    // FullName:  CQmlFileBrowserComponent::setProjectPath
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: const QString & text
    //************************************
    void setProjectPath(const QString &text)
    {
        qDebug() << "s2";
        mProjectPath = text;
		mBrowser->setCurrenyPath(mProjectPath);
    }

	//************************************
	// Method:    ProjectType
	// FullName:  CQmlFileBrowserComponent::ProjectType
	// Access:    public 
	// Returns:   QT_NAMESPACE::QString
	// Qualifier: const
	//************************************
	QString ProjectType() const 
	{ 
		return mProjectType;
	}
	//************************************
	// Method:    setProjectType
	// FullName:  CQmlFileBrowserComponent::setProjectType
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const QString & val
	//************************************
	void setProjectType(const QString &val)
	{
		mProjectType = val;
		mBrowser->createMenu(mProjectType);
	}
    
	//************************************
	// Method:    ProjectName
	// FullName:  CQmlFileBrowserComponent::ProjectName
	// Access:    public 
	// Returns:   QT_NAMESPACE::QString
	// Qualifier: const
	//************************************
	QString ProjectName() const
	{
		return mProjectName;
	}
	//************************************
	// Method:    setProjectName
	// FullName:  CQmlFileBrowserComponent::setProjectName
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const QString & val
	//************************************
	void setProjectName(const QString &val) 
	{ 
		qDebug() << "project name: " << val;
		mProjectName = val;
	}
signals:
    
public slots:
	void doSendCommand(QStringList args);
private:

    CFileBrowser *mBrowser;
    QGraphicsProxyWidget *mProxy;

    QString mProjectPath;
    QString mProjectType;
	QString mProjectName;
	

};

#endif // CQMLFILEBROWSERCOMPONENT_H
