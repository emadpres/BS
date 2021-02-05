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

class StaffWork : public QWidget
{
	Q_OBJECT
private:
	database *db;
public:
	QTableView *table;
	QHBoxLayout *mainLayout;
	QGroupBox *leftBox , *rightBox;
	QPushButton *inBtn, *outBtn;
	
	QComboBox *staff_cb;
	QVector<int> staff_code;
	//QLabel *labelType ,*labelBed ,*labelStart,*labelEnd ,*labelTable;
	//QLineEdit *LineName , *LineFamily , *LineId , *LineTell;
	//QComboBox *comboType;
	//QSpinBox  *spinBed;
	//QDateEdit *DateStart;
	

	StaffWork( database *mdb , QWidget *parent = 0   ) ;
	~StaffWork(void);
	void updatePage();

	public slots:
		void showResult();
		void fillStaffCB();
		void enterStaff();
		void exitStaff();
};
