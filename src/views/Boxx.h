#ifndef PLAY_WITH_FIRE_BOXX_H
#define PLAY_WITH_FIRE_BOXX_H

#include <QGraphicsPixmapItem>
#include "Block.h"
#include "Item.h"
#include <QRandomGenerator>
#include <QDebug>

class Boxx : public Block  {
public:
    Boxx(int x , int y , int width , int height);
    ~Boxx();

private:
    int width;
    int height;
    Item* item;
};


#endif //PLAY_WITH_FIRE_BOXX_H
