#ifndef ALIREZA_H
#define ALIREZA_H
#include <QtDeclarative>
#include <QtGui>
#include <QtCore>
class ReminderModel : public QAbstractListModel
{
	Q_OBJECT
public:
	enum DummyRoles {
		TitleRole=Qt::UserRole+1
	};

	ReminderModel(QObject* parent=NULL);
	~ReminderModel();

	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);

private:

	void fillData();
	QStringList m_data;
};
#endif // ALIREZA_H
