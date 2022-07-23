#ifndef PLAY_WITH_FIRE_ITEM_H
#define PLAY_WITH_FIRE_ITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "Player.h"
#include <QTimer>
#include <QDebug>

class Item: public QGraphicsPixmapItem {
private:
    QString type;
    QPixmap pixmap;
    int positionX,positionY,width,height;

public:
    Item(int x, int y , int width,int height,int rand);
    QString getType();
};



#endif //PLAY_WITH_FIRE_ITEM_H
