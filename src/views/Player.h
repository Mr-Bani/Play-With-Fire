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
#include <QVector>
#include "Wall.h"
#include <QMap>




class Player : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
Q_PROPERTY(qreal height READ x WRITE setX)
Q_PROPERTY(qreal width READ y WRITE setY)


private:
    QString name,state{"idle"},prevState,character;

    int score{},bombCount{100},lifeCount{5},speed{3},screenWidth,screenHeight,id;
    int positionX, positionY,playerWidth{37},playerHeight{45};
    double bombRadius;
    bool moving{false},isIdle{true};
    QPixmap* pixmaps = new QPixmap[5];
    QPixmap* idlePixmaps,*walkingPixmaps,*runningPixmaps,*deadPixmaps;
    QPropertyAnimation* xAnimator, *yAnimator;
    QTimer* walkingTimer,*pixmapTimer;
    bool canImove,flipped{false};


public:
    Player(QString name,int x, int y, int screenWIdth, int screenHeight,int id,QString character,QMap<QString,QVector<int>> characters);
    Player(const Player &p);
    void setSpeed(int speed);
    int animationDirection{1};
    //dictionary for frame numbers, idle,walk,run,dead;
    QMap<QString,QVector<int>> characters;

    int whichFoot{1},whichPixmap{0},prevPixmap{0},pixmapsCount{};
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
    void readPixmaps();
    void setState(QString state);
    void flip();
    bool isFlipped();


public slots:
void idle();
void setpixmap();
};





#endif //PLAY_WITH_FIRE_PLAYER_H
