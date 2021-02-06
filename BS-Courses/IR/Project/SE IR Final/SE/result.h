#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QPalette>
class Result : public QWidget
{
    Q_OBJECT
public:
    Result(QWidget *parent = 0,char*FileID=0);
    QPushButton* FileB;
    QLabel *Address,*Info,*Info1,*Info2;
    QFile *File;
    char* FileName;
    QTextStream *Stream;
signals:

public slots:
    void Open();

};

#endif // RESULT_H
