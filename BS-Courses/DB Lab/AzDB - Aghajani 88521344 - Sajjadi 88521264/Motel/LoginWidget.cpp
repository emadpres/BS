#include "LoginWidget.h"
#include "motelwidget.h"

#include <QVBoxLayout>

#include <QSqlQuery>
#include <QSqlError>
#include <QPushButton>
#include <QComboBox>

LoginWidget::LoginWidget(QWidget *parent)
{
	db =  new database();

	mainLayout =  new QVBoxLayout(this);
	this->setLayout(mainLayout);

	cb_users = new QComboBox();
	mainLayout->addWidget(cb_users );
	fillUsers();

	login_bt = new QPushButton("ورود");
	mainLayout->addWidget(login_bt);
	connect(login_bt,SIGNAL(clicked()),this,SLOT(Login()));

	
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::fillUsers()
{
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec("select * from staff");
	if(ok)
	{
		while( queryExecutor.next())
		{
			cb_users->addItem( queryExecutor.value(1).toString() +" "+ queryExecutor.value(2).toString());
		}
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

void LoginWidget::Login()
{
	MotelWidget *m = new MotelWidget(NULL,cb_users->currentIndex());
	delete cb_users;
	delete login_bt;
	QLabel *lb = new QLabel("اجرای موفق");
	mainLayout->addWidget(lb); 
	m->show();
	this->close();
}
