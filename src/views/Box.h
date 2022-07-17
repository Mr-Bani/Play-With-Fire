#ifndef PLAY_WITH_FIRE_BOX_H
#define PLAY_WITH_FIRE_BOX_H

#include <QGraphicsPixmapItem>
#include "Block.h"

class Box : public QGraphicsPixmapItem  {
public:
    Box(int width , int height);

private:
    int width;
    int height;
};


#endif //PLAY_WITH_FIRE_BOX_H
