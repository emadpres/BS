#pragma once
#include "mbasics.h"
#include <QGraphicsScene>
#include <QTimer>

class OthelloBoard;
class OthelloPlayer;

//this class is game controller
class GameController:public QObject{
Q_OBJECT
public:
	//constructor which needs scene of graphics to add the board to it
	GameController(QGraphicsScene* scene);
public slots:
	void agentTimer();
private:
	// this method would be called by board when a human click on an item
	void humanPlay(int x, int y);
	
	QTimer* timer;

	QGraphicsScene* scene;
	OthelloBoard* board;
	//�� ǘ��� ���� ���� �� ��� ���
	TURN currentTurn;
	// ����� �������
	OthelloPlayer* player;
	//���� ���� ���� ��� ���� ���
	friend class OthelloBoard;
};
