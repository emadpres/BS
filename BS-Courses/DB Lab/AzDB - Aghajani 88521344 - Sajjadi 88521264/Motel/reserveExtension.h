#pragma once
//#include <QtCore>
#include "database.h"
//#include <QSqlTableModel>
#include <QWidget>

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QDateEdit>


class reserveExtension : public QWidget
{
	Q_OBJECT
public:
	reserveExtension(database *mdb ,QWidget *parent = 0);
	~reserveExtension(void);
	void updatePage();

private:

	QGroupBox *searchbox;
	QGroupBox *resultbox;
	QVBoxLayout *mainvlay;
	QLabel *idcode_lbl;
	QLabel *reserveid_lbl;
	QLineEdit *idcode_line;
	QLineEdit *reserveid_line;
	QPushButton *searchbtn;
	QHBoxLayout *tophlay;
	QHBoxLayout *downhlay;
	QHBoxLayout *downdownhlay;
	QMessageBox *msgBox;

	QVBoxLayout *vblay;

	QPushButton *changebtn;
	QDateEdit *endtime;
	QLabel *endtime_lbl;

	QTableView *table;

	
	database *db;
	QDate endWant2stay;
public slots:
	void showTable();
	void showMessage();


};
