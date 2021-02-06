#include "result.h"
#include "ShowDoc.h"
Result::Result(QWidget *parent,char* FileID) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout());
    char* temp=new char[50];
    strcpy(temp,"File/");
    strcat(temp,FileID);
    FileB=new QPushButton(FileID);
    FileName=temp;
    QPalette pl;
    FileB->setFlat(1);
    pl=FileB->palette();
    pl.setColor(QPalette::Normal,QPalette::ButtonText,QColor(0, 0, 255));
    FileB->setPalette(pl);
    FileB->setMaximumSize(60,30);
    FileB->setMinimumSize(60,30);
    File=new QFile(temp);
    File->open(QIODevice::ReadWrite);
    Stream=new QTextStream(File);
    Address=new QLabel(("<font color=#00FF00>"+("  Address: "+QString(temp))+"</font>"));
    Info=new QLabel(("Summury:\n"+Stream->readLine()));
    Stream->readLine();
    Stream->readLine();
    Stream->readLine();
    Stream->readLine();
    Info1=new QLabel(Stream->readLine());
    Info2=new QLabel(Stream->readLine());
    this->layout()->addWidget(FileB);
    this->layout()->addWidget(Address);
    this->layout()->addWidget(Info);
    this->layout()->addWidget(Info1);
    this->layout()->addWidget(Info2);
    File->close();
    delete File;
    this->setFixedSize(800,150);
    connect(FileB,SIGNAL(clicked()),this,SLOT(Open()));
}
void Result::Open()
{
    File=new QFile(FileName);
    File->open(QIODevice::ReadWrite);
    Stream=new QTextStream(File);
    ShowDoc *ClusW=new ShowDoc(this,&Stream->readAll());
    ClusW->show();
    File->close();
    delete File;
}
