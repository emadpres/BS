#include "dialog.h"
#include "ClusterW.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Search Engine");
    this->setFixedSize(800,680);
    sea=new CSearcher();
    sea->MakeIndex();
    MainL=new QVBoxLayout();
    WidgetLayout=new QVBoxLayout();
    InputLine=new QLineEdit();
    HomeUI();
    setLayout(MainL);
    InputLine->setFocus();
    first=false;
    connect(InputLine,SIGNAL(textChanged(QString)),this,SLOT(SearchF()));
}
void Dialog::MoveToResault()
{
     QLayoutItem *child;
     first=true;
     while ((child = MainL->takeAt(0)) != 0)
     {
         if(child->widget())
         {
            child->widget()->hide();
            if(child->widget()!=InputLine)
                delete child;
         }
         else if(child->spacerItem())
         {
             delete child;
         }
     }
     InputLine->show();
     TimeInfo=new QLabel("         Time Information");
     image = new QPixmap("CaptureSmall.PNG");
     imageLabel = new QLabel();
     PageLabel=new QLabel("     Page Number 1   ");
     imageLabel->setPixmap(*image);
     QWidget *x,*q,*z,*w;
     x=new QWidget();
     q=new QWidget();
     z=new QWidget();
     w=new QWidget();
     Search=new QPushButton("Search");
     BackButton=new QPushButton("&Back");
     NextPage=new QPushButton("Next");
     PrevPage=new QPushButton("Prev");
     z->setLayout(new QVBoxLayout());
     x->setLayout(new QHBoxLayout());
     x->layout()->addWidget(InputLine);
     x->layout()->addWidget(Search);
     x->layout()->addWidget(BackButton);
     z->layout()->addWidget(x);
     z->layout()->addWidget(TimeInfo);
     q->setLayout(new QHBoxLayout());
     q->layout()->addWidget(imageLabel);
     q->layout()->addWidget(z);
     MainL->addWidget(q);
     MainL->addLayout(WidgetLayout);
     PageNumber=1;
     natije=sea->SearchWithQuery(InputLine->text().toStdString().c_str());
     WidgetLayout->addWidget(GetPage(PageNumber,WidgetLayout,natije));
     w->setLayout(new QHBoxLayout());
     w->layout()->addWidget(PrevPage);
     w->layout()->addWidget(PageLabel);
     w->layout()->addWidget(NextPage);
     w->setFixedSize(400,50);
     MainL->addWidget(w);
     connect(Search,SIGNAL(clicked()),this,SLOT(SearchF()));
     connect(BackButton,SIGNAL(clicked()),this,SLOT(HomeUI()));
     connect(NextPage,SIGNAL(clicked()),this,SLOT(PageMovePlus()));
     connect(PrevPage,SIGNAL(clicked()),this,SLOT(PageMoveNeg()));
}
void Dialog::PageMovePlus()
{
    int m;
    if(natije.size()%3==0)
        m=natije.size()/3;
    else
        m=natije.size()/3+1;
    PageNumber++;
    char* tempc=new char();
    PageLabel->setText(("     Page Number: "+QString(itoa(PageNumber,tempc,10))+" of "+QString(itoa(m,tempc,10))));
    delete tempc;
    WidgetLayout->addWidget(GetPage(PageNumber,WidgetLayout,natije));
}
void Dialog::PageMoveNeg()
{
    int m;
    if(natije.size()%3==0)
        m=natije.size()/3;
    else
        m=natije.size()/3+1;
    PageNumber--;
    char* tempc=new char();
    PageLabel->setText(("     Page Number: "+QString(itoa(PageNumber,tempc,10))+" of "+QString(itoa(m,tempc,10))));
    delete tempc;
    WidgetLayout->addWidget(GetPage(PageNumber,WidgetLayout,natije));
}

QWidget* Dialog::GetPage(int pageno,QVBoxLayout* pLayout,std::vector<int> res)
{
    QLayoutItem* child;
    const int zarib=3;
    NextPage->setEnabled(1);
    PrevPage->setEnabled(1);
    char* tempc=new char();
    TimeInfo->setText("         Found "+QString(itoa(res.size(),tempc,10))+" results");
    delete tempc;
    while ((child = pLayout->takeAt(0)) != 0)
    {
        if(child->widget())
           child->widget()->hide();
        delete child;
    }
    char* temp=new char[50];
    QWidget* returnWidget=new QWidget();
    returnWidget->setLayout(new QVBoxLayout());
    for(int i=(pageno-1)*zarib;i<(pageno*zarib);i++)
    {
        if(i<res.size())
        {
            char*a=new char[50];
            strcpy(temp,sea->docs[res[i]].c_str());
            delete a;
            returnWidget->setFixedSize(800,500);
            returnWidget->layout()->addWidget(new Result(0,temp));
        }
    }
    if(res.size()==0)
    {
        returnWidget->layout()->addWidget(new QLabel("Your search \""+InputLine->text()+"\" did not match any documents. "));
        returnWidget->layout()->addWidget(new QLabel("Suggestions:"));
        returnWidget->layout()->addWidget(new QLabel("* Make sure all words are spelled correctly."));
        returnWidget->layout()->addWidget(new QLabel("* Try different keywords."));
        returnWidget->layout()->addWidget(new QLabel("* Try more general keywords. "));
        for(int i=0;i<20;i++)
            returnWidget->layout()->addWidget(new QLabel(" "));
    }
    if(pageno*zarib>res.size())
    {
       if((pageno*zarib)-res.size()==1)
           for(int i=0;i<6;i++)
                returnWidget->layout()->addWidget(new QLabel(" "));
       else if((pageno*zarib)-res.size()==2)
           for(int i=0;i<12;i++)
              returnWidget->layout()->addWidget(new QLabel(" "));
   }
    if(pageno*zarib>=res.size())
        NextPage->setEnabled(0);
    if(pageno==1)
        PrevPage->setEnabled(0);
   return returnWidget;
}

