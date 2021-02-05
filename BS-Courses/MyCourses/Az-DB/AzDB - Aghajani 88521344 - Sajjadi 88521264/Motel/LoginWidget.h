#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

//#include <QtCore/qcoreapplication.h>
#include <QWidget>
#include "database.h"
class QComboBox;
class databse;
class QPushButton;
class QVBoxLayout ;

class LoginWidget : public QWidget
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = 0);
	~LoginWidget();
	QVBoxLayout *mainLayout;

	QComboBox* cb_users;
	QPushButton* login_bt;
	void fillUsers();
	database *db;

public slots:
		void Login();

};

#endif // LOGINWIDGET_H
