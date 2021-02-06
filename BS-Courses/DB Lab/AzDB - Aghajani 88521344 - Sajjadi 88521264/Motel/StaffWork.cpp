#include "StaffWork.h"
#include <QSqlQuery>
#include <QSqlError>

StaffWork::StaffWork(database *mdb , QWidget *parent  ) 
{
	db = mdb;
	table = new QTableView(this);
	table->setLayoutDirection(Qt::RightToLeft);

	mainLayout =  new QHBoxLayout(this);
	rightBox = new QGroupBox("مشخصات");
	leftBox = new QGroupBox("Result");
	mainLayout->addWidget(leftBox);
	mainLayout->addWidget(rightBox);

	////////////////////////////////////////////////	Result
	QVBoxLayout *resultLayout = new QVBoxLayout();
	leftBox->setLayout(resultLayout);
	resultLayout->addWidget(table);
	table->setModel(db->model);
	////////////////////////////////////////////////

	////////////////////////////////////////////////	Top
	QVBoxLayout *topLayout = new QVBoxLayout();
	rightBox->setLayout(topLayout);
	
	QLabel *staff_lbl = new QLabel("کارمند");
	topLayout->addWidget(staff_lbl);
	staff_cb= new QComboBox();
	topLayout->addWidget(staff_cb);

	fillStaffCB();

	inBtn= new QPushButton("ثبت ورود");
	topLayout->addWidget(inBtn);
	outBtn= new QPushButton("ثبت خروج");
	topLayout->addWidget(outBtn);

	connect(inBtn,SIGNAL(clicked()),this,SLOT(enterStaff()));
	connect(outBtn,SIGNAL(clicked()),this,SLOT(exitStaff()));
	////////////////////////////////////////////////
	/*QDate date;
	date = date.currentDate();
	DateStart->setDisplayFormat("dd-MM-yyyy");
	DateStart->setDate(date);*/

	/*QStringList comboList;
	comboList << "normal" << "master"<<"suite"<<"business class room"<<"penthouse";
	comboType->addItems(comboList);*/
}

StaffWork::~StaffWork(void)
{
}

void StaffWork::showResult()
{
	QString query("select staff.staff_ID,staff.fname,staff.lname, event.tuzihat, work.time \
					from work,staff,event \
					where event.type=work.type AND work.staff_ID=staff.staff_ID ORDER BY work.time DESC ");

	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		db->model->setQuery(queryExecutor);
		db->model->setHeaderData(0, Qt::Horizontal,"کد پرسنلی");
		db->model->setHeaderData(1, Qt::Horizontal,"نام");
		db->model->setHeaderData(2, Qt::Horizontal,"نام خانوادگی");
		db->model->setHeaderData(3, Qt::Horizontal,"رویداد");
		db->model->setHeaderData(4, Qt::Horizontal,"زمان");
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

//void StaffWork::showResult()
//{
//	QqueryExecutor queryExecutor(db->db);
//	
//	QString queryString ("CALL ee ('Emad')");
//
//
//	bool ok = queryExecutor.exec(queryString);
//
//	int a = queryExecutor.size() ;
//	if(ok)
//	{
//		db->model->setQuery(queryExecutor);
//	}
//	else
//	{
//		QSqlError err ;
//		err = queryExecutor.lastError();
//		QString s = queryExecutor.lastError().text();
//		db->model->clear();
//	}
//}
		
//void StaffWork::registerTrans()
//{
//	
//	if(trans_cb->currentText()=="" || roomID->text()=="" || destination->text()=="")
//	{
//		db->model->clear();
//		return;
//	}
//
//	QqueryExecutor queryExecutor(db->db);
//	QString queryString = "CALL registerTransportation (";
//	int a = trans_code[trans_cb->currentIndex()-1] ;
//	queryString += QString(QString::number(a)+","+roomID->text()+",'"+destination->text()+"'");
//	queryString += ")";
//
//	queryExecutor.prepare(queryString);
//	
//	bool ok = queryExecutor.exec();
//	if(ok)
//		db->model->setQuery(queryExecutor);
//	else
//	{
//		QSqlError err ;
//		err = queryExecutor.lastError();
//		QString s = queryExecutor.lastError().text();
//		db->model->clear();
//	}
//}

void StaffWork::updatePage()
{
	showResult();
}

//void StaffWork::search()
//{
//	db->model->clear();
//	QString query ("SELECT * FROM transportation where 1 ");
//	if(trans_cb->currentText()!="")
//	{
//		query += " AND code=";
//		int a = trans_code[trans_cb->currentIndex()-1] ;
//		query += QString::number(a);
//	}
//	if(roomID->text()!="")
//	{
//		query += " AND roomNumber=";
//		query += roomID->text() ;
//	}
//
//	if(destination->text()!="")
//	{
//		query += " AND destination='";
//		query += destination->text() ;
//		query += "'";
//	}
//
//	QqueryExecutor queryExecutor(db->db);
//	bool ok = queryExecutor.exec(query);
//	if(ok)
//		db->model->setQuery(queryExecutor);
//	else
//	{
//		QSqlError err ;
//		err = queryExecutor.lastError();
//		QString s = queryExecutor.lastError().text();
//		db->model->clear();
//	}
//}

void StaffWork::fillStaffCB()
{
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec("select * from staff");
	if(ok)
	{
		staff_cb->addItem("");
		while( queryExecutor.next())
		{
			staff_cb->addItem( queryExecutor.value(1).toString());
			staff_code.append(queryExecutor.value(0).toInt());
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

void StaffWork::enterStaff()
{
	if(staff_cb->currentText()=="") return;
	QString query("INSERT INTO work (staff_ID,type) VALUES(");
	query += QString::number(staff_code[staff_cb->currentIndex()-1]);
	query += ",1)";
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		showResult();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

void StaffWork::exitStaff()
{
	if(staff_cb->currentText()=="") return;
	QString query("INSERT INTO work (staff_ID,type) VALUES(");
	query += QString::number(staff_code[staff_cb->currentIndex()-1]);
	query += ",2)";
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		showResult();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}
