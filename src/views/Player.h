#ifndef PLAY_WITH_FIRE_PLAYER_H
#define PLAY_WITH_FIRE_PLAYER_H

#include <QString>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <Qtimer>
#include <QGraphicsItemAnimation>
#include <QStyleOptionGraphicsItem>
#include "Wall.h"




class Player : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
Q_PROPERTY(qreal height READ x WRITE setX)
Q_PROPERTY(qreal width READ y WRITE setY)


private:
    QString name;
    int score{},bombCount{100},lifeCount{5},speed{3},screenWidth,screenHeight,id;
    int positionX, positionY,playerWidth{65},playerHeight{101};
    double bombRadius;
    bool moving{false},isIdle{true};
    QPixmap* pixmaps = new QPixmap[5];
    QPropertyAnimation* xAnimator, *yAnimator;
    QTimer* walkingTimer;
    bool canImove;

public:
    Player(QString name,int x, int y, int screenWIdth, int screenHeight,int id);
    Player(const Player &p);
    void setSpeed(int speed);
    int whichFoot{1},whichPixmap{0},prevPixmap{0};
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
    void setPositionX(int x);
    void setPositionY(int y);
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    //void keyReleaseEvent(QKeyEvent *event);
    void setmoving(bool moving);
    int getHeight();
    int getWidth();

public slots:
void idle();
};






#endif //PLAY_WITH_FIRE_PLAYER_H
