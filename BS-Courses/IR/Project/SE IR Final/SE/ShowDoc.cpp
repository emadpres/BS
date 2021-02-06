#include "ShowDoc.h"
ShowDoc::ShowDoc(QWidget *parent, QString *text)
    : QDialog(parent)
{
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Search Engine");
    this->setFixedSize(800,600);
    TextEdit=new QPlainTextEdit(*text);
    QLabel *label=new QLabel();
    label->setText("\t\t\t\tDocument Viewer");
    this->setLayout(new QVBoxLayout());
    layout()->addWidget(label);
    layout()->addWidget(TextEdit);
    TextEdit->setReadOnly(1);
}
ShowDoc::~ShowDoc()
{
}