void Dialog::HomeUI()
{
    QPalette pl;
    QLayoutItem *child;
    first=false;
    while ((child = MainL->takeAt(0)) != 0)
    {
        if(child->widget())
        {
           child->widget()->hide();
           if(child->widget()!=InputLine)
               delete child;
        }
        else if(child->spacerItem())
        {
            delete child;
        }
    }
    while ((child =WidgetLayout->takeAt(0)) != 0)
    {
        if(child->widget())
           child->widget()->hide();
        delete child;
    }
    //set Image
    MainImage=new QImage("Capture.PNG");
    // new label
    CreateL=new QPushButton();
    EvaluateL=new QPushButton();
    ClusterL=new QPushButton();

    //set Cluster Label Att
    ClusterL->setText("Cluster");
    ClusterL->setFlat(1);
    pl=ClusterL->palette();
    pl.setColor(QPalette::Normal,QPalette::ButtonText,QColor(0, 0, 255));
    ClusterL->setPalette(pl);
    //set Create Label Att
    CreateL->setText("Create");
    CreateL->setFlat(1);
    pl=CreateL->palette();
    pl.setColor(QPalette::Normal,QPalette::ButtonText,QColor(0, 0, 255));
    CreateL->setPalette(pl);
    //Button
    Search=new QPushButton("&Search");
    Search->setAutoFillBackground(0);
    Lucky=new QPushButton("&I'm Feeling Lucky");
    Lucky->setAutoFillBackground(0);
    //set Evaluate Label Att
    EvaluateL->setText("Evaluate");
    EvaluateL->setFlat(1);
    pl=EvaluateL->palette();
    pl.setColor(QPalette::Normal,QPalette::ButtonText,QColor(0, 0, 255));
    EvaluateL->setPalette(pl);
    //image
    image = new QPixmap("Capture.PNG");
    imageLabel = new QLabel();
    imageLabel->setPixmap(*image);
    //add Line
    InputLine->setFixedWidth(400);

    // Add Label To Layout
    MainL->addSpacerItem(new QSpacerItem(0,200));
    QWidget* w;
    MainL->addWidget(imageLabel,0,Qt::AlignCenter);
    MainL->addWidget(InputLine,0,Qt::AlignCenter);
    w=new QWidget();
    w->setLayout(new QHBoxLayout());
    w->layout()->addWidget(Search);
    w->layout()->addWidget(Lucky);
    MainL->addWidget(w,0,Qt::AlignCenter);
    w=new QWidget();
    w->setLayout(new QHBoxLayout());
    w->layout()->addWidget(ClusterL);
    w->layout()->addWidget(CreateL);
    w->layout()->addWidget(EvaluateL);
    MainL->addWidget(w,0,Qt::AlignCenter);
    MainL->addSpacerItem(new QSpacerItem(0,300));
    connect(ClusterL,SIGNAL(clicked()),this,SLOT(ClusterF()));
    connect(EvaluateL,SIGNAL(clicked()),this,SLOT(EvaluateF()));
    connect(CreateL,SIGNAL(clicked()),this,SLOT(CreateF()));
    connect(Search,SIGNAL(clicked()),this,SLOT(SearchF()));
    connect(Lucky,SIGNAL(clicked()),this,SLOT(LuckyF()));
    InputLine->setFocus();
}

void Dialog::ClusterF()
{
   ClusterW *ClusW=new ClusterW(this,sea);
   ClusW->show();
}
void Dialog::EvaluateF()
{
    double RI=0,Purity=0;
    eval *e=new eval("cluster.txt","class.txt",&RI,&Purity);
    e->Run();
    QMessageBox msgBox;
    msgBox.setText("Evaluation Result");
    char* tempc=new char();
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText("Purity = "+QString(itoa(Purity*100,tempc,10))+" %\nRI = "+QString(itoa(RI*100,tempc,10))+" %");
    delete tempc;
    msgBox.exec();

}
void Dialog::SearchF()
{
    if(InputLine->text()!="")
         MoveToResault();
    else if(first)
        HomeUI();
    InputLine->setFocus();
}
void Dialog::CreateF()
{
    delete sea;
    sea=new CSearcher();
    sea->MakeIndex();
    QMessageBox msgBox;
    msgBox.setText("Index Make Successfully");
    char* tempc=new char();
    msgBox.setIcon(QMessageBox::Information);
    delete tempc;
    msgBox.exec();
}
void Dialog::LuckyF()
{
    if(natije.size()!=0)
    {
        QString fo="File/";
        fo+=sea->docs[natije[0]].c_str();
        QFile* File=new QFile(fo);
        File->open(QIODevice::ReadWrite);
        QTextStream *Stream=new QTextStream(File);
        ShowDoc *ClusW=new ShowDoc(this,&Stream->readAll());
        ClusW->show();
        File->close();
        delete File;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("No Match Found");
        char* tempc=new char();
        msgBox.setIcon(QMessageBox::Information);
        delete tempc;
        msgBox.exec();
    }
}

Dialog::~Dialog()
{
}
