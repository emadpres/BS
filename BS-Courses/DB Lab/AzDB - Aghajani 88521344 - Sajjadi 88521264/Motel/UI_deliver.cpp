#include "UI_deliver.h"

UI_deliver::UI_deliver(database *mdb, QWidget *parent)
{	
	db = mdb;
	search = new QPushButton("Search");
	vbox = new QVBoxLayout(this);
	QGridLayout *grid1 = new QGridLayout();
	QGroupBox *group1 = new QGroupBox(tr("Deliver"));
	//
	reserveIdLable = new QLabel("reserve ID");
	reserveIdLable->setFixedWidth(50);
	reserveIdLineEdit = new QLineEdit();
	grid1->addWidget(reserveIdLable, 0, 0);
	grid1->addWidget(reserveIdLineEdit, 0, 2);
	//
	idCodeLable = new QLabel("ID code");
	idCodeLable->setFixedWidth(50);
	idCodeLineEdit = new QLineEdit();
	grid1->addWidget(idCodeLable, 0, 4);
	grid1->addWidget(idCodeLineEdit, 0, 5);
	grid1->addWidget(search, 1, 5);
	//

	//inja bayad query bezanam

	//
	QGridLayout *grid2 = new QGridLayout();
	QGroupBox *group2 = new QGroupBox(tr("Passenger"));
	//mosafer
	nameLable = new QLabel("Name");
	nameLable->setFixedWidth(50);
	nameLineEdit = new QLineEdit();
	grid2->addWidget(nameLable, 0, 0);
	grid2->addWidget(nameLineEdit, 0, 2);
	//
	familyLable = new QLabel("Family");
	familyLable->setFixedWidth(50);
	familyLineEdit = new QLineEdit();
	grid2->addWidget(familyLable, 0, 4);
	grid2->addWidget(familyLineEdit, 0, 5);
	//
	passengerIdCodeLable = new QLabel("ID");
	passengerIdCodeLable->setFixedWidth(50);
	passengerIdCodeLineEdit = new QLineEdit();
	grid2->addWidget(passengerIdCodeLable, 1, 0);
	grid2->addWidget(passengerIdCodeLineEdit, 1, 2);
	//
	tellLable = new QLabel("Tell");
	tellLable->setFixedWidth(50);
	tellLineEdit = new QLineEdit();
	grid2->addWidget(tellLable, 1, 4);
	grid2->addWidget(tellLineEdit, 1, 5);

	group1->setLayout(grid1);
	group2->setLayout(grid2);

	vbox->addWidget(group1);
	vbox->addWidget(group2);

	connect(search, SIGNAL(clicked()), this, SLOT(save()));

}

UI_deliver::~UI_deliver(void)
{
}

void UI_deliver::save()
{
	qCodeID = idCodeLineEdit->text();
	qReserveId = reserveIdLineEdit->text().toInt();
	nameLineEdit->setText(db->fill(qReserveId, qCodeID)[0]);
	familyLineEdit->setText(db->fill(qReserveId, qCodeID)[1]);
	tellLineEdit->setText(db->fill(qReserveId, qCodeID)[2]);
	passengerIdCodeLineEdit->setText(db->fill(qReserveId, qCodeID)[3]);
	//
	QMessageBox msgBox;
	msgBox.setText(db->fill(qReserveId, qCodeID)[4] + " toman ,  for " + db->fill(qReserveId, qCodeID)[5] + " day(s) !");
	msgBox.setIcon(QMessageBox::Information);
	msgBox.exec();
}
void UI_deliver::updatePage()
{
	reserveIdLineEdit->clear();
	idCodeLineEdit->clear();
	nameLineEdit->clear();
	familyLineEdit->clear();
	passengerIdCodeLineEdit->clear();
	tellLineEdit->clear();
}