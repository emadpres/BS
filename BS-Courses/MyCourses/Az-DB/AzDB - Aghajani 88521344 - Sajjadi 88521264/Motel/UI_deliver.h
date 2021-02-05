#pragma once
//#include <QtGui/QWidget>
//#include <QtCore>
#include "database.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QDateEdit>

class UI_deliver : public QWidget
{
	Q_OBJECT

private:
	database *db;

public:
	QPushButton* search;
	QVBoxLayout* vbox;
	//
	QLabel* reserveIdLable;
	QLabel* idCodeLable;

	//mosafer
	QLabel* nameLable;
	QLabel* familyLable;
	QLabel* passengerIdCodeLable;
	QLabel* tellLable;

	//
	QLineEdit* reserveIdLineEdit;
	QLineEdit* idCodeLineEdit;
	//mosafer
	QLineEdit* nameLineEdit;
	QLineEdit* familyLineEdit;
	QLineEdit* passengerIdCodeLineEdit;
	QLineEdit* tellLineEdit;

	//
	QGridLayout *grid1;
	QGroupBox *group1;

	QGridLayout *grid2;
	QGroupBox *group2;

	int qReserveId;
	QString qCodeID;

	UI_deliver(database *mdb, QWidget *parent = 0) ;
	~UI_deliver(void);
	void updatePage();

	public slots:
		void save();

};
