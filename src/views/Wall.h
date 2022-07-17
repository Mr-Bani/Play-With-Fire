#ifndef PLAY_WITH_FIRE_WALL_H
#define PLAY_WITH_FIRE_WALL_H

#include <QGraphicsPixmapItem>
#include "Block.h"
#include <QGraphicsView>
class Wall: public QGraphicsPixmapItem {
public:
    Wall(int width , int height);

private:
    int width;
    int height;
};




#endif //PLAY_WITH_FIRE_BOX_H