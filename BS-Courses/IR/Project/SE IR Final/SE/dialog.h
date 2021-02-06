#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QPalette>
#include "eval.h"
#include "searcher.h"
#include "result.h"
#include "ShowDoc.h"
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void MoveToResault();
    std::vector<int> natije;
    QWidget* GetPage(int pageno,QVBoxLayout* pLayout,std::vector<int>);
    QHBoxLayout *Line1,*Line2,*Line3,*Line4,*Line3_2,*Line4_2;
    QVBoxLayout *MainL,*WidgetLayout;
    QImage *MainImage;
    QLabel *imageLabel,*TimeInfo,*PageLabel;
    QWidget *pic;
    QPixmap *image;
    QPushButton *ClusterL,*CreateL,*EvaluateL,* Search,*Lucky,*NextPage,*PrevPage,*BackButton;
    QLineEdit *InputLine;
    CSearcher* sea;
    bool first;
    int PageNumber;
 public slots:
    void ClusterF();
    void EvaluateF();
    void HomeUI();
    void CreateF();
    void SearchF();
    void PageMovePlus();
    void PageMoveNeg();
    void LuckyF();
};
#endif // DIALOG_H
