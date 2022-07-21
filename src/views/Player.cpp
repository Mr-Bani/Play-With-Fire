#include "Player.h"
#include "QDebug"

Player::Player(QString name, int x, int y, int screenWidth, int screenHeight, int id, QString character,
               QMap<QString, QVector<int>> characters) : id(id), name(name), positionX(x), positionY(y),
                                                         screenHeight(screenHeight), screenWidth(screenWidth),
                                                         character(character) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->characters = characters;
    idlePixmaps = new QPixmap[15];
    walkingPixmaps = new QPixmap[15];
    runningPixmaps = new QPixmap[15];
    deadPixmaps = new QPixmap[15];
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
    positionX=x();
    return positionX;
}

int Player::getPositionY() {
    positionY= y();
    return positionY;
}

void Player::goUp() {
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
    //qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goDown() {
    positionY=y();
    yAnimator->setStartValue(positionY);
    qInfo()<<"positionY: " << positionY<<"player height: " <<playerHeight<< " screenHeight: "<<screenHeight << "Speed" << speed <<"\n";
    if (positionY + speed + playerHeight < screenHeight) {
        positionY += speed;
        qInfo()<<"Here\n";
    } else {
        positionY = screenHeight - playerHeight;
        qInfo()<<"there\n";
    }
    yAnimator->setEndValue(positionY);
    yAnimator->setDuration(10);
    yAnimator->start();

//    setPos(positionX,positionY);



//    qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goLeft() {
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
    xAnimator->setStartValue(positionX);
    if (positionX + speed + playerWidth <= screenWidth) {
        positionX += speed;
    } else {
        positionX = screenWidth - playerWidth;
    }

    xAnimator->setEndValue(positionX);
    xAnimator->setDuration(10);
    xAnimator->start();
    //setPos(positionX,positionY);
    // qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
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
        pixmapTimer->setInterval(100);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(idlePixmaps[whichPixmap]);;
    } else if (state == "Walking") {
        pixmapTimer->setInterval(20);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(walkingPixmaps[whichPixmap]);
    } else if (state == "Running") {
        pixmapTimer->setInterval(10);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(runningPixmaps[whichPixmap]);

    } else if (state == "Dead") {
        pixmapTimer->setInterval(200);
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(deadPixmaps[whichPixmap]);
    }


}

void Player::readPixmaps() {
    for (int i = 0; i < 15; i++) {
        idlePixmaps[i] = (QPixmap(":/images/mike-idle" + QString::number(i + 1))).scaled(screenHeight/16, screenHeight/16, Qt::IgnoreAspectRatio,
                                                                                         Qt::SmoothTransformation);

    }
    for (int i = 0; i < 15; i++) {
        walkingPixmaps[i] = (QPixmap(":/images/mike-walk" + QString::number(i + 1))).scaled(screenHeight/16, screenHeight/16,
                                                                                            Qt::IgnoreAspectRatio,
                                                                                            Qt::SmoothTransformation);
    }
    for (int i = 0; i < 15; i++) {
        runningPixmaps[i] = (QPixmap(":/images/mike-run" + QString::number(i + 1))).scaled(screenHeight/16, screenHeight/16,
                                                                                           Qt::IgnoreAspectRatio,
                                                                                           Qt::SmoothTransformation);
    }
    for (int i = 0; i < 15; i++) {
        deadPixmaps[i] = (QPixmap(":/images/mike-dead" + QString::number(i + 1))).scaled(screenHeight/16, screenHeight/16, Qt::IgnoreAspectRatio,
                                                                                         Qt::SmoothTransformation);
    }

}

void Player::setState(QString state) {
    this->state = state;
    }

void Player::flip() {
    flipped = !flipped;
    qInfo() << "PositionX: " << positionX << "PositionY: " << positionY << "\n";
    for (int i = 0; i < 15; i++) {
        idlePixmaps[i] = idlePixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < 15; i++) {
        walkingPixmaps[i] = walkingPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < 15; i++) {
        runningPixmaps[i] = runningPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }
    for (int i = 0; i < 15; i++) {
        deadPixmaps[i] = deadPixmaps[i].transformed(QTransform::fromScale(-1, 1));
    }

}



bool Player::isFlipped() {
    return flipped;
}

