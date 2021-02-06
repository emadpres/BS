#include "dbwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QGroupBox>
#include "Table.h"

using namespace std;


dbWindow::dbWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// mainFrame mainLayout
	QFrame *mainFrame=new QFrame;
	this->setCentralWidget(mainFrame);
	QHBoxLayout *big= new QHBoxLayout();
	QVBoxLayout *mainLayout1 = new QVBoxLayout();
	QVBoxLayout *mainLayout2 = new QVBoxLayout();
	QVBoxLayout *mainLayout3 = new QVBoxLayout();
	mainFrame->setLayout(big);

	QGroupBox *g1=new QGroupBox();
	g1->setLayout(mainLayout1);
	big->addWidget(g1);
	g1->setTitle("SQL Test");
	g1->setFixedSize(220,300);
	big->addWidget(g1);

	QGroupBox *g2=new QGroupBox();
	g2->setLayout(mainLayout2);
	big->addWidget(g2);
	g2->setFixedSize(320,400);
	g2->setTitle("Query");

	big->addLayout(mainLayout3);

	// ComboBox

	combo = new QComboBox();
	combo->setFixedWidth(250);
	combo->addItem(""); //0
	combo->addItem("Person");
	combo->addItem("Device");
	combo->addItem("Mission");
	combo->addItem("Fire");
	combo->addItem("Activity");
	combo->addItem("--------"); //6
	combo->addItem("Most Useful Shift");
	combo->addItem("---------");//Biggest Mission
	combo->addItem("Moste Ever Successful Mission");
	combo->addItem("Days with Most Succesful Fire"); //10
	combo->addItem("Most Leaders");
	
	QObject::connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(comboChange(int)));


	
	//hLayout_1;
	QHBoxLayout *hLayout_1 = new QHBoxLayout();

	searchBut = new QPushButton("Serach");
	searchBut->setFixedWidth(150);
	QObject::connect(searchBut,SIGNAL(clicked()),this,SLOT(search()));
	hLayout_1->addWidget(searchBut);



	//hLayout_2;
	QHBoxLayout *hLayout_2 = new QHBoxLayout();
	
	nameLabel = new QLabel("Person: Name");
	name = new QLineEdit();
	degreeLabel = new QLabel("Degree");
	degree = new QLineEdit();

	hLayout_2->addWidget(nameLabel);
	hLayout_2->addWidget(name);
	hLayout_2->addWidget(degreeLabel);
	hLayout_2->addWidget(degree);

	//hLayout_3
	QHBoxLayout *hLayout_3 = new QHBoxLayout();

	shiftLabel= new QLabel("Shift");
	shift = new QLineEdit();
	dateFromLabel = new QLabel("Date: From");
	dateFrom = new QLineEdit();
	dateToLabel = new QLabel("To");
	dateTo = new QLineEdit();


	hLayout_3->addWidget(dateFromLabel);
	hLayout_3->addWidget(dateFrom);
	hLayout_3->addWidget(dateToLabel);
	hLayout_3->addWidget(dateTo);

	//hLayout_4
	QHBoxLayout *hLayout_4 = new QHBoxLayout();

	shiftLabel= new QLabel("Shift");
	shift = new QLineEdit();
	placeLabel = new QLabel("Place");
	place = new QLineEdit();


	hLayout_4->addWidget(shiftLabel);
	hLayout_4->addWidget(shift);
	hLayout_4->addWidget(placeLabel);
	hLayout_4->addWidget(place);

	//hLayout_5
	QHBoxLayout *hLayout_5 = new QHBoxLayout();

	kindLabel= new QLabel("Kind");
	kind = new QLineEdit();
	

	hLayout_5->addWidget(kindLabel);
	hLayout_5->addWidget(kind);



	// SQL Manual
	QTextEdit *box= new QTextEdit();
	box->setFixedSize(200,200);
	QPushButton *runManual = new QPushButton("Run as an Admin");
	runManual ->setFixedWidth(120);
	QObject::connect(runManual,SIGNAL(clicked()),SLOT(runManual()));


	// Table
	resultTable  = new myTable(5,3,this);
	resultTable->hide();
	resultTable->setMinimumSize(400,530);

	QHBoxLayout *hLayout_save = new QHBoxLayout();
	QHBoxLayout *hLayout_addDel = new QHBoxLayout();

	save = new QPushButton("save to file :");
		QObject::connect(save,SIGNAL(clicked()),SLOT(saveTable()));
	path = new QLineEdit();
	save->hide();
	path->hide();
	hLayout_save->addWidget(save);
	hLayout_save->addWidget(path);
	add = new QPushButton("Add");
	add->hide();
	del = new QPushButton("Delete");
	del->hide();
	QObject::connect(add,SIGNAL(clicked()),SLOT(addPerson()));
	QObject::connect(del,SIGNAL(clicked()),SLOT(delPerson()));
	hLayout_addDel->addWidget(add);
	hLayout_addDel->addWidget(del);

	



	

	/// Assign All Layouts
	initDisable();
	searchBut->setEnabled(false);

	mainLayout1->addWidget(box);
	mainLayout1->addWidget(runManual);

	mainLayout2->addWidget(combo);
	mainLayout2->setAlignment(combo, Qt::AlignHCenter);
	mainLayout2->addLayout(hLayout_1);
	mainLayout2->addLayout(hLayout_2);
	mainLayout2->addLayout(hLayout_3);
	mainLayout2->addLayout(hLayout_4);
	mainLayout2->addLayout(hLayout_5);

	mainLayout3->addWidget(resultTable);
	mainLayout3->addLayout(hLayout_save);
	mainLayout3->addLayout(hLayout_addDel);




	
	///******** Database ******************************************//
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("localhost");
	db.setDatabaseName("health");
	db.setUserName("admin");
	db.setPassword("admin");
	bool ok = db.open();
	if(!ok)
		exit(1);
	else
		query = new QSqlQuery(db); 


}
void dbWindow::comboChange(int index)
{
	initDisable();
	searchBut->setEnabled(true);
	switch(index)
	{
	case 1:
		curTable="Preson";
		add->show();
		del->show();
		name->setEnabled(true);
		degree->setEnabled(true);
		break;
	case 2:
		curTable="Activity";
		place->setEnabled(true);
		kind->setEnabled(true);
		break;
	case 3:
		curTable="Mission";
		name->setEnabled(true);
		shift->setEnabled(true);
		dateFrom->setEnabled(true);
		dateTo->setEnabled(true);
		place->setEnabled(true);
		
		break;
	case 4:
		curTable="Fire";

		break;
	case 5:
		curTable="Activity";
		name->setEnabled(true);
		degree->setEnabled(true);
		shift->setEnabled(true);
		dateFrom->setEnabled(true);
		dateTo->setEnabled(true);
		place->setEnabled(true);
		break;
	case 9:
	case 10:
	case 11:
		break;
	}

}
void dbWindow::search()
{
	resultTable->clear();
	switch(combo->currentIndex())
	{
		case 0:
			break;
		case 1:
			searchPerson();
			break;
		case 2:
			searchDevice();
			break;
		case 3:
			searchMission();
			break;
		case 5:
			searchActivity();
			break;
		case 7:
			mostUsefulShift();
			break;
		case 9:
			mostSuccessfulMission();
			break;
		case 10:
			dayMostSuccessfulFire();
			break;
		case 11:
			mostLeaders();
			break;
		//case 8:
		//	mostSuccessfulMission();
	}
}

