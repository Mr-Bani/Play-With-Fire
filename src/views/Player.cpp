#include "Player.h"
#include "QDebug"
Player::Player(QString name,int x, int y, int screenWidth, int screenHeight,int id):id(id),name(name),positionX(x),positionY(y),screenHeight(screenHeight), screenWidth(screenWidth) {

    setFlags(GraphicsItemFlag::ItemIsFocusable);
    setFocus();

    pixmaps[0] = QPixmap (":/images/player");
pixmaps[1] = QPixmap (":/images/player-right");
pixmaps[2] = QPixmap (":/images/player-left");
walkingTimer = new QTimer();
walkingTimer->setInterval(500);
walkingTimer->start();
connect(walkingTimer,&QTimer::timeout,this,&Player::idle);
setPixmap(pixmaps[0]);
setPos(x,y);

xAnimator = new QPropertyAnimation(this, "height",this);
yAnimator = new QPropertyAnimation(this, "width",this);
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
    score+= value;

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
    setPixmap(pixmaps[2]);
    whichPixmap=2;
    yAnimator->setStartValue(positionY);
    if (positionY-speed >= 0) {
        positionY -= speed;
    }
    else{
        positionY = 0;
    }
    yAnimator->setEndValue(positionY);
    yAnimator->setDuration(10);
    yAnimator->start();
    //setPos(positionX,positionY);
    //qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goDown() {
    setPixmap(pixmaps[1]);
    whichPixmap=1;
    yAnimator->setStartValue(positionY);
    if (positionY+speed+playerHeight <= screenHeight) {
        positionY += speed;
    }
    else{
        positionY = screenHeight-playerHeight;

    }
    yAnimator->setEndValue(positionY);
    yAnimator->setDuration(10);
    yAnimator->start();

//    setPos(positionX,positionY);



//    qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}

void Player::goLeft() {
    setPixmap(pixmaps[2]);
    whichPixmap=2;
    xAnimator->setStartValue(positionX);
    if (positionX-speed >= 0) {
        positionX -= speed;
    }
    else{
        positionX = 0;
    }

    xAnimator->setEndValue(positionX);
    xAnimator->setDuration(10);
    xAnimator->start();
    //setPos(positionX,positionY);

  //  qInfo()<<positionX<<" " << positionY<<" " << screenWidth<<" " <<screenHeight << " \n";
}
void Player::goRight() {
    setPixmap(pixmaps[1]);
    whichPixmap=1;
    xAnimator->setStartValue(positionX);
    if (positionX+speed+playerWidth <= screenWidth) {
        positionX += speed;
    }
    else{
        positionX = screenWidth-playerWidth;
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


void Player::keyPressEvent(QKeyEvent *event) {
if(id==1){
    if (event->key() == Qt::Key_Up) {
        moving = true;
        if(positionY > 0) {
            goUp();
        }

    } else if (event->key() == Qt::Key_Down) {
        moving = true;
        if (positionY+playerHeight < screenHeight) {
            goDown();
        }
    } else if (event->key() == Qt::Key_Left || event->key()==Qt::Key_A) {
        moving = true;
        if (positionX > 0) {
            goLeft();
        }
    } else if (event->key() == Qt::Key_Right) {
        moving = true;
        if (positionX+playerWidth < screenWidth) {
            goRight();
        }
    }}
else if(id==2){
    if (event->key() == Qt::Key_W) {
        moving = true;
        if(positionY > 0) {
            goUp();
        }

    } else if (event->key() == Qt::Key_S) {
        moving = true;
        if (positionY+playerHeight < screenHeight) {
            goDown();
        }
    } else if (event->key()==Qt::Key_A) {
        moving = true;
        if (positionX > 0) {
            goLeft();
        }
    } else if (event->key() == Qt::Key_D) {
        moving = true;
        if (positionX+playerWidth < screenWidth) {
            goRight();
        }
    }
}
}

void Player::setPositionX(int x) {
    positionX = x;
}
void Player::setPositionY(int y) {
    positionY = y;
}

void Player::idle() {
if(isIdle && whichPixmap!=0){
    setPixmap(pixmaps[0]);
}
}
