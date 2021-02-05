#include "database.h"
#include <QSqlQuery>
#include <QSqlError>


database::database(void)
{
	//db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setHostName("localhost");
	//db.setDatabaseName("hotelDB");

	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("motel");
	
	if (!db.isValid()){
		QString err ;
		err = db.lastError().text();
		return;
	}

    bool ok = db.open("root","");
	if(ok)
	{
	 model  = new QSqlQueryModel();
	}
	else
	{
		QSqlError errStr ;
		errStr = db.lastError();
	}
}
	
//	

database::~database(void)
{
}


bool database::findRoom(QString type, QString numOfBeds)
{
	QSqlQuery query(db);
	query.prepare("SELECT id , type ,numOfBeds,cost FROM room WHERE isfree = 'true' AND NumOfBeds = ? AND type = ?");
	query.addBindValue(numOfBeds);
	query.addBindValue(type);
	bool ok = query.exec();
	if(ok)
		model->setQuery(query);
	else
		{
			QSqlError err ;
			err = query.lastError();
			QString s = query.lastError().text();
			model->clear();
		}
	return true;
}

int database::reserveRoom(QString name,QString famliy ,QString idCode ,QString tell ,QString roomID,QString start,QString end)
{

	int reserveID = 0;
	QSqlQuery query(db);
	query.prepare("INSERT INTO passenger (name,family,IDCode,tell) VALUES(?,?,?,?)");
	query.addBindValue(name);
	query.addBindValue(famliy);
	query.addBindValue(idCode);
	query.addBindValue(tell);

	bool ok = query.exec();
	if(ok)
	{
		query.clear();
		query.exec("SELECT max(id) FROM passenger");
		int passId = -1;
		while (query.next())
		{
			passId = query.value(0).toInt();
		}
		query.prepare("INSERT INTO reserve (roomID,passID,beginTime,endTime) VALUES(?,?,?,?)");
		query.addBindValue(roomID);
		query.addBindValue(passId);
		query.addBindValue(start);
		query.addBindValue(end);
		if(query.exec())
		{
			query.clear();
			query.prepare("UPDATE room SET isfree = ? WHERE id = ?");
			query.addBindValue(false);
			query.addBindValue(roomID);
			if(query.exec())
			{
				query.clear();
				query.prepare("SELECT max(id) FROM reserve");
				query.exec();
				while (query.next())
				{
					reserveID = query.value(0).toInt();
				}
				return reserveID;
			}
			else
			{
				QSqlError err;
				err = query.lastError();
			}
				return 0;
		}
		else
		{
			QSqlError err;
			err = query.lastError();
		}
			return 0;
	}
	else
	{
		QSqlError err;
		err = query.lastError();
	}
		return 0;
}
void database::reserveExtensionSearch(QString idcode , QString reservecode)
{
	//0012345677456
	QSqlQuery query(db);
	query.clear();


	query.prepare("SELECT name ,family ,tell ,beginTime ,endTime  FROM passenger , reserve WHERE passenger.IDCode = ? and reserve.id = ?  and  passenger.id = reserve.passID  ");
	query.addBindValue( idcode);
	query.addBindValue( reservecode.toInt());
	query.exec();
	model->setQuery(query);

	model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Family");
	model->setHeaderData(2, Qt::Horizontal, "Tell");
	model->setHeaderData(3, Qt::Horizontal, "BeginTime");
}

double database::retrieveCost(QString idcode, QString reservecode)
{
	//model->clear();
	
	QSqlQuery query(db);
	query.clear();
	query.prepare("SELECT cost FROM passenger , reserve ,room WHERE passenger.IDCode = ? and reserve.id = ?  and  passenger.id = reserve.passID  and reserve.roomID = room.id");
	query.addBindValue( idcode);
	query.addBindValue( reservecode.toInt());
	bool isOk =false;
	isOk = query.exec();
	model->setQuery(query);
	double cost = 0.0;

	if(isOk)
	{
		cost = model->data(model->index(0, 0)).toDouble();
		model->clear();
		return cost;
	}
	return -1.0;
}

QDate database::retrieveEndTime(QString idcode, QString reservecode)

{
	QSqlQuery query(db);
	query.clear();
	query.prepare("SELECT endTime  FROM passenger , reserve WHERE passenger.IDCode = ? and reserve.id = ?  and  passenger.id = reserve.passID  ");
	query.addBindValue( idcode);
	query.addBindValue( reservecode.toInt());
	bool isOk =false;
	isOk = query.exec();
	//model->setQuery(query);
	//QString temp;
	
	QDate d;

	if(isOk)
	{
		
		while (query.next()) 
		 {
			bool h =false;

		    QString temp = query.value(0).toString();
			
			d = QDate::fromString(temp ,"dd-MM-yyyy");

			//QString stemp =d.toString("dd-MM-yyyy");

		}
	}

	
	return d;

}

void database::updateEndTime(QDate t , QString reservecode)
{
	////0012345677456
	QSqlQuery query(db);
	query.clear();

	QString tt = t.toString("dd-MM-yyyy");
	
	query.exec("UPDATE reserve SET endTime = ? WHERE id = ?");
	query.addBindValue(tt);
	query.addBindValue( reservecode.toInt());
	
	
	bool isOk =false;
	isOk = query.exec();
	//QSqlError e =query.lastError();
}
QVector<QString> database::fill(int resID, QString idCode)
{
	QSqlQuery query(db);
	query.prepare("SELECT passID, roomID, beginTime, endTime FROM reserve WHERE id = ?");
	query.addBindValue(resID);
	query.exec();
	//QSqlError error;
	//error = query.lastError();
	int passID, roomID;
	QDate d1, d2;
	QString S1, S2;
	while (query.next()) 
	{
		passID = query.value(0).toInt();
		roomID = query.value(1).toInt();
		S1 = query.value(2).toString();
		S2 = query.value(3).toString();
	}
	d1 = d1.fromString(S1, "dd-MM-yyyy");
	d2 = d2.fromString(S2, "dd-MM-yyyy");
	int res = d1.daysTo(d2);
	query.clear();
	query.prepare("SELECT name, family, tell, IDCode FROM passenger WHERE id = ?");
	query.addBindValue(passID);
	query.exec();
	QString name, family, tell, id;
	int cost;
	QVector<QString> v;
	while (query.next()) 
	{
		name = query.value(0).toString();
		family = query.value(1).toString();
		tell = query.value(2).toString();
		id = query.value(3).toString();
	}

	//
	query.clear();
	query.prepare("SELECT cost FROM room WHERE id = ?");
	query.addBindValue(roomID);
	query.exec();
	while (query.next()) 
		cost = query.value(0).toInt();
	

	v.push_back(name);
	v.push_back(family);
	v.push_back(tell);
	v.push_back(id);
	v.push_back( QString::number(cost*res) );
	v.push_back( QString::number(res));
	//is free e roomID bayad true she :D
	query.clear();
	query.prepare("UPDATE room SET isfree = ? WHERE id = ?"); 
	query.addBindValue(true);
	query.addBindValue(roomID);
	query.exec();
	return v;
}