//***************************************************

void dbWindow::searchPerson()
{
	int coulumn=0;
	QString q="Select * From Person";
	if(name->text() != "" || degree->text()!="" )
	{
		q += " Where 1==1 ";
		if(name->text() != "")
			q = q + " And name='"+name->text()+"'";
		if(degree->text() != "")
			q = q + " And degree='"+degree->text()+"'";
	}

	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 3 ;
	QStringList Headers;
	Headers<<"Person Code"<<"Degree"<<"Name";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}
void dbWindow::searchDevice()
{
	int coulumn=0;
	QString q="Select * From Device";
	if(kind->text() != "" || place->text()!="" )
	{
		q += " Where 1==1 ";
		if(kind->text() != "")
			q = q + " And kind='"+kind->text()+"'";
		if(place->text() != "")
			q = q + " And placeCode='"+place->text()+"'";
	}


	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 3 ;
	QStringList Headers;
	Headers<<"Device Code"<<"Kind"<<"Place";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}

void dbWindow::searchMission()
{
	int coulumn=0;
	QString q="Select * From Mission Where 1==1 ";
	
	if(name->text() != "")
	{
		query->exec("Select personCode from Person Where name='"+name->text()+"'");
		query->next();
		QString t=query->value(0).toString();
		q = q + " And personCode='"+t+"'";
	}

	if(place->text() != "")
		q = q + " And placeCode='"+place->text()+"'";
	if(shift->text() != "")
		q = q + " And shift='"+shift->text()+"'";
	if(dateFrom->text() != "")
	{
		if(dateTo->text() != "")
		{
			q = q + " And date>="+dateFrom->text() + " And date<="+dateTo->text() ;
		}
		else
		{
			q = q + " And date="+dateFrom->text() ;
		}
	}

	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 5 ;
	QStringList Headers;
	Headers<<"Mission Code"<<"Person Name"<<"Place Name"<<"Date"<<"Shift";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}
