#include "Bomb.h"
#include "../views/Player.h"
#include "../windows/Game.h"


Bomb::Bomb(int positionX, int positionY, double bombRadius):positionX(positionX), positionY(positionY), bombRadius(bombRadius) {
    auto pixmap = new QPixmap(":/images/bomb");
    pixmaps[0] = QPixmap(":/images/ex2");
    pixmaps[1] = QPixmap(":/images/ex3");
    pixmaps[2] = QPixmap(":/images/ex4");
    pixmaps[3] = QPixmap(":/images/ex5");
    auto scaledPixmap = pixmap->scaled(15,15);
    setPixmap(scaledPixmap);




    explodTime = new QTimer();
    explodTime->setInterval(3000);
        connect(explodTime, &QTimer::timeout, this, &Bomb::ex1);
    explodTime->start();
    setPos(positionX, positionY);


    explodTime2 = new QTimer();
    QTimer::singleShot(3000,this, &Bomb::ex2);

}
Bomb::~Bomb() {
    delete explodTime;
}
int Bomb::getPositionX() {
    return positionX;
}

int Bomb::getPositionY() {
    return positionY;
}

void Bomb::setExplodeTime(double explodeTime) {
    this->explodeTime = explodeTime;
}

double Bomb::getExplodeTime() {
    return explodeTime;
}

double Bomb::getBombRadius() {
    return bombRadius;
}

QRectF Bomb::boundingRect() const {
    return QRectF();
}

void Bomb::ex1() {
    auto pixmap = new QPixmap(":/images/ex1");
    auto scaledPixmap = pixmap->scaled(25, 25);
    setPixmap(scaledPixmap);setPos(positionX,positionY);
}

void Bomb::ex2() {
    for (int i = 0; i < 4; i++) {
        setPixmap(pixmaps[i].scaled(25,25));

    }
}




