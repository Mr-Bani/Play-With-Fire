#include "Player.h"
#include "QDebug"

Player::Player(QString name, int x, int y, int screenWidth, int screenHeight, int id, QString character, int speed,
               int lives) : id(id), name(name), positionX(x), positionY(y),
                            screenHeight(screenHeight), screenWidth(screenWidth),
                            character(character), speed(speed), lifeCount(lives) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    fillFramesInfo();
    idlePixmaps = new QPixmap[framesInfo[0]];
    walkingPixmaps = new QPixmap[framesInfo[1]];
    runningPixmaps = new QPixmap[framesInfo[2]];
    deadPixmaps = new QPixmap[framesInfo[3]];
    readPixmaps();
    setPixmap(idlePixmaps[0]);
    whichPixmap = 0;
    setState("Idle");
    setPos(x, y);
    pixmapTimer = new QTimer();
    pixmapTimer->setInterval(100);
    pixmapTimer->start();
    playerHeight = pixmap().height();
    playerWidth = pixmap().width();
    connect(pixmapTimer, &QTimer::timeout, this, &Player::setpixmap);
    walkingTimer = new QTimer();
    walkingTimer->setInterval(250);
    walkingTimer->start();
    connect(walkingTimer, &QTimer::timeout, this, &Player::idle);
    itemTimer = new QTimer();

    xAnimator = new QPropertyAnimation(this, "height", this);
    yAnimator = new QPropertyAnimation(this, "width", this);
}

void Player::setSpeed(int speed) {
    this->speed = speed;

}

void Player::setBombCount(int bombCount) {
    this->bombCount = bombCount;

}

void Player::setLifeCount(int lifeCount) {
    this->lifeCount = lifeCount;

}

void Player::setBombRadius(double bombRadius) {
    this->bombRadius = bombRadius;

}

void Player::scoreUp(int value) {
    score += value;

}

int Player::getScore() {
    return score;
}

int Player::getBombCount() {
    return bombCount;
}

int Player::getLifeCount() {
    return lifeCount;
}

int Player::getSpeed() {
    return speed;
}

double Player::getBombRadius() {
    return bombRadius;
}

void Player::setScore(int score) {
    this->score = score;

}

QString Player::getName() {
    return name;
}

int Player::getPositionX() {
    positionX = x();
    return positionX;
}

int Player::getPositionY() {
    positionY = y();
    return positionY;
}

void Player::goUp() {
    if (dead) { return; }
    yAnimator->setStartValue(positionY);
    if (positionY - speed >= 0) {
        positionY -= speed;
    } else {
        positionY = 0;
    }
    yAnimator->setEndValue(positionY);
    yAnimator->setDuration(10);
    yAnimator->start();
    //setPos(positionX,positionY);
}

