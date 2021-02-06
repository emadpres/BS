#include <QTableWidget>
#include <QTableWidgetItem>
#include "Table.h"
#include <QLabel>
#include <QStringList>

#include <string.h>
#include <QSqlQuery>
#include <QTableWidgetItem>

using namespace std;




myTable::myTable( int _rows, int _columns, QWidget * parent = 0 )
	: QTableWidget(_rows,_columns,parent)
{
	

	/***********Table Intil*****************/	
	column=_columns;
	this->setColumnCount(column);

	row = _rows ;
	this->setRowCount(row);

	/***********Table Headers *****************/	
	QStringList Headers;
	Headers<<"Name"<<"Family"<<"ID"<<"Tel No.";
	setHorizontalHeaderLabels(Headers);

}

void myTable::load(QSqlQuery *query,int _column, QStringList _headers)
{
	this->show();
	this->setRowCount(0);	
	this->setColumnCount(_column);
	setHorizontalHeaderLabels(_headers);
	
	if(	_column < 0)
	{
		this->setRowCount(1);
		this->setColumnCount(1);
		setHorizontalHeaderItem(0,new QTableWidgetItem ("Error"));
		this->setItem(0,0,new QTableWidgetItem ("BAD QUERY !!")); 
		return;
	}
	int row=0;
	while (query->next()) 
	{
		this->insertRow(row);
		row++;
		
		for(int i=0;i<_column;i++)
		{
			this->setItem(row-1,i,new QTableWidgetItem (query->value(i).toString()));  //Improtant
		}
	}
	//this->setMinimumSize(this->columnCount()*10,rowCount()*5);

}
void myTable::save(QString fileName)
{

/*	ofstream outStream((fileName+".txt").data());
	if(outStream)
	{
		bool lastRow=0;

		for(int i=0; i<rowCount() ;i++)
		{
			for(int j=0;j<columnCount();j++)
			{
				if(item(i,j))
				{
					string a=(item(i,j))->text().toStdString();
					outStream <<a<<";";
				}
				else
					outStream<<";";
			}

			outStream <<std::endl;
		}
		

	}//endof if(OutStream)
	outStream.close();*/
}