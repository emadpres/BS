#include "TransportationWidget.h"
#include <QSqlQuery>
#include <QSqlError>

TransportationWidget::TransportationWidget(database *mdb , QWidget *parent  ) 
{
	db = mdb;
	table = new QTableView(this);
	table->setLayoutDirection(Qt::RightToLeft);
	mainLayout =  new QVBoxLayout(this);
	topBox = new QGroupBox("Top");
	resultBox = new QGroupBox("Result");
	mainLayout->addWidget(topBox);
	mainLayout->addWidget(resultBox);

	////////////////////////////////////////////////	Result
	resultLayout = new QVBoxLayout();
	resultBox->setLayout(resultLayout);
	resultLayout->addWidget(table);
	table->setModel(db->model);
	////////////////////////////////////////////////

	////////////////////////////////////////////////	Top
	QHBoxLayout *topLayout = new QHBoxLayout();
	topBox->setLayout(topLayout);
	topLayout->setDirection(QBoxLayout::RightToLeft);

	QLabel *roomID_lbl = new QLabel("شماره اتاق");
	topLayout->addWidget(roomID_lbl);
	roomID = new QLineEdit();
	topLayout->addWidget(roomID);

	QLabel *transCode_lbl = new QLabel("کد آژانس");
	topLayout->addWidget(transCode_lbl);
	trans_cb = new QComboBox();
	topLayout->addWidget(trans_cb);
	fillTransCB();
	
	QLabel *destination_lbl = new QLabel("مقصد");
	topLayout->addWidget(destination_lbl);
	destination = new QLineEdit();
	topLayout->addWidget(destination);

	QLabel *price_lbl = new QLabel("مبلغ");
	topLayout->addWidget(price_lbl);
	price = new QLineEdit();
	topLayout->addWidget(price);

	registerBtn = new QPushButton("ثبت");
	topLayout->addWidget(registerBtn);
	searchBtn = new QPushButton("جستجو");
	topLayout->addWidget(searchBtn);

	connect(registerBtn,SIGNAL(clicked()),this,SLOT(registerTrans()));
	connect(searchBtn,SIGNAL(clicked()),this,SLOT(search()));
	////////////////////////////////////////////////
	/*QDate date;
	date = date.currentDate();
	DateStart->setDisplayFormat("dd-MM-yyyy");
	DateStart->setDate(date);*/

	/*QStringList comboList;
	comboList << "normal" << "master"<<"suite"<<"business class room"<<"penthouse";
	comboType->addItems(comboList);*/
}

TransportationWidget::~TransportationWidget(void)
{
}

void TransportationWidget::showResult()
{
	QSqlQuery queryExecutor(db->db);
	
	QString queryString ("CALL ee ('Emad')");


	bool ok = queryExecutor.exec(queryString);

	int a = queryExecutor.size() ;
	if(ok)
	{
		db->model->clear();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}
		
void TransportationWidget::registerTrans()
{
	
	if(trans_cb->currentText()=="" || roomID->text()=="" || destination->text()=="" || price->text()=="")
	{
		db->model->clear();
		QMessageBox *errBox = new QMessageBox(QMessageBox::Information,"خطا در ثبت","اطلاعات را کامل وارد نمایید !");
		errBox->setStandardButtons(QMessageBox::Ok);
		db->model->clear();
		errBox->exec();
		return;
	}

	QSqlQuery queryExecutor(db->db);
	QString queryString = "CALL registerTransportation (";
	int a = trans_code[trans_cb->currentIndex()-1] ;
	queryString += QString(QString::number(a)+","+roomID->text()+",'"+destination->text()+"',");
	queryString += price->text();
	queryString += ")";

	queryExecutor.prepare(queryString);
	
	bool ok = queryExecutor.exec();
	if(ok)
	{
		db->model->setQuery(queryExecutor);
		search();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();

		QMessageBox *errBox = new QMessageBox(QMessageBox::Information,"خطا در ثبت","شماره اتاق ناموجود !");
		errBox->setStandardButtons(QMessageBox::Ok);
		db->model->clear();
		errBox->exec();
		return;
	}
}

void TransportationWidget::updatePage()
{
	search();
}

void TransportationWidget::search()
{
	db->model->clear();
	QString query ("SELECT * FROM transportation where 1 ");
	if(trans_cb->currentText()!="")
	{
		query += " AND code=";
		int a = trans_code[trans_cb->currentIndex()-1] ;
		query += QString::number(a);
	}
	if(roomID->text()!="")
	{
		query += " AND roomNumber=";
		query += roomID->text() ;
	}

	if(destination->text()!="")
	{
		query += " AND destination='";
		query += destination->text() ;
		query += "'";
	}

	if(price->text()!="")
	{
		query += " AND price=";
		query += price->text() ;
		//query += "'";
	}

	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		db->model->setQuery(queryExecutor);
		db->model->setHeaderData(0, Qt::Horizontal,"کد آژانس");
		db->model->setHeaderData(1, Qt::Horizontal,"شماره اتاق");
		db->model->setHeaderData(2, Qt::Horizontal,"تاریخ");
		db->model->setHeaderData(3, Qt::Horizontal,"مقصد");
		db->model->setHeaderData(4, Qt::Horizontal,"هزینه");
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

void TransportationWidget::fillTransCB()
{
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec("select * from transportation_agency");
	if(ok)
	{
		trans_cb->addItem("");
		while( queryExecutor.next())
		{
			trans_cb->addItem( queryExecutor.value(1).toString());
			trans_code.append(queryExecutor.value(0).toInt());
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
