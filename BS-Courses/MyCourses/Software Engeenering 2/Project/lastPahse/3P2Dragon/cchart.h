#ifndef CCHART_H
#define CCHART_H

#include <QWidget>
#include <QtCore>
#include <QtGui>

class CChart : public QWidget
{
	Q_OBJECT

public:
	CChart(QMap<QString,int> list,QWidget *parent = 0);
	~CChart();
	//************************************
	// Method:    paintEvent
	// FullName:  CChart::paintEvent
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: QPaintEvent * e
	//************************************
	void paintEvent(QPaintEvent *e);
private:
	QMap<QString,int> list;
};

#endif // CCHART_H
