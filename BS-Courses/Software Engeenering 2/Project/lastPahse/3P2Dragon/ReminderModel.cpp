#include "ReminderModel.h"


ReminderModel::ReminderModel(QObject *parent) : QAbstractListModel(parent)
{
	m_data.clear();
	QHash<int, QByteArray> roles;
	roles[TitleRole]="name";

	roles[1025]= "notes";
	setRoleNames(roles);
	fillData();
}

ReminderModel::~ReminderModel()
{

}

int ReminderModel::rowCount(const QModelIndex &parent) const
{
	return m_data.count();
}

QVariant ReminderModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();
	if ((index.row()<0) || (index.row()>=m_data.count())) return QVariant();
	if (role==TitleRole)
		return m_data.at(index.row());
	else if (role == 1025)
	{
		QSettings setting("config/reminder.ini",QSettings::IniFormat);

		QStringList notes;

		for (int i = 0 ; i < 100 ; i++)
		{
			QString note =  setting.value(QString(m_data.at(index.row()))+"/"+QString("note%1").arg(i)).toString();
			if (! note.isEmpty())
				notes.append(note);
		}


		return notes;
	}
	return QVariant();
}

void ReminderModel::fillData()
{
	beginResetModel();
	m_data.clear();


	m_data.append("Saturday");
	m_data.append("Sunday");
	m_data.append("Monday");
	m_data.append("Tuesday");
	m_data.append("Wednesday");
	m_data.append("Thursday");
	m_data.append("Friday");

	endResetModel();


}

bool ReminderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	qDebug("SetData called");
	return true;
}

