#ifndef PLAY_WITH_FIRE_PLAYER_H
#define PLAY_WITH_FIRE_PLAYER_H

#include <QString>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>



class Player : public QGraphicsItem {
private:
    QString name;
    int score,bombCount,lifeCount,speed,postionX,positionY;
    double bombRadius;
public:
    Player(QString name, int postionX, int positionY);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
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
};



};


#endif //PLAY_WITH_FIRE_PLAYER_H
