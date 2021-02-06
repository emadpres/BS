#pragma once

#include "MBasics.h"
#include <QString>
#include <QObject>
#include <QList>
#include <QPair>

class OthelloBoard;
class OthelloPlayer:QObject{
Q_OBJECT
public:
	//Çíä ÓÇÒäÏå ÈÇíÏ ÊæÓØ ˜áÇÓ åÇí İÑÒäÏ ÕÏÇ ÒÏå ÔæäÏ
	OthelloPlayer(OthelloBoard* board,TURN turn){
		this->board = board;
		this->turn = turn;
	}
	
	//äÇã Êíã ÊæÓØ Çíä ãÊæÏ ÈÇíÏ ÈÑÑÏÇäÏå ÔæÏ
	virtual QString getName()=0;
	// äÇã äæíÓäÏÇä ÊæÓØ Çíä ãÊæÏ ÈÇíÏ ÈÑÑÏÇäÏå ÔæÏ
	virtual QList<QString> getAuthors()=0;
	// Çíä ãÊæÏ ÇÕáí ÇÓÊ æ í˜ ÌİÊ ÚÏÏ ÈÑãíÑÏÇäÏ æ ÈÇÒí ÈÚÏí ÎæÏÔ ÑÇ ãÚÑİí ãí˜äÏ
	virtual QPair<int,int> nextPlay()=0;
	
signals:
	//æŞÊí í˜ ÈÇÒí˜ä ÇÒ ÇÏÇãå ÈÇÒí ãäÕÑİ ãíÔæÏ ãíÊæÇäÏ Çíä ÓíäÇá ÑÇ ÇÒ ÎæÏÔ ÇÚáÇã äÏ.
	void dead();

protected:
	OthelloBoard* board;
	TURN turn;
};
