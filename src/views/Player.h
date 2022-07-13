#ifndef PLAY_WITH_FIRE_PLAYER_H
#define PLAY_WITH_FIRE_PLAYER_H

#include <QString>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>




class Player : public QGraphicsPixmapItem {
private:
    QString name;
    int score{},bombCount{100},lifeCount{5},speed{3},postionX,positionY;
    double bombRadius;
public:
    Player(QString name, int postionX, int positionY);
    Player(const Player &p);
    void setPosition(int postionX, int positionY);
    void setSpeed(int speed);
    void setBombCount(int bombCount);
    void setLifeCount(int lifeCount);
    void setBombRadius(double bombRadius);
    void setScore(int score);
    void scoreUp(int value);
    int getScore();
    int getBombCount();
    int getLifeCount();
    int getSpeed();
    double getBombRadius();
    QString getName();
    int getPositionX();
    int getPositionY();
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
};






#endif //PLAY_WITH_FIRE_PLAYER_H
