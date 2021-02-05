#pragma once

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QVector>


//#include <QqueryExecutor>
//#include <QtCore>
//#include <QSqlError>

class database
{
public:
	database(void);
	~database(void);
	
	QSqlQueryModel *model;
	QDateTime tempdatetime;
	QVector<QString> fill(int resID, QString idCode);

	bool findRoom(QString type,QString numOfBeds);
	int reserveRoom(QString name,QString famliy ,QString idCode ,QString tell ,QString roomID,QString start,QString end);

	void reserveExtensionSearch(QString , QString);
	double retrieveCost(QString , QString);
	QDate retrieveEndTime(QString , QString);
	void updateEndTime(QDate , QString);

	QSqlDatabase db;
	QDate tempdate;
};