void dbWindow::mostUsefulShift()
{
	int coulumn=0;
	QString q="Select shift From (SELECT shift, Count(shift) as shiftCount FROM Mission Group by shift ) as a where shiftCount= (Select Max(b.shiftCount) From  (SELECT shift, Count(shift) as shiftCount FROM Mission Group by shift ) as b ) ";
	
	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 1 ;
	QStringList Headers;
	Headers<<"Most Useful Shifts";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();

}
void dbWindow::mostSuccessfulMission()
{
	int coulumn=0;
	QString q="Select * From Mission where missionCode  = (Select Max(x) From (select Count(*) as x From Fire Where result=1 group by missionCode)) ";
	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 5 ;
	QStringList Headers;
	Headers<<"Most Successful Missions Code"<<"Leader Code"<<"Place Code"<<"Date"<<"Shift";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}

void dbWindow::dayMostSuccessfulFire()
{
	int coulumn=0;
	QString q="select date From Fire where result=1 group by date having count(*)=(Select Max(c) From ( SELECT date ,count(*) as c FROM Fire Where result=1 group by date ) as date_count)"; 	
	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 2 ;
	QStringList Headers;
	Headers<<"Days with Most Succesful Fire";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();

}
void dbWindow::mostLeaders()
{
	int coulumn=0;
	QString q="select * From Person where personCode=(Select personCode From Mission group by personCode having count(*)=(Select max(c) From (Select Count(*) as c From Mission group by personCode)))";
	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 3 ;
	QStringList Headers;
	Headers<<"Leaer Code"<<"Degree"<<"Name";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}
