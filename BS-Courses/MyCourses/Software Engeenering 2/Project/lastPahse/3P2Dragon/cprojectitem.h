#ifndef CPROJECTITEM_H
#define CPROJECTITEM_H

#include <QDeclarativeItem>
#include <QtGui>
#include <Qtcore>
#include <QtTest>

class CProjectItem : public QObject
{
    Q_OBJECT
public:
    explicit CProjectItem(QObject *parent = 0);
    //************************************
    // Method:    addItem
    // FullName:  CProjectItem::addItem
    // Access:    public 
    // Returns:   bool
    // Qualifier:
    // Parameter: QString name
    // Parameter: QString path
    // Parameter: QString type
    // Parameter: QString url
    //************************************
    bool addItem(QString name, QString path, QString type,QString url);

signals:
    
public slots:

private slots:
	//************************************
	// Method:    testAddItem_data
	// FullName:  CProjectItem::testAddItem_data
	// Access:    private 
	// Returns:   void
	// Qualifier: test Data
	//************************************
	void testAddItem_data();
	//************************************
	// Method:    testAddItem
	// FullName:  CProjectItem::testAddItem
	// Access:    private 
	// Returns:   void
	// Qualifier: forTesting
	//************************************
	void testAddItem();
};

#endif // CPROJECTITEM_H
