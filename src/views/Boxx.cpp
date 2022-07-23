#include "Boxx.h"

Boxx::Boxx(int x, int y, int width, int height) :  Block(x,y,width,height,"Box")  {

}

Boxx::~Boxx() {
    QRandomGenerator generator;
    item = new Item(getPositionX(),getPositionY(),getWidth(),getHeight(),QRandomGenerator::global()->bounded(0,7));
    scene()->addItem(item);
}
