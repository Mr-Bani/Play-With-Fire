#include "Bomb.h"
#include "Boxx.h"


Bomb::Bomb(Player *player, int x, int y, int bombRadius, int explosionTime, int screenWidth, int screenHeight,
           QGraphicsView *game) : player(player), positionX(x), positionY(y), width(0), height(0), radius(bombRadius),
                                  explosionTime(explosionTime), game(game) {
    pixmaps = new QPixmap[6];
    pixmaps[0] = QPixmap(":/images/bomb").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation);
    pixmaps[1] = QPixmap(":/images/explosion1").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
    pixmaps[2] = QPixmap(":/images/explosion2").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
    pixmaps[3] = QPixmap(":/images/explosion3").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
    pixmaps[4] = QPixmap(":/images/explosion4").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
    pixmaps[5] = QPixmap(":/images/explosion5").scaled(screenWidth / 25, screenHeight / 25, Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation);
    setPixmap(pixmaps[0]);
    setPos(x, y);
    height = pixmaps[0].height();
    width = pixmaps[0].width();
    player->setDroppedBomb(true);
    explosionTimer = new QTimer();
    explosionTimer->setInterval(100);
    QTimer::singleShot(explosionTime * 1000, this, &Bomb::explodeit);
    connect(explosionTimer, &QTimer::timeout, this, &Bomb::explode);
    rDistance = lDistance = uDistance = dDistance = screenWidth;
    explosionWidth = pixmaps[5].width();
    explosionHeight = pixmaps[5].height();


}

void Bomb::explode() {
    if (whichPixmap < 5) {
        setPixmap(pixmaps[++whichPixmap]);
        for(int i=1;i<rDistance+lDistance+uDistance+dDistance;i++){
        explosionItems[i].setPixmap(pixmaps[whichPixmap]);}

    } else {
        explosionTimer->stop();
        player->setDroppedBomb(false);
        delete this;
    }
}

void Bomb::explodeit() {
    nearestObject();
    explosionTimer->start();
    explosionItems = new QGraphicsPixmapItem[rDistance+lDistance+uDistance+dDistance];
    for(int i=1;i<rDistance;i++){
        explosionItems[i].setPos(positionX+i*explosionWidth,positionY);
        game->scene()->addItem(&explosionItems[i]);
    }
    for(int i=0;i<lDistance;i++){
        explosionItems[i+rDistance].setPos(positionX-i*explosionWidth,positionY);
        game->scene()->addItem(&explosionItems[i+rDistance]);
    }
    for(int i=0;i<uDistance;i++){
        explosionItems[i+rDistance+lDistance].setPos(positionX,positionY-i*explosionHeight);
        game->scene()->addItem(&explosionItems[i+rDistance+lDistance]);
    }for(int i=0;i<dDistance;i++){
        explosionItems[i+rDistance+lDistance+uDistance].setPos(positionX,positionY+i*explosionHeight);
        game->scene()->addItem(&explosionItems[i+rDistance+ lDistance+uDistance]);
    }
    for (auto &item: removingItems) {

            auto playerr = dynamic_cast<Player*>(item);
        if(playerr!= nullptr){
            if(player!=playerr){player->scoreUp(50);}
            playerr->injury();
        }
        else{
            player->scoreUp(5);
            delete item;}
    }
}

Bomb::~Bomb() {
    delete explosionTimer;
    for(int i=1;i<rDistance+lDistance+uDistance+dDistance;i++){
        game->scene()->removeItem(&explosionItems[i]);
    }
    delete [] explosionItems;
    delete[] pixmaps;


}

int Bomb::getPositionX() const {
    return positionX;
}

void Bomb::setPositionX(int positionX) {
    Bomb::positionX = positionX;
}

int Bomb::getPositionY() const {
    return positionY;
}

void Bomb::setPositionY(int positionY) {
    Bomb::positionY = positionY;
}

int Bomb::getWidth() const {
    return width;
}

void Bomb::setWidth(int width) {
    Bomb::width = width;
}

int Bomb::getHeight() const {
    return height;
}

void Bomb::setHeight(int height) {
    Bomb::height = height;
}

void Bomb::nearestObject() {

    for (auto &item: game->items()) {
        Boxx* item1 = dynamic_cast<Boxx *>(item);

        if(item1!= nullptr){

        if (item1->y() <= positionY && item1->y() + item1->getHeight() >= positionY && item->x()>positionX && item->x() - positionX < rDistance) {
            rDistance = item->x() - positionX;
            rNear = item;
        } else if (item1->y() <= positionY && item1->y() + item1->getHeight() >= positionY && item->x() < positionX &&
                   positionX - item->x() < lDistance) {
            lDistance = positionX - item->x();
            lNear = item;
        } else if (item1->x() <= positionX && item1->x() + item1->getWidth() >= positionX && item->y() < positionY &&
                   positionY - item->y() < uDistance) {
            uDistance =positionY - item->y();
            uNear = item;
        } else if (item1->x() < positionX && item1->x() + item1->getWidth() > positionX && item->y() > positionY &&
                   positionY - item->y() < dDistance) {
            dDistance =  item->y() - positionY;
            dNear = item;
        }}
        else{
            Player* item2 = dynamic_cast<Player*>(item);
            if(item2==nullptr){
                continue;
            }
            if (item2->y() <= positionY && item2->y() + item2->getHeight() >= positionY && item->x()>positionX && item->x() - positionX < rDistance) {
                rDistance = item->x() - positionX;
                rNear = item;
            } else if (item2->y() <= positionY && item2->y() + item2->getHeight() >= positionY && item->x() < positionX &&
                       positionX - item->x() < lDistance) {
                lDistance = positionX - item->x();
                lNear = item;
            } else if (item2->x() <= positionX && item2->x() + item2->getWidth() >= positionX && item->y() < positionY &&
                       positionY - item->y() < uDistance) {
                uDistance =positionY - item->y();
                uNear = item;
            } else if (item2->x() < positionX && item2->x() + item2->getWidth() > positionX && item->y() > positionY &&
                       positionY - item->y() < dDistance) {
                dDistance =  item->y() - positionY;
                dNear = item;
            }}


    }

    if (rDistance > radius * width) {
        rNear = nullptr;
        rDistance = radius;
    }
    else{
        rDistance /=width;
        rDistance++;
    }
    if (lDistance > radius * width) {
        lNear = nullptr;
        lDistance = radius;
    }
    else{
        lDistance /=width;
        lDistance++;
    }
    if (uDistance > radius * height) {
        uNear = nullptr;
        uDistance = radius;
    }
    else{
        uDistance /=height;
        uDistance++;
    }
    if (dDistance > radius * height) {
        dNear = nullptr;
        dDistance = radius;
    }
    else{
        dDistance /=height;
        dDistance++;
    }
    if (rNear != nullptr) {
        removingItems += rNear;
    }
    if (lNear != nullptr) {
        removingItems += lNear;
            }
    if (uNear != nullptr) {
        removingItems += uNear;
    }
    if (dNear != nullptr) {
        removingItems += dNear;
    }


}





