#ifndef __BASICS_H__
#define __BASICS_H__

#include <QList>

#define BOARD QList< QList < STATE > > 
enum STATE {EMPTY =-2, HOLE, BLACK, WHITE};
#define GAMESIZE 8
#define ITEM_WIDTH 80

#endif
