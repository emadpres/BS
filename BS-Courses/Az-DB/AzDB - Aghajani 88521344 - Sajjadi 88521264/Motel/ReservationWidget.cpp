#include "ReservationWidget.h"
#include <QSqlQuery>
#include <QSqlError>
#include "motelwidget.h"

ReservationWidget::ReservationWidget(database *mdb , QWidget *parent  ) 
{

	db = mdb;
	table = new QTableView(this);
	table->setLayoutDirection(Qt::RightToLeft);
	
	mainLayout =  new QVBoxLayout(this);
	topBox = new QGroupBox("مسافر");
	middleBox = new QGroupBox("اتاق ها");
	middle2Box = new QGroupBox("رزرواسیون");
	resultBox = new QGroupBox("نتیجه");
	mainLayout->addWidget(topBox);
	mainLayout->addWidget(middleBox);
	mainLayout->addWidget(middle2Box);
	mainLayout->addWidget(resultBox);

	QDate date;
	date = date.currentDate();

	////////////////////////////////////////////////	Result
	resultLayout = new QVBoxLayout();
	resultBox->setLayout(resultLayout);
	resultLayout->addWidget(table);
	table->setModel(db->model);
	////////////////////////////////////////////////

	////////////////////////////////////////////////	Top
	QVBoxLayout *topLayout = new QVBoxLayout();
	topBox->setLayout(topLayout);
	
	QHBoxLayout *passangerLayout1 = new QHBoxLayout();
	topLayout->addLayout(passangerLayout1);
	passangerLayout1->setDirection(QBoxLayout::RightToLeft);
	
	QHBoxLayout *passangerLayout2 = new QHBoxLayout();
	topLayout->addLayout(passangerLayout2);
	passangerLayout2->setDirection(QBoxLayout::RightToLeft);

	QHBoxLayout *passangerLayout3 = new QHBoxLayout();
	topLayout->addLayout(passangerLayout3);
	passangerLayout3->setDirection(QBoxLayout::RightToLeft);
		
	QLabel *fname_lbl = new QLabel("نام",this);
	passangerLayout1->addWidget(fname_lbl);
	fname = new QLineEdit("عماد",this);
	passangerLayout1->addWidget(fname);

	QLabel *lname_lbl = new QLabel("نام خانوادگی");
	passangerLayout1->addWidget(lname_lbl);
	lname = new QLineEdit("آقاجانی");
	passangerLayout1->addWidget(lname);

	QLabel *tel_lbl = new QLabel("تلفن");
	passangerLayout1->addWidget(tel_lbl);
	tel = new QLineEdit("4499");
	passangerLayout1->addWidget(tel);

	QLabel *ID_lbl = new QLabel("شماره ملی");
	passangerLayout1->addWidget(ID_lbl);
	ID = new QLineEdit("1234");
	passangerLayout1->addWidget(ID);

	sex = new QComboBox();
	sex->addItem("");
	sex->addItem("مرد");
	sex->addItem("زن");
	passangerLayout1->addWidget(sex);

	QLabel *healthStatus_lbl = new QLabel("وضعیت سلامت");
	passangerLayout1->addWidget(healthStatus_lbl);
	healthStatus = new QLineEdit();
	healthStatus->setDisabled(true);
	healthStatus->setText("سالم");
	passangerLayout1->addWidget(healthStatus);

	startDateEnable = new QCheckBox();
	passangerLayout2->addWidget(startDateEnable);
	serachStartDate = new QDateEdit();
	serachStartDate->setDisplayFormat("yyyy-MM-dd");
	serachStartDate->setDate(date);
	passangerLayout2->addWidget(serachStartDate);

	endDateEnable = new QCheckBox();
	passangerLayout2->addWidget(endDateEnable);
	serachEndDate = new QDateEdit();
	serachEndDate->setDisplayFormat("yyyy-MM-dd");
	serachEndDate->setDate(date);
	passangerLayout2->addWidget(serachEndDate);

	startDateEnable->setChecked(false);
	endDateEnable->setChecked(false);
	updateDateIndicators();
	connect(startDateEnable,SIGNAL(stateChanged(int)),this,SLOT(updateDateIndicators()));
	connect(endDateEnable,SIGNAL(stateChanged(int)),this,SLOT(updateDateIndicators()));

	searchPassengerBtn = new QPushButton("جستجوی مسافران");
	searchPassengerReservatonsBtn = new QPushButton("جستجوی سابقه رزروها");
	passangerLayout3->addWidget(searchPassengerBtn);
	passangerLayout3->addWidget(searchPassengerReservatonsBtn);
	connect(searchPassengerBtn,SIGNAL(clicked()),this,SLOT(searchPassenger()));
	connect(searchPassengerReservatonsBtn,SIGNAL(clicked()),this,SLOT(searchReservations()));
	////////////////////////////////////////////////


	//////////////////////////////////////////////// Middle
	QVBoxLayout *middleLayout = new QVBoxLayout();
	middleBox->setLayout(middleLayout);
	QHBoxLayout *roomsLayout1 = new QHBoxLayout();
	middleLayout->addLayout(roomsLayout1);
	QHBoxLayout *roomsLayout2 = new QHBoxLayout();
	middleLayout->addLayout(roomsLayout2);
	QHBoxLayout *roomsLayout3 = new QHBoxLayout();
	middleLayout->addLayout(roomsLayout3);
	roomsLayout1->setDirection(QBoxLayout::RightToLeft);
	roomsLayout2->setDirection(QBoxLayout::RightToLeft);
	roomsLayout3->setDirection(QBoxLayout::RightToLeft);


	QLabel *roomNumber_lbl = new QLabel("شماره اتاق");
	roomsLayout1->addWidget(roomNumber_lbl);
	roomNumber = new QLineEdit();
	roomsLayout1->addWidget(roomNumber);

	QLabel *type_lbl = new QLabel("تعداد تخت");
	roomsLayout1->addWidget(type_lbl );
	roomType = new QLineEdit();
	roomsLayout1->addWidget(roomType);

	QLabel *empty_lbl = new QLabel("وضعیت");
	isFree = new QComboBox();
	isFree->addItem("");
	isFree->addItem("پر");
	isFree->addItem("خالی");
	roomsLayout2->addWidget(empty_lbl);
	roomsLayout2->addWidget(isFree);

	QLabel *status_lbl = new QLabel("توضیحات");
	roomsLayout2->addWidget(status_lbl );
	roomStatus = new QLineEdit();
	roomsLayout2->addWidget(roomStatus);

	updateRoomBtn = new QPushButton("بروزرسانی وضعیت اتاق");
	roomsLayout2->addWidget(updateRoomBtn);
	connect(updateRoomBtn,SIGNAL(clicked()),this,SLOT(updateRoom()));

	searchRoomBtn = new QPushButton("جستجو اتاق");
	roomsLayout3->addWidget(searchRoomBtn);

	connect(searchRoomBtn,SIGNAL(clicked()),this,SLOT(searchRoom()));
	////////////////////////////////////////////////

	//////////////////////////////////////////////// Middle
	QVBoxLayout *middle2Layout = new QVBoxLayout();
	middle2Box->setLayout(middle2Layout);
	QHBoxLayout *reserveLayout1 = new QHBoxLayout();
	middle2Layout->addLayout(reserveLayout1);
	QHBoxLayout *reserveLayout2 = new QHBoxLayout();
	middle2Layout->addLayout(reserveLayout2);

	QLabel *dateStart_lbl = new QLabel("شروع");
	reserveLayout1->addWidget(dateStart_lbl );
	DateStart =  new QDateEdit();
	DateStart->setDisplayFormat("yyyy-MM-dd");
	reserveLayout1->addWidget(DateStart);
	DateStart->setDate(date);

	QLabel *duration_lbl = new QLabel("مدت");
	reserveLayout1->addWidget(duration_lbl );
	duration =  new QLineEdit("5");
	reserveLayout1->addWidget(duration);
	

	reserveBtn = new QPushButton("ثبت");
	reserveLayout1->addWidget(reserveBtn);

	connect(reserveBtn,SIGNAL(clicked()),this,SLOT(reserve()));
	
	ClearStyleSheets();
	searchPassengerBtn->installEventFilter(this);
	searchPassengerReservatonsBtn->installEventFilter(this);
	updateRoomBtn->installEventFilter(this);
	searchRoomBtn->installEventFilter(this);
	reserveBtn->installEventFilter(this);
	////////////////////////////////////////////////
	/*QDate date;
	date = date.currentDate();
	DateStart->setDisplayFormat("dd-MM-yyyy");
	DateStart->setDate(date);*/

	/*QStringList comboList;
	comboList << "normal" << "master"<<"suite"<<"business class room"<<"penthouse";
	comboType->addItems(comboList);*/
}
bool ReservationWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Enter) {
		if (obj == (QObject*)searchPassengerBtn)
			HighlightSearchPassengerFields();
		else if (obj == (QObject*)searchPassengerReservatonsBtn)
			HighlightSearchReservationHistoryFields();
		else if (obj == (QObject*)updateRoomBtn)
			HighlightUpdateRoomFields();
		else if (obj == (QObject*)searchRoomBtn)
			HighlightSearchRoomFields();
		else if (obj == (QObject*)reserveBtn)
			HighlightReserveFields();
		return true;
	}
	else if (event->type() == QEvent::Leave) {
		ClearStyleSheets();
		return true;
	}
	else {
		// pass the event on to the parent class
		return QWidget::eventFilter(obj, event);
	}
}

