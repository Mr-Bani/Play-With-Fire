#include "Wall.h"
#include <QGraphicsScene>

Wall::Wall(int width, int height)  {


    QPixmap pixmap(":/images/wall");
    pixmap = pixmap.scaled(width , height);
    setPixmap(pixmap);

}
