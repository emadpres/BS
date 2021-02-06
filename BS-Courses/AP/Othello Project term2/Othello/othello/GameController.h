#pragma once
#include "MBasics.h"
#include <QGraphicsScene>

class OthelloBoard;
class OthelloPlayer;

//this class is game controller
class GameController{
public:
	//constructor which needs scene of graphics to add the board to it
	GameController(QGraphicsScene* scene);
private:
	// this method would be called by board when a human click on an item
	void humanPlay(int x, int y);
	
	QGraphicsScene* scene;
	OthelloBoard* board;
	//�� ǘ��� ���� ���� �� ��� ���
	TURN currentTurn;
	// ����� �������
	OthelloPlayer* player;
	//���� ���� ���� ��� ���� ���
	friend class OthelloBoard;
};