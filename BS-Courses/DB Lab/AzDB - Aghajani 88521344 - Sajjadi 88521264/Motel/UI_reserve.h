#pragma once
#include "database.h"
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QDateEdit>
#include <QComboBox>
#include <QSpinBox>

class UI_reserve : public QWidget
{
	Q_OBJECT
private:
	database *db;
public:

	QVBoxLayout *mainLayout;
	QGroupBox *roomInf , *passengerInf;
	QGridLayout *roomLayout  , *passengerLayout ;

	QPushButton *searchBtn ,*okBtn;
	QLabel *labelType ,*labelBed ,*labelStart,*labelEnd ,*labelTable;
	QLabel *labelName , *labelFamily , *labelIDCode , *labelTell;
	QComboBox *comboType;
	QSpinBox  *spinBed;
	QDateEdit *DateStart , *DateEnd;
	QLineEdit *LineName , *LineFamily , *LineId , *LineTell;
	QTableView *table;

	UI_reserve( database *mdb , QWidget *parent = 0   ) ;
	~UI_reserve(void);
	void updatePage();

	public slots:
		void showRoom();
		void reserveRoom();
};
