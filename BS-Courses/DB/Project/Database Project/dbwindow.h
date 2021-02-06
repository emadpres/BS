#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>
#include "ui_dbwindow.h"

#include <QGraphicsView>
#include <vector>

class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class myTable;
class QLineEdit;
class QTextEdit;
class QSqlQuery;
class QLabel;
class QComboBox;


class dbWindow : public QMainWindow
{
	Q_OBJECT

	myTable *resultTable;
	QSqlQuery *query;

	QLineEdit *path;
	QPushButton *save;
	QPushButton *add;
	QPushButton *del;

	QComboBox *combo;

	QTextEdit *box;
	//***********
	
	QPushButton *searchBut;
	
	QLabel *nameLabel, *degreeLabel;
	QLineEdit *name, *degree;

	QLabel *dateFromLabel, *dateToLabel;
	QLineEdit *dateFrom, *dateTo;

	QLabel *shiftLabel, *placeLabel;
	QLineEdit *shift, *place;

	
	QLabel *kindLabel;
	QLineEdit *kind;

	QString curTable;

	void initTable();

	void searchPerson();
	void searchDevice();
	void searchMission();
	void mostUsefulShift();
	void mostSuccessfulMission();
	void dayMostSuccessfulFire();
	void mostLeaders();
	void searchActivity();
	void initDisable();

	//std::vector< std::vector<QLineEdit*> > textLines;
public:
	
	dbWindow(QWidget *parent = 0);
	~dbWindow();

public slots:
	void search();
	void saveTable();
	void runManual();
	void comboChange(int index);
	void addPerson();
	void delPerson();



//private:
//	Ui::dbWindowClass ui;
};

#endif // DBWINDOW_H
