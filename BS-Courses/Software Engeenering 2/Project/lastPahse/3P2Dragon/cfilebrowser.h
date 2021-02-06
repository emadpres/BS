#ifndef CFILEBROWSER_H
#define CFILEBROWSER_H

#include <QtGui>
#include <Qtcore>

#include "thumbnailiconprovider.h"
#include "crepositorymanager.h"

class CFileBrowser : public QListView
{
    Q_OBJECT
public:
    //************************************
    // Method:    CFileBrowser
    // FullName:  CFileBrowser::CFileBrowser
    // Access:    public 
    // Returns:   
    // Qualifier:
    // Parameter: QWidget * parent
    //************************************
    explicit CFileBrowser(QWidget *parent = 0);
    //************************************
    // Method:    createMenu
    // FullName:  CFileBrowser::createMenu
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString type
    //************************************
    void createMenu(QString type);
	//************************************
	// Method:    setCurrenyPath
	// FullName:  CFileBrowser::setCurrenyPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: QString path
	//************************************
	void setCurrenyPath(QString path);
signals:
    //************************************
    // Method:    sendCommand
    // FullName:  CFileBrowser::sendCommand
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QStringList args
    //************************************
    void sendCommand(QStringList args); //type , command name , path
public slots:
    //************************************
    // Method:    changePath
    // FullName:  CFileBrowser::changePath
    // Access:    public 
    // Returns:   void
    // Qualifier:
    //************************************
    void changePath();
	//************************************
	// Method:    actionTriggered
	// FullName:  CFileBrowser::actionTriggered
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: QString name
	//************************************
	void actionTriggered(QString name);

protected:
    //************************************
    // Method:    contextMenuEvent
    // FullName:  CFileBrowser::contextMenuEvent
    // Access:    protected 
    // Returns:   void
    // Qualifier:
    // Parameter: QContextMenuEvent * e
    //************************************
    void contextMenuEvent (QContextMenuEvent *e);

private:
    void config();
    void init();

private:
	QString mType;
    QString mCurrentPath;

    QFileSystemModel *mFileModel;
    QMenu *menu;
	QAction *menu_act;
};

#endif // CFILEBROWSER_H
