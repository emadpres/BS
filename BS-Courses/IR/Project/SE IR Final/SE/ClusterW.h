#ifndef CLUSTERW_H
#define CLUSTERW_H


#include <QtGui/QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QRadioButton>
#include "search.h"
#include "averagecluster.h"
#include "centroidCluster.h"
class ClusterW : public QDialog
{
    Q_OBJECT

public:
    ClusterW(QWidget *parent = 0,CSearcher* sea2=0);
    QHBoxLayout *Line1,*Line2,*Line3;
    QVBoxLayout *MainL;
    CSearcher* sea;
    QImage *MainImage;
    QLabel *InfoL,*TimeL,*imageLabel;
    QWidget *pic;
    QPixmap *image;
    QPushButton* ClusterB;
    QLineEdit *InputLine;
    QPlainTextEdit *TextEdit;
    QFile* CFile;
    QTextStream* CStream;
    QRadioButton* Average,*Single;
public slots:
    void ClusterFunc();

};
#endif // CLUSTERW_H
