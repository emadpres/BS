#include "UI_reserve.h"
//#include <QMessageBox>

UI_reserve::UI_reserve(database *mdb , QWidget *parent  ) 
{
	db = mdb;
	

	mainLayout =  new QVBoxLayout(this);
	//config roomlayout;
	roomInf = new QGroupBox("Room Information");
	roomLayout = new QGridLayout();

	roomInf->setLayout(roomLayout);

	labelType = new QLabel("type");
	labelBed = new QLabel("number Of Beds");
	labelStart = new QLabel("start Date");
	labelEnd = new QLabel("End Date");
	comboType = new QComboBox();
	spinBed =  new QSpinBox();
	DateStart =  new QDateEdit();
	DateEnd =  new QDateEdit();
	searchBtn =  new QPushButton("Search");
	roomLayout->addWidget(labelType,0 , 0);
	roomLayout->addWidget(comboType,0 , 1);
	roomLayout->addWidget(labelBed,0 , 2);
	roomLayout->addWidget(spinBed,0 , 3);
	roomLayout->addWidget(labelStart,1 , 0);
	roomLayout->addWidget(DateStart,1 , 1);
	roomLayout->addWidget(labelEnd,1 , 2);
	roomLayout->addWidget(DateEnd,1 , 3);
	roomLayout->addWidget(searchBtn,1 , 4);
	
	QDate date;
	date = date.currentDate();
	DateStart->setDisplayFormat("dd-MM-yyyy");
	DateEnd->setDisplayFormat("dd-MM-yyyy");
	DateStart->setDate(date);
	DateEnd->setDate(date);

	QStringList comboList;
	comboList << "normal" << "master"<<"suite"<<"business class room"<<"penthouse";
	comboType->addItems(comboList);

	spinBed->setRange(1,10);

	// config passengerLayout
	passengerInf= new QGroupBox("passenger Information");
	passengerLayout = new QGridLayout();
	passengerInf->setLayout(passengerLayout);
	labelName = new QLabel("First Name");
	labelFamily = new QLabel("Last Name");
	labelIDCode = new QLabel("ID code");
	labelTell = new QLabel("Phone Number");
	okBtn = new QPushButton("OK");
	LineName = new QLineEdit();
	LineFamily = new QLineEdit();
	LineId = new QLineEdit();
	LineTell = new QLineEdit();
	passengerLayout->addWidget(labelName,0,0);
	passengerLayout->addWidget(LineName,0,1);
	passengerLayout->addWidget(labelFamily,0,2);
	passengerLayout->addWidget(LineFamily,0,3);
	passengerLayout->addWidget(labelIDCode,1,0);
	passengerLayout->addWidget(LineId,1,1);
	passengerLayout->addWidget(labelTell,1,2);
	passengerLayout->addWidget(LineTell,1,3);
	passengerLayout->addWidget(okBtn,1,4);

	labelTable = new QLabel("click On  id column to select the room!");
	table = new QTableView();
	table->setModel(db->model);
	mainLayout->addWidget(roomInf);
	mainLayout->addWidget(labelTable);
	mainLayout->addWidget(table);
	mainLayout->addWidget(passengerInf);

	connect(searchBtn,SIGNAL(clicked()),this,SLOT(showRoom()));
	connect(okBtn,SIGNAL(clicked()),this,SLOT(reserveRoom()));
	
}

UI_reserve::~UI_reserve(void)
{
}

void UI_reserve::showRoom()
{

	if(db->findRoom(comboType->currentText(),spinBed->text()) )
	{
		//table->show();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("There is no room with this properties");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
	}
}
void UI_reserve::reserveRoom()
{
	QString _name = LineName->text();
	QString _famliy = LineFamily->text();
	QString _Idcode = LineId->text();
	QString _tell = LineTell->text();
	QString _start = DateStart->text();
	QString _end = DateEnd->text();
	QString _roomID = table->currentIndex().data().toString();
	if (_roomID.toInt() == 0)
	{
		QMessageBox msg;
		msg.setText("select id of the room in table");
		msg.setIcon(QMessageBox::Information);
		msg.exec();
		return;
	}
	int reserveID = 0;
	reserveID = db->reserveRoom(_name,_famliy,_Idcode,_tell,_roomID,_start,_end);
	if(reserveID)
	{
		table->clearSpans();
		QMessageBox msgBox;
		msgBox.setText("room reserved successfully!\n your reserveID is "+QString::number(reserveID));
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		updatePage();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("cannot reserve the room!");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
	}
}
void UI_reserve::updatePage()
{
	LineName->clear();
	LineFamily->clear();
	LineTell->clear();
	LineId->clear();
	QDate date;
	date = date.currentDate();
	DateStart->setDate(date);
	DateEnd->setDate(date);
	comboType->setCurrentIndex(0);
	db->model->clear();
	table->show();
}
