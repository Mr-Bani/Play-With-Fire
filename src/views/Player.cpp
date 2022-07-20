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
    pixmapTimer->setInterval(50);
    pixmapTimer->start();

    connect(pixmapTimer, &QTimer::timeout, this, &Player::setpixmap);
    walkingTimer = new QTimer();
    walkingTimer->setInterval(250);
    walkingTimer->start();
    connect(walkingTimer, &QTimer::timeout, this, &Player::idle);

//

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
    return positionX;
}

int Player::getPositionY() {
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
    yAnimator->setStartValue(positionY);
    if (positionY + speed + playerHeight <= screenHeight) {
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
    if (isIdle && whichPixmap != 0) {
        setState("Idle");
    }
}

void Player::setmoving(bool moving) {
    this->moving = moving;
    isIdle = !moving;
}

int Player::getHeight() {
    return playerHeight;
}

int Player::getWidth() {
    return playerWidth;
}

void Player::setpixmap() {
    qInfo() << "Working..\n";
    if (state == "Idle") {
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(idlePixmaps[whichPixmap]);

        qInfo() << whichPixmap << "\n";
    } else if (state == "Walking") {
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(walkingPixmaps[whichPixmap]);

        qInfo() << whichPixmap << "\n";
    } else if (state == "Running") {
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(runningPixmaps[whichPixmap]);

        qInfo() << whichPixmap << "\n";
    } else if (state == "Dead") {
        prevPixmap = whichPixmap;
        whichPixmap++;
        whichPixmap %= 15;
        setPixmap(deadPixmaps[whichPixmap]);

        qInfo() << whichPixmap << "\n";


    }


}

void Player::readPixmaps() {
    for (int i = 0; i < 15; i++) {
        idlePixmaps[i] = (QPixmap(":/images/mike-idle" + QString::number(i + 1))).scaled(150, 100, Qt::KeepAspectRatio,
                                                                                         Qt::SmoothTransformation);
    }
    for (int i = 0; i < 15; i++) {
        walkingPixmaps[i] = (QPixmap(":/images/mike-walk" + QString::number(i + 1))).scaled(150, 100,
                                                                                            Qt::KeepAspectRatio,
                                                                                            Qt::SmoothTransformation);
    }
    for (int i = 0; i < 15; i++) {
        runningPixmaps[i] = (QPixmap(":/images/mike-run" + QString::number(i + 1))).scaled(150, 100,
                                                                                           Qt::KeepAspectRatio,
                                                                                           Qt::SmoothTransformation);
    }
    for (int i = 0; i < 15; i++) {
        deadPixmaps[i] = (QPixmap(":/images/mike-dead" + QString::number(i + 1))).scaled(150, 100, Qt::KeepAspectRatio,
                                                                                         Qt::SmoothTransformation);
    }

}

void Player::setState(QString state) {
    this->state = state;
}

void Player::flip() {
    flipped = !flipped;
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

