#ifndef SHOWDOC_H
#define SHOWDOC_H
#include <QtGui/QDialog>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QLabel>
class ShowDoc : public QDialog
{
    Q_OBJECT
public:
    ShowDoc(QWidget *parent = 0,QString* text=0);
    ~ShowDoc();
    QPlainTextEdit* TextEdit;

};

#endif // SHOWDOC_H