void Player::goDown() {
    if (dead) { return; }
    positionY = y();
    yAnimator->setStartValue(positionY);
    if (positionY + speed + playerHeight < screenHeight) {
        positionY += speed;
    } else {
        positionY = screenHeight - playerHeight;
    }
    yAnimator->setEndValue(positionY);
    yAnimator->setDuration(10);
    yAnimator->start();

//    setPos(positionX,positionY);



//    qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goLeft() {
    if (dead) { return; }
    xAnimator->setStartValue(positionX);
    if (positionX - speed >= 0) {
        positionX -= speed;
    } else {
        positionX = 0;
    }

    xAnimator->setEndValue(positionX);
    xAnimator->setDuration(10);
    xAnimator->start();
    //setPos(positionX,positionY);

    //  qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goRight() {
    if (dead) { return; }
    positionX = x();
    xAnimator->setStartValue(positionX);
    if (positionX + speed + playerWidth < screenWidth) {
        positionX += speed;
    } else {
        positionX = screenWidth - playerWidth;
    }
    xAnimator->setEndValue(positionX);
    xAnimator->setDuration(10);
    xAnimator->start();

//    setPos(positionX,positionY);



//    qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

Player::Player(const Player &p) {
    name = p.name;
    positionX = p.positionX;
    positionY = p.positionY;
    speed = p.speed;
    bombCount = p.bombCount;
    lifeCount = p.lifeCount;
    bombRadius = p.bombRadius;
    score = p.score;
}


void Player::setPositionX(int x) {
    positionX = x;
}

void Player::setPositionY(int y) {
    positionY = y;
}

void Player::idle() {
    if (isIdle) {
        setState("Idle");
    }
}

void Player::setmoving(bool moving) {
    this->moving = moving;
    isIdle = !moving;
}

int Player::getHeight() {
    return pixmap().height();
}

int Player::getWidth() {
    return pixmap().width();
}

void Player::setpixmap() {
    //qInfo()<<"x: "<<positionX<<" y: "<<positionY<<"\n";
    if (state == "Idle") {
        pixmapTimer->setInterval(70);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= framesInfo[0];
        setPixmap(idlePixmaps[whichPixmap]);;
    } else if (state == "Walking") {
        pixmapTimer->setInterval(20);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= framesInfo[1];
        setPixmap(walkingPixmaps[whichPixmap]);
    } else if (state == "Running") {
        pixmapTimer->setInterval(10);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= framesInfo[2];
        setPixmap(runningPixmaps[whichPixmap]);

    } else if (state == "Dead") {
        pixmapTimer->setInterval(100);
        prevPixmap = whichPixmap;
        whichPixmap++;
        if (whichPixmap == framesInfo[3] - 1) { pixmapTimer->stop(); }
        setPixmap(deadPixmaps[whichPixmap]);
    }


}

void Player::readPixmaps() {
    flipped = false;
    for (int i = 0; i < framesInfo[0]; i++) {
        idlePixmaps[i] = (QPixmap(":/images/" + character + "/idle" + QString::number(i + 1))).scaled(screenHeight / 16,
                                                                                                      screenHeight / 16,
                                                                                                      Qt::IgnoreAspectRatio,
                                                                                                      Qt::SmoothTransformation);

    }
    for (int i = 0; i < framesInfo[1]; i++) {
        walkingPixmaps[i] = (QPixmap(":/images/" + character + "/walk" + QString::number(i + 1))).scaled(
                screenHeight / 16, screenHeight / 16,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation);
    }
    for (int i = 0; i < framesInfo[2]; i++) {
        runningPixmaps[i] = (QPixmap(":/images/" + character + "/run" + QString::number(i + 1))).scaled(
                screenHeight / 16, screenHeight / 16,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation);
    }
    for (int i = 0; i < framesInfo[3]; i++) {
        deadPixmaps[i] = (QPixmap(":/images/" + character + "/dead" + QString::number(i + 1))).scaled(screenHeight / 16,
                                                                                                      screenHeight / 16,
                                                                                                      Qt::IgnoreAspectRatio,
                                                                                                      Qt::SmoothTransformation);
    }

}

void Player::setState(QString state) {
    this->state = state;
}

void Player::flip() {
    flipped = !flipped;
    for (int i = 0; i < framesInfo[0]; i++) {
        idlePixmaps[i] = idlePixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < framesInfo[1]; i++) {
        walkingPixmaps[i] = walkingPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < framesInfo[2]; i++) {
        runningPixmaps[i] = runningPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < framesInfo[3]; i++) {
        deadPixmaps[i] = deadPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }

}


bool Player::isFlipped() {
    return flipped;
}

bool Player::isDroppedBomb() const {
    return droppedBomb;
}

void Player::setDroppedBomb(bool droppedBomb) {
    this->droppedBomb = droppedBomb;
}

void Player::die() {
    isIdle = false;
    setState("Dead");
    setDroppedBomb(true);
    dead = true;
    prevPixmap = whichPixmap;
    whichPixmap = 0;


}

bool Player::isDead() const {
    return dead;
}

void Player::setDead(bool dead) {
    this->dead = dead;
}

void Player::injury() {
    lifeCount--;
    setState("Idle");
    for (int i = 0; i < framesInfo[0]; i += 2) {
        idlePixmaps[i] = QPixmap();
        walkingPixmaps[i] = QPixmap();
        runningPixmaps[i] = QPixmap();
    }
    if (lifeCount == 0) {
        die();
    }
    QTimer::singleShot(1000, this, &Player::readpixampsSlot);

}

void Player::readpixampsSlot() {
    readPixmaps();
}

void Player::fillFramesInfo() {
    if (character == "mike") {
        framesInfo += 15;
        framesInfo += 15;
        framesInfo += 15;
        framesInfo += 15;
    } else if (character == "ansherli") {
        framesInfo += 16;
        framesInfo += 20;
        framesInfo += 20;
        framesInfo += 30;

    } else if (character == "rex") {
        framesInfo += 10;
        framesInfo += 10;
        framesInfo += 8;
        framesInfo += 8;
    } else if (character == "santa") {
        framesInfo += 16;
        framesInfo += 13;
        framesInfo += 9;
        framesInfo += 17;

    }


}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);

    for(QGraphicsItem* object: collidingItems()){
        Item* item = dynamic_cast<Item*>(object);

            if(item!=nullptr){
                if(item->getType()=="infBomb"){
                    itemTimer->setInterval(50);
                    itemTimer->start();
                    connect(itemTimer, &QTimer::timeout, this, &Player::infBomb);
                    QTimer::singleShot(2000,this, &Player::stopItem);

                }
                else if(item->getType()=="heart"){
                    injury();
                    lifeCount+=2;
                }
                else if(item->getType()=="speed"){
                    setSpeed(2*speed);
                    QTimer::singleShot(5000,this,&Player::normalSpeed);
                }
                scene()->removeItem(item);
            }


    }
}

void Player::normalSpeed() {
    speed /= 2;
}

void Player::infBomb() {
    droppedBomb = false;
}

void Player::stopItem() {
    itemTimer->stop();

}

