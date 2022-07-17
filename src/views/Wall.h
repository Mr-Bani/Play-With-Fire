#ifndef PLAY_WITH_FIRE_WALL_H
#define PLAY_WITH_FIRE_WALL_H

#include <QGraphicsPixmapItem>
#include "Block.h"
#include <QGraphicsView>
class Wall: public Block {
public:
    Wall(int x , int y , int width , int height);
};




#endif //PLAY_WITH_FIRE_BOX_H