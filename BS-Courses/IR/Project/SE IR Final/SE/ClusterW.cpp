
#include "ClusterW.h"

ClusterW::ClusterW(QWidget *parent,CSearcher* sea2)
    : QDialog(parent)
{
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Search Engine");
    //new Layout
    sea=sea2;
    Line1=new QHBoxLayout();
    Line2=new QHBoxLayout();
    Line3=new QHBoxLayout();
    MainL=new QVBoxLayout();
    TextEdit=new QPlainTextEdit();
    TextEdit->setFixedSize(500,600);
    TextEdit->setReadOnly(1);
    //set Image
    MainImage=new QImage("Capture.PNG");
    // new label
    InfoL=new QLabel();
    //set Cluster Label Att
    InfoL->setText("Please Enter Number Of Cluster");
    //Button
    ClusterB=new QPushButton("&Cluster");
    //set Time Label
    TimeL=new QLabel();
    TimeL->setText("System Time");
    //image
    image = new QPixmap("Capturesmall.PNG");
    imageLabel = new QLabel();
    imageLabel->setPixmap(*image);
    //add Line
    InputLine=new QLineEdit();
    InputLine->setFixedWidth(400);
    Average=new QRadioButton("Average Link");
    Single=new QRadioButton("Centroid");
    Average->setChecked(1);
    QWidget *tempw=new QWidget();
    tempw->setLayout(new QVBoxLayout());
    tempw->layout()->addWidget(Average);
    tempw->layout()->addWidget(Single);
    // Add Label To Layout
    Line1->addWidget(imageLabel);
    Line1->addWidget(InfoL);
    Line1->addWidget(InputLine);
    Line1->addWidget(tempw);
    Line1->addWidget(ClusterB);
    Line2->addWidget(TextEdit,0,Qt::AlignCenter);
    Line3->addWidget(TimeL,0,Qt::AlignCenter);
    MainL->addLayout(Line1);
    MainL->addLayout(Line2);
    MainL->addLayout(Line3);
    setLayout(MainL);
    connect(ClusterB,SIGNAL(clicked()),this,SLOT(ClusterFunc()));
}
void ClusterW::ClusterFunc()
{
    QTime* CLTime;
    char* tempc;
    int TimeD;
    if(Average->isChecked())
    {
        tempc=new char();
        delete CLTime;
        CLTime=new QTime();
        CLTime->start();
        CAverageCluster* averageItem=new CAverageCluster(sea);
        averageItem->Cluster(InputLine->text().toInt());
        TimeD=CLTime->elapsed();
        TimeL->setText(QString("Clustering Time= "+QString(itoa(TimeD,tempc,10))+" ms"));
        delete tempc;
    }
    if(Single->isChecked())
    {
        tempc=new char();
        delete CLTime;
        CLTime=new QTime();
        CLTime->start();
        CCentroidCluster* centroidItem=new CCentroidCluster(sea);
        centroidItem->Cluster(InputLine->text().toInt());
        TimeD=CLTime->elapsed();
        TimeL->setText(QString("Clustering Time= "+QString(itoa(TimeD,tempc,10))+" ms"));
        delete tempc;
    }
    CFile=new QFile("cluster.txt");
    CFile->open(QIODevice::ReadWrite);
    CStream=new QTextStream(CFile);
    TextEdit->clear();
    TextEdit->appendPlainText("\t\t    Clustering Finish Successfully\n");
    TextEdit->appendPlainText("Number Of Cluster:");
    TextEdit->appendPlainText(CStream->readLine());
    TextEdit->appendPlainText("\nClusters:");
    TextEdit->appendPlainText(CStream->readAll());
    CFile->close();
    delete CFile;
}
