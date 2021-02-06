#ifndef MOTELWIDGET_H
#define MOTELWIDGET_H

//#include <QtCore/qcoreapplication.h>
#include <QWidget>
#include "database.h"
#include "ReservationWidget.h"
#include "TransportationWidget.h"
#include "StaffWork.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>


class MotelWidget : public QWidget
{
	Q_OBJECT

public:
	MotelWidget(QWidget *parent = 0, int userID=-1);
	~MotelWidget();
	int currentUserID;
	public slots:
		void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
	//Ui::MainWindowClass ui;

	void createIcons();
	QListWidget *contentsWidget;
	QStackedWidget *pagesWidget;
	database *db;

	ReservationWidget *reservePage;
	TransportationWidget *TransportationPage;
	StaffWork *StaffWorkPage;
};

#endif // MOTELWIDGET_H
