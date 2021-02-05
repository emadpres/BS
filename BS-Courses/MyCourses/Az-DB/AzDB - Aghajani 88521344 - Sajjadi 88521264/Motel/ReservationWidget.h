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
#include <QCheckBox>
#include <QEvent>

class ReservationWidget : public QWidget
{
	Q_OBJECT
private:
	database *db;
public:
	// We use below function to handle button RollOver
	bool eventFilter(QObject *obj, QEvent *event);

	QTableView *table;
	QVBoxLayout *mainLayout;
	QGroupBox *topBox , *middleBox, *middle2Box, *resultBox;
	QPushButton *searchPassengerBtn, *searchPassengerReservatonsBtn, *updateRoomBtn, *searchRoomBtn, *reserveBtn;
	QDateEdit *serachStartDate, *serachEndDate;
	QVBoxLayout *resultLayout;
	QCheckBox *startDateEnable,*endDateEnable;

	QLineEdit *fname,*lname,*tel,*ID, *healthStatus ;
	QComboBox *sex;

	QLineEdit *roomNumber, *roomType, *roomStatus;
	QComboBox *isFree;

	QDateEdit *DateStart;
	QLineEdit *duration;
	//QLabel *labelType ,*labelBed ,*labelStart,*labelEnd ,*labelTable;
	//QLineEdit *LineName , *LineFamily , *LineId , *LineTell;
	//QComboBox *comboType;
	//QSpinBox  *spinBed;
	//QDateEdit *DateStart;
	

	ReservationWidget( database *mdb , QWidget *parent = 0   ) ;
	~ReservationWidget(void);
	void updatePage();
	QString CreateReservationsHistorySearchQuery();
	QString CreatePssangerSearchQuery();

	public slots:
		void showResult();
		void reserve();
		//void search();
		void fillTransCB();
		void searchReservations();
		void updateRoom();
		void searchRoom();
		void updateDateIndicators();
		void searchPassenger();
		void ClearStyleSheets();
		void HighlightSearchPassengerFields();
		void HighlightSearchReservationHistoryFields();
		void HighlightReserveFields();
		void HighlightSearchRoomFields();
		void HighlightUpdateRoomFields();
};
