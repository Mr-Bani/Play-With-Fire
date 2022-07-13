//
// Created by Mahdi on 7/13/2022.
//

#include "Player.h"

Player::Player(QString name, int postionX, int positionY):name(name),postionX(postionX), positionY(positionY) {
QPixmap pixmap (":/images/player");
pixmap = pixmap.scaled(100,100);
    setPixmap(pixmap);
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
    return postionX;
}

int Player::getPositionY() {
    return positionY;
}

void Player::goUp() {
    positionY -= speed;
}

void Player::goDown() {
    positionY += speed;
}

void Player::goLeft() {
    postionX -= speed;
}
void Player::goRight() {
    postionX += speed;
}

void Player::setPosition(int postionX, int positionY) {
    this->postionX = postionX;
    this->positionY = positionY;

}
#include "QWidget"
#include "iostream"
using namespace std;



Player::Player(const Player &p) {
    name = p.name;
    postionX = p.postionX;
    positionY = p.positionY;
    speed = p.speed;
    bombCount = p.bombCount;
    lifeCount = p.lifeCount;
    bombRadius = p.bombRadius;
    score = p.score;

}
