#pragma once
#include <QMainWindow>
#include "QListWidget"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QTextEdit"
#include "QDir"


class CWindow:public QWidget
{
//	Q_OBJECT

public:
	CWindow(QWidget *parent = 0);
	~CWindow();
	void Search();
	void ShowResult();

	QVBoxLayout *mMainLayout;
	QHBoxLayout *mSearchLayout, *mResultLayout;
	QPushButton *mSearchButton, *mShowButton;
	QTextEdit *mTextEdit;
	QListWidget *mResultList;

};
