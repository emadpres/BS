#include "motelwidget.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHBoxLayout>
MotelWidget::MotelWidget(QWidget *parent, int userID)
	: QWidget(parent)
{
	//ui.setupUi(this);
	db =  new database();

	currentUserID = userID+1;

	contentsWidget = new QListWidget(this);
	contentsWidget->setViewMode(QListView::IconMode);
	contentsWidget->setIconSize(QSize(60, 84));
	contentsWidget->setMovement(QListView::Static);
	contentsWidget->setMaximumWidth(350);
	contentsWidget->setSpacing(50);

	//page
	pagesWidget = new QStackedWidget(this);

	reservePage = new ReservationWidget( db, this );
	pagesWidget->addWidget(reservePage);

	StaffWorkPage = new StaffWork(db,this);
	pagesWidget->addWidget(StaffWorkPage);

	TransportationPage = new TransportationWidget(db,this);
	pagesWidget->addWidget(TransportationPage);


	


	//
	createIcons();
	contentsWidget->setCurrentRow(0);

	//Layout
	QHBoxLayout *horizontalLayout = new QHBoxLayout();
	//QVBoxLayout *leftLayout = new QVBoxLayout();
	horizontalLayout->addWidget(contentsWidget);
	horizontalLayout->addWidget(pagesWidget);
	//leftLayout->addWidget(pagesWidget, 1);
	//QPushButton* a=new QPushButton("AAAA");
	//leftLayout->addWidget(a);
	//

	QVBoxLayout *mainLayout = new QVBoxLayout(this);



	mainLayout->addLayout(horizontalLayout);
	//mainLayout->addStretch(1);
	//mainLayout->addSpacing(12);
	//setLayout(mainLayout);
	setWindowTitle(tr("سامانه هتلداری همیار "));
	this->setFixedSize(1050,620);

}

MotelWidget::~MotelWidget()
{

}


void MotelWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	pagesWidget->setCurrentIndex(contentsWidget->row(current));

	if(pagesWidget->currentIndex() == 0)
	{
		reservePage->updatePage();
	}
	else if(pagesWidget->currentIndex() == 1)
	{
		StaffWorkPage->updatePage();
	}
	else if(pagesWidget->currentIndex() == 2)
	{
		TransportationPage->updatePage();
	}
}


void MotelWidget::createIcons()
{
	QListWidgetItem *reserveButton = new QListWidgetItem(contentsWidget);
	reserveButton->setIcon(QIcon("images/reserve.gif"));
	reserveButton->setText(tr("رزرواسیون"));
	reserveButton->setTextAlignment(Qt::AlignHCenter);
	reserveButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *staffWorkButton = new QListWidgetItem(contentsWidget);
	staffWorkButton->setIcon(QIcon("images/tamdid.jpg"));
	staffWorkButton->setText(tr("ثبت ورود/خروج"));
	staffWorkButton->setTextAlignment(Qt::AlignHCenter);
	staffWorkButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


	QListWidgetItem *reserveTransportation = new QListWidgetItem(contentsWidget);
	reserveTransportation->setIcon(QIcon("images/tamdid.jpg"));
	reserveTransportation->setText(tr("حمل و نقل"));
	reserveTransportation->setTextAlignment(Qt::AlignHCenter);
	reserveTransportation->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	/*reserveButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	QListWidgetItem *deliverButton = new QListWidgetItem(contentsWidget);
	deliverButton->setIcon(QIcon("images/deliver.png"));
	deliverButton->setText(tr("دلیور"));
	deliverButton->setTextAlignment(Qt::AlignHCenter);
	deliverButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


	QListWidgetItem *reserveExtensionButton = new QListWidgetItem(contentsWidget);
	reserveExtensionButton->setIcon(QIcon("images/tamdid.jpg"));
	reserveExtensionButton->setText(tr("Reserve Extension"));
	reserveExtensionButton->setTextAlignment(Qt::AlignHCenter);
	reserveExtensionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/



	connect(contentsWidget,
		SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
		this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}