#ifndef __OTHELLOPLAYER__
#define __OTHELLOPLAYER__

#include "BASICS.h"
#include <QString>
#include <QObject>
#include <QList>
#include <QPair>

class OthelloBoard;
class OthelloPlayer:QObject{
Q_OBJECT
public:
	//��� ������ ���� ���� ���� ��� ����� ��� ��� ����
	OthelloPlayer(OthelloBoard* board,STATE turn)
	{
		this->board = board;
		this->turn = turn;
	}
	
	STATE getTurn()
	{
		return turn;
	}
	
	//��� ��� ���� ��� ���� ���� �ѐ������ ���
	virtual QString getName()=0;
	// ��� �����ϐ�� ���� ��� ���� ���� �ѐ������ ���
	virtual QList<QString> getAuthors()=0;
	// ��� ���� ���� ��� � � ��� ��� ��������� � ���� ���� ���� �� ����� ����
	virtual QPair<int,int> nextPlay()=0;
	
signals:
	//���� � ����� �� ����� ���� ����� ����� ������� ��� ����� �� �� ���� ����� ��.
	void dead();

protected:
	OthelloBoard* board;
	STATE turn;
};
#endif
