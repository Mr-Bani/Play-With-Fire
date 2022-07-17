
#include "Block.h"

Block::Block(int x, int y,int width,int height,QString type) : positionX(x), positionY(y),width(width),height(height){
 if (type=="Wall"){
        QPixmap pixmap(":/images/wall");
        pixmap = pixmap.scaled(width , height);
        setPixmap(pixmap);
 }
    setPos(positionX,positionY);

}

int Block::getWidth() const {
    return width;
}

void Block::setWidth(int width) {
    Block::width = width;
}

int Block::getHeight() const {
    return height;
}

void Block::setHeight(int height) {
    Block::height = height;
}

int Block::getPositionX() const {
    return positionX;
}

void Block::setPositionX(int positionX) {
    setPos(positionX,positionY);
    this->positionX = positionX;
}

int Block::getPositionY() const {
    return positionY;
}

void Block::setPositionY(int positionY) {
    setPos(positionX,positionY);
    this->positionY = positionY;
}
