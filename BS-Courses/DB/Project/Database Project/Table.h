#ifndef TABLE_H
#define TABLE_H

//#define MAXLINE 100
#include <fstream>
//using std::ifstream;
using std::ofstream;

#include <QTableWidget>

class QSqlQuery;
class myTable : public QTableWidget
{
public:
	myTable( int rows, int columns, QWidget * parent );
	int column, row;
	void load(QSqlQuery*,int , QStringList);
	void save(QString);
	QLineEdit *path;



//	ifstream inputStream;

	
private:


};

#endif
