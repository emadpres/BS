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

class TransportationWidget : public QWidget
{
	Q_OBJECT
private:
	database *db;
public:
	QTableView *table;
	QVBoxLayout *mainLayout;
	QGroupBox *topBox , *resultBox;
	QPushButton *searchBtn, *registerBtn;
	
	QVBoxLayout *resultLayout;

	QLineEdit *roomID,*destination, *price ;
	QComboBox *trans_cb;
	QVector<int> trans_code;
	//QLabel *labelType ,*labelBed ,*labelStart,*labelEnd ,*labelTable;
	//QLineEdit *LineName , *LineFamily , *LineId , *LineTell;
	//QComboBox *comboType;
	//QSpinBox  *spinBed;
	//QDateEdit *DateStart;
	

	TransportationWidget( database *mdb , QWidget *parent = 0   ) ;
	~TransportationWidget(void);
	void updatePage();

	public slots:
		void showResult();
		void registerTrans();
		void search();
		void fillTransCB();
};