ReservationWidget::~ReservationWidget(void)
{
}

void ReservationWidget::showResult()
{
	QSqlQuery queryExecutor(db->db);
	bool at = db->db.isOpen();
	QString queryString ("Select ' ? ' from passenger");
	queryExecutor.prepare(queryString);

	queryExecutor.addBindValue(QString("Emad"));

	bool ok = queryExecutor.exec();

	int a = queryExecutor.size() ;
	if(ok)
	{
		db->model->setQuery(queryExecutor);
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}
		
void ReservationWidget::reserve()
{
	
	if( fname->text()=="" || lname->text()=="" || tel->text()=="" || ID->text()=="" || sex->currentText()=="")
	{
		QMessageBox *err = new QMessageBox(QMessageBox::Information,"خطا در ثبت","اطلاعات مسافر را کامل نمایید.");
		err->setStandardButtons(QMessageBox::Ok);
		db->model->clear();
		err->exec();
		return;
	}

	if(roomNumber->text()=="" && table->currentIndex().data().toInt()==0 )
	{
		QMessageBox *err = new QMessageBox(QMessageBox::Information,"خطا در ثبت","لطفا یکی از اتاق ها را انتخاب نمایید!");
		err->setStandardButtons(QMessageBox::Ok);
		db->model->clear();
		err->exec();
		return;
	}

	if(duration->text()=="")
	{
		QMessageBox *err = new QMessageBox(QMessageBox::Information,"خطا در ثبت","مدت زمان را وارد نمایید!");
		err->setStandardButtons(QMessageBox::Ok);
		db->model->clear();
		err->exec();
		return;
	}

	int rNumber = -1;
	if(roomNumber->text()!="")
		rNumber = roomNumber->text().toInt();
	else
		rNumber = table->currentIndex().data().toInt() ;

	QString queryString = "CALL reserve ('";
	// Passenger
	queryString += QString( fname->text());	// fname
	queryString += QString( "' , '");
	queryString += lname->text();			//lname
	queryString += QString("','");
	queryString += QString( tel->text() );	//tel
	queryString += QString("','");
	queryString += QString( ID->text());
	queryString += QString("'");
	if(sex->currentIndex()==1)
		queryString +=  QString( ",0,");
	else
		queryString +=  QString( ",1,");
	queryString += QString("'");
	queryString += healthStatus->text();
	queryString += QString("',");
	// Room

	int currentUserID =((MotelWidget*)(parent()->parent()))->currentUserID ;
	queryString += QString( QString::number(rNumber)+",'"+DateStart->text()+"',"+duration->text()+","+QString::number(currentUserID));
	queryString += ")";

	QString s = DateStart->text();
	

	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(queryString);
	if(ok)
	{
		db->model->setQuery(queryExecutor);
		searchReservations();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();

		QMessageBox *errBox = new QMessageBox(QMessageBox::Information,"خطا در ثبت","تکراری بودن شماره ملی یا خطای تکرار نوع 2!");
		errBox->setStandardButtons(QMessageBox::Ok);
		errBox->exec();
		return;
	}
}

void ReservationWidget::searchPassenger()
{
	HighlightSearchPassengerFields();

	db->model->clear();
	QString query  = CreatePssangerSearchQuery();
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);

	if(ok)
	{
		db->model->setQuery(queryExecutor);
		db->model->setHeaderData(0, Qt::Horizontal,"نام");
		db->model->setHeaderData(1, Qt::Horizontal,"نام خانوادگی");
		db->model->setHeaderData(2, Qt::Horizontal,"تلفن");
		db->model->setHeaderData(3, Qt::Horizontal,"شماره ملی");
		db->model->setHeaderData(4, Qt::Horizontal,"جنسیت");
		db->model->setHeaderData(5, Qt::Horizontal,"وضیت سلامتی");


	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}

}

