#include "reserveExtension.h"
#include <QSqlQueryModel>



reserveExtension::reserveExtension(database *mdb ,QWidget *parent)
{

	db = mdb ;
	//querymodel = new QSqlTableModel;

	searchbox = new QGroupBox("Search");
	resultbox = new QGroupBox("Result");
	mainvlay = new QVBoxLayout(this);

	idcode_lbl = new QLabel("ID");
	reserveid_lbl = new QLabel("Reserve ID");

	idcode_line = new QLineEdit();
	reserveid_line = new QLineEdit();

	searchbtn = new QPushButton("Search");

	tophlay = new QHBoxLayout();

	tophlay->addWidget(idcode_lbl);
	tophlay->addWidget(idcode_line);
	tophlay->addWidget(reserveid_lbl);
	tophlay->addWidget(reserveid_line);
	tophlay->addWidget(searchbtn);

	searchbox->setLayout(tophlay);




	downhlay = new QHBoxLayout();
	downdownhlay = new QHBoxLayout();
	vblay = new QVBoxLayout();

	table = new QTableView();
	changebtn = new QPushButton("Change");
	endtime = new QDateEdit();
	endtime->setDisplayFormat("dd-MM-yyyy");
	endtime->setDate(QDate::currentDate());
	endtime_lbl = new QLabel("Please enter the end time \n that you want to stay ");

	downhlay->addWidget(table);
	downdownhlay->addWidget(endtime_lbl);
	downdownhlay->addWidget(endtime);
	downdownhlay->addWidget(changebtn);
	
	vblay->addLayout(downhlay);
	vblay->addLayout(downdownhlay);

	resultbox->setLayout(vblay);
	//resultbox->setLayout(downdownhlay);

	mainvlay->addWidget(searchbox);
	mainvlay->addWidget(resultbox);



	connect(searchbtn , SIGNAL(clicked()) ,this ,SLOT(showTable()));
	connect(changebtn , SIGNAL(clicked()) ,this ,SLOT(showMessage()) );

}

reserveExtension::~reserveExtension(void)
{
}

void reserveExtension::showTable()
{
	db->reserveExtensionSearch(idcode_line->text() , reserveid_line->text() );
	table->setModel(db->model);
	table->show();
}
void reserveExtension::showMessage()
{
	QSqlQueryModel *q;

	double cost;
	cost = db->retrieveCost(idcode_line->text() , reserveid_line->text());
	QDate t = endtime->date();
	endWant2stay = db->retrieveEndTime(idcode_line->text() , reserveid_line->text());

	/*
	QString a,b;
	a = t.toString();
	b = endWant2stay.toString();
	*/
	
	int diff = endWant2stay.daysTo(t);

	msgBox = new QMessageBox();
	

	if(diff*cost  <= 0.0)
	{
		msgBox->setInformativeText("The time that you enter is incorrect \n please enter again.");
		msgBox->setStandardButtons(QMessageBox::Cancel);
		msgBox->setDefaultButton(QMessageBox::Cancel);

	}
	else
	{
		msgBox->setText("The extensive cost that you must pay is "+QString::number(diff*cost)+"." );
		msgBox->setInformativeText("Do you want to stay?");
		msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
		msgBox->setDefaultButton(QMessageBox::Save);

	}
	db->reserveExtensionSearch(idcode_line->text() , reserveid_line->text() );
	int ret = msgBox->exec();

	 switch (ret) {
   case QMessageBox::Save:
       // Save was clicked
	   db->updateEndTime(t  , reserveid_line->text());
	   db->reserveExtensionSearch(idcode_line->text() , reserveid_line->text() );
       break;
   //case QMessageBox::Discard:
       // Don't Save was clicked
    //   break;
   case QMessageBox::Cancel:
	   db->reserveExtensionSearch(idcode_line->text() , reserveid_line->text() );
       // Cancel was clicked
	   
       break;
   default:
       // should never be reached
       break;
 }

}
void reserveExtension::updatePage()
{
	idcode_line->clear();
	reserveid_line->clear();
	QDate date;
	date = date.currentDate();
	endtime->setDate(date);
	db->model->clear();
	table->show();

}