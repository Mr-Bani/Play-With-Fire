//
// Created by Mahdi on 7/13/2022.
//

#include "Player.h"

Player::Player(QString name, int postionX, int positionY):name(name),postionX(postionX), positionY(positionY) {

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