void ReservationWidget::searchReservations()
{
	HighlightSearchReservationHistoryFields();

	db->model->clear();
	QString query  = CreateReservationsHistorySearchQuery();
	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);

	if(ok)
	{
		db->model->clear();
		db->model->setQuery(queryExecutor);
		db->model->setHeaderData(0, Qt::Horizontal,"نام");
		db->model->setHeaderData(1, Qt::Horizontal,"نام خانوادگی");
		db->model->setHeaderData(2, Qt::Horizontal,"شماره ملی");
		db->model->setHeaderData(3, Qt::Horizontal,"شماره اتاق");
		db->model->setHeaderData(4, Qt::Horizontal,"تاریخ اقامت");
		db->model->setHeaderData(5, Qt::Horizontal,"مدت اقامت");
		db->model->setHeaderData(6, Qt::Horizontal,"متصدی");

		
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}


void ReservationWidget::updatePage()
{
	searchRoom();
}


void ReservationWidget::searchRoom()
{
	HighlightSearchRoomFields();

	db->model->clear();
	QString query ("SELECT rooms.roomNumber,rooms.type,roomfree.tuzihat,rooms.status FROM rooms,roomfree where roomfree.type=rooms.isFree ");
	if(roomNumber->text()!="")
	{
		query += " AND roomNumber=";
		query += roomNumber->text();
	}
	if(roomType->text()!="")
	{
		query += " AND rooms.type=";
		query += roomType->text() ;
	}

	if(isFree->currentText() !="")
	{
		query += " AND isFree=";
		if(isFree->currentIndex()==1)
			query += QString::number(0) ;
		else
			query += QString::number(1) ;
	}

	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		db->model->setQuery(queryExecutor);
		db->model->setHeaderData(0, Qt::Horizontal,"شماره اتاق");
		db->model->setHeaderData(1, Qt::Horizontal,"تعداد تخت");
		db->model->setHeaderData(2, Qt::Horizontal,"خالی بودن");
		db->model->setHeaderData(3, Qt::Horizontal,"توضیحات اتاق");
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

void ReservationWidget::fillTransCB()
{
	/*QqueryExecutor queryExecutor(db->db);
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
	}*/
}

void ReservationWidget::updateRoom()
{

	HighlightUpdateRoomFields();

	if(roomNumber->text()=="")
		return;
	db->model->clear();
	QString query ="UPDATE rooms SET ";
	if(isFree->currentIndex()>0)
		query += (" isFree="+QString::number(isFree->currentIndex()-1)+",");
	query += ("status='"+roomStatus->text()+"' where roomNumber="+roomNumber->text());

	QSqlQuery queryExecutor(db->db);
	bool ok = queryExecutor.exec(query);
	if(ok)
	{
		roomNumber->setText("");
		isFree->setCurrentIndex(0);
		searchRoom();
	}
	else
	{
		QSqlError err ;
		err = queryExecutor.lastError();
		QString s = queryExecutor.lastError().text();
		db->model->clear();
	}
}

QString ReservationWidget::CreateReservationsHistorySearchQuery()
{
	QString query = "SELECT passenger.fname,passenger.lname,passenger.ID \
							,roomNumber,startDate,duration,staff.lName \
					FROM passenger,reservation,staff \
					WHERE reservation.staff_ID=staff.staff_ID AND \
							passenger.ID=passenger ";
	if(fname->text()!="")
	{
		query += " AND passenger.fname='";
		query += fname->text();
		query += "'";
	}

	if(lname->text()!="")
	{
		query += " AND passenger.lname='";
		query += lname->text();
		query += "'";
	}

	if(tel->text()!="")
	{
		query += " AND passenger.tel='";
		query += tel->text();
		query += "'";
	}

	if(ID->text()!="")
	{
		query += " AND passenger.ID='";
		query += ID->text();
		query += "'";
	}

	if(sex->currentText() !="")
	{
		query += " AND passenger.sex=";
		if(sex->currentIndex()==1)
			query += QString::number(0) ;
		else
			query += QString::number(1) ;
	}
	
	if(roomNumber->text() != "")
	{
		query += " AND reservation.roomNumber =";
		query += roomNumber->text() ;
	}


	if(startDateEnable->isChecked())
	{
		query += " AND reservation.startDate >= '";
		query += serachStartDate->text() ;
		query += "' " ;
	}

	if(endDateEnable->isChecked())
	{
		// MySQL Date Arithmetic
		//	Where reservation.startDate >= ADDDATE('2014-05-22', 4);
		query += " AND ADDDATE(reservation.startDate,";
		query += duration->text();
		query += ") <='";
		query += serachEndDate->text() ;
		query += "' " ;
	}

	

	return query;
}

QString ReservationWidget::CreatePssangerSearchQuery()
{
	QString query = "SELECT * FROM passenger WHERE 1 ";
	if(fname->text()!="")
	{
		query += " AND passenger.fname='";
		query += fname->text();
		query += "'";
	}

	if(lname->text()!="")
	{
		query += " AND passenger.lname='";
		query += lname->text();
		query += "'";
	}

	if(tel->text()!="")
	{
		query += " AND passenger.tel='";
		query += tel->text();
		query += "'";
	}

	if(ID->text()!="")
	{
		query += " AND passenger.ID='";
		query += ID->text();
		query += "'";
	}

	if(sex->currentText() !="")
	{
		query += " AND passenger.sex=";
		if(sex->currentIndex()==1)
			query += QString::number(0) ;
		else
			query += QString::number(1) ;
	}

	return query;

}

void ReservationWidget::updateDateIndicators()
{
	if(startDateEnable->isChecked())
		serachStartDate->setEnabled(true);
	else
		serachStartDate->setEnabled(false);

	if(endDateEnable->isChecked())
		serachEndDate->setEnabled(true);
	else
		serachEndDate->setEnabled(false);
}

void ReservationWidget::ClearStyleSheets()
{
	fname->setStyleSheet("");
	lname->setStyleSheet("");
	tel->setStyleSheet("");
	ID->setStyleSheet("");
	sex->setStyleSheet("");
	healthStatus->setStyleSheet("");
	serachStartDate->setStyleSheet("");
	serachEndDate->setStyleSheet("");

	roomNumber->setStyleSheet("");
	roomType->setStyleSheet("");
	isFree->setStyleSheet("");
	roomStatus->setStyleSheet("");

	DateStart->setStyleSheet("");
	duration->setStyleSheet("");
}

void ReservationWidget::HighlightSearchPassengerFields()
{
	ClearStyleSheets();

	fname->setStyleSheet("background: yellow");
	lname->setStyleSheet("background: yellow");
	tel->setStyleSheet("background: yellow");
	ID->setStyleSheet("background: yellow");
	sex->setStyleSheet("background: yellow");
	healthStatus->setStyleSheet("background: yellow");
}

void ReservationWidget::HighlightSearchReservationHistoryFields()
{
	ClearStyleSheets();

	fname->setStyleSheet("background: yellow");
	lname->setStyleSheet("background: yellow");
	tel->setStyleSheet("background: yellow");
	ID->setStyleSheet("background: yellow");
	sex->setStyleSheet("background: yellow");
	healthStatus->setStyleSheet("background: yellow");
	serachStartDate->setStyleSheet("background: yellow");
	serachEndDate->setStyleSheet("background: yellow");
	roomNumber->setStyleSheet("background: yellow");

}

void ReservationWidget::HighlightReserveFields()
{
	ClearStyleSheets();

	HighlightSearchPassengerFields();
	roomNumber->setStyleSheet("background: yellow");
	DateStart->setStyleSheet("background: yellow");
	duration->setStyleSheet("background: yellow");
}

void ReservationWidget::HighlightSearchRoomFields()
{
	ClearStyleSheets();

	roomNumber->setStyleSheet("background: yellow");
	roomType->setStyleSheet("background: yellow");
	isFree->setStyleSheet("background: yellow");	

}

void ReservationWidget::HighlightUpdateRoomFields()
{
	ClearStyleSheets();
	roomNumber->setStyleSheet("background: yellow");
	isFree->setStyleSheet("background: yellow");
	roomStatus->setStyleSheet("background: yellow");
}


