#ifndef CREPOSITORYMANAGER_H
#define CREPOSITORYMANAGER_H

#include <QtGui>
#include <QtCore>
#include <QtXml>

struct menuInfo
{
    QString name;
    QString filePath;
    QStringList args;
    QString iconPath;
};
struct repInfo
{
    QString executeFile;
    QList<menuInfo> menus;
};

class CRepositoryManager : public QObject
{
    Q_OBJECT
public:
    explicit CRepositoryManager(QObject *parent = 0);
    //************************************
    // Method:    readRepInfo
    // FullName:  CRepositoryManager::readRepInfo
    // Access:    public 
    // Returns:   void
    // Qualifier:
    //************************************
    void readRepInfo();
    //************************************
    // Method:    initAppRepository
    // FullName:  CRepositoryManager::initAppRepository
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: QString type
    //************************************
    void initAppRepository(QString type);
	//************************************
	// Method:    getMenuesInfo
	// FullName:  CRepositoryManager::getMenuesInfo
	// Access:    public 
	// Returns:   QList<menuInfo>
	// Qualifier:
	// Parameter: QString type
	//************************************
	QList<menuInfo>getMenuesInfo(QString type);
	//************************************
	// Method:    getExcuteFile
	// FullName:  CRepositoryManager::getExcuteFile
	// Access:    public 
	// Returns:   QT_NAMESPACE::QString
	// Qualifier:
	// Parameter: QString type
	//************************************
	QString getExcuteFile(QString type);
	//************************************
	// Method:    getFilePath
	// FullName:  CRepositoryManager::getFilePath
	// Access:    public 
	// Returns:   QT_NAMESPACE::QString
	// Qualifier:
	// Parameter: QString type
	// Parameter: QString name
	//************************************
	QString getFilePath(QString type , QString name);
	//************************************
	// Method:    getExecArgs
	// FullName:  CRepositoryManager::getExecArgs
	// Access:    public 
	// Returns:   QT_NAMESPACE::QStringList
	// Qualifier:
	// Parameter: QString type
	// Parameter: QString name
	//************************************
	QStringList getExecArgs(QString type , QString name);
signals:
    
public slots:
    
private:
    QMap<QString , repInfo > mAppRepository;
};

#endif // CREPOSITORYMANAGER_H