void dbWindow::searchActivity()
{
	int coulumn=0;
	QString q="Select * From Activity Where 1==1 ";
	
	if(name->text() != "")
	{
		query->exec("Select personCode from Person Where name='"+name->text()+"'");
		query->next();
		QString t=query->value(0).toString();
		q = q + " And personCode='"+t+"'";
	}

	if(place->text() != "")
		q = q + " And placeCode='"+place->text()+"'";
	if(shift->text() != "")
		q = q + " And shift='"+shift->text()+"'";
	if(dateFrom->text() != "")
	{
		if(dateTo->text() != "")
		{
			q = q + " And date>="+dateFrom->text() + " And date<="+dateTo->text() ;
		}
		else
		{
			q = q + " And date="+dateFrom->text() ;
		}
	}

	if(!query->exec(q))
		coulumn=-1;
	else
		coulumn = 5 ;
	QStringList Headers;
	Headers<<"Activity Code"<<"Person Name"<<"Date"<<"Shift"<<"Place Name";
	resultTable->load(query,coulumn ,Headers);
	save->show();
	path->show();
}
//**************************************************************
void dbWindow::addPerson()
{
	if(name->text()!="" && degree->text()!="" )
	{
		query->exec("Select Count(*) from Person");
		query->next();
		int x=query->value(0).toInt();
		x++;
		QString count=QString::number(x);
		count = "Insert Into Person Values("+count+","+degree->text()+",'"+name->text()+"')" ;
		query->exec( count );
	}

	searchPerson();


}
void dbWindow::delPerson()
{
	if(name->text()!="" || degree->text()!="" )
	{
		QString q= "Delete From Person Where 1==1 ";
		if(name->text()!="")
			q = q + " And name='"+name->text()+"'";
		if(degree->text()!="")
			q = q + " And degree="+degree->text();
		
		query->exec( q );
	}
	
	searchPerson();

}

void dbWindow::runManual()
{
	resultTable->hide();
}

void dbWindow::saveTable()
{
	if(path->text()!="")
		resultTable->save(path->text());
}
dbWindow::~dbWindow()
{

}
void dbWindow::initTable()
{
	query->exec("Create Table Person ( code Integer Primary Key, degree Integer, shift Integer Not Null, name Vchar(20) Not Null, Check(degree>0) )");
	query->exec("Create Table Activity (activityCode INTEGER PRIMARY KEY  NOT NULL , personCode INTEGER, date INTEGER, shift INTEGER, placeCode INTEGER, Foreign Key (personalCode) References Person On Update Cascade, Check(placeCode<3) )");
	query->exec("CREATE TABLE Device (deviceCode INTEGER PRIMARY KEY  NOT NULL ,kind VARCHAR(20) NOT NULL ,placeCode INTEGER NOT NULL )");
	query->exec("CREATE TABLE Fire (fireCode INTEGER PRIMARY KEY  NOT NULL , missionCode INTEGER NOT NULL , gunCode INTEGER NOT NULL , date INTEGER NOT NULL , shift INTEGER NOT NULL , objectCode INTEGER, kind VARCHAR(20), result BOOL)");
	query->exec("CREATE TABLE Mission (missionCode INTEGER PRIMARY KEY  NOT NULL , personCode INTEGER NOT NULL , placeCode INTEGER NOT NULL , date INTEGER NOT NULL , shift INTEGER NOT NULL )");
	query->exec("CREATE TABLE Object (objectCode INTEGER PRIMARY KEY  NOT NULL , deviceCode INTEGER NOT NULL , date INTEGER NOT NULL , time INTEGER NOT NULL )");
	query->exec("CREATE TABLE Place (placeCode INTEGER PRIMARY KEY  NOT NULL ,name VARCHAR(20) NOT NULL )");
	query->exec("CREATE TABLE Tracking (trackingCode INTEGER PRIMARY KEY  NOT NULL , missionCode INTEGER, objectCode INTEGER NOT NULL , deviceCode INTEGER NOT NULL , date INTEGER NOT NULL , shift INTEGER NOT NULL )");
	//query->exec("Insert Into Person Values(1,Null,2,'Emad')");
	//query->exec("Insert Into Person Values(2,Null,2,'Hasan')");
	
	
	
}
void dbWindow::initDisable()
{
	curTable="";
	name->setDisabled(true);
	degree->setDisabled(true);
	place->setDisabled(true);
	shift->setDisabled(true);
	dateFrom->setDisabled(true);
	dateTo->setDisabled(true);
	kind->setDisabled(true);

	add->hide();
	del->hide();
}