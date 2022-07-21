#ifndef PLAY_WITH_FIRE_BOMB_H
#define PLAY_WITH_FIRE_BOMB_H
#include <QGraphicsItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <Qtimer>
#include <QGraphicsItemAnimation>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

class Bomb : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT

private:
    int frame{};
    double explodeTime;
    int positionX,positionY;
    double bombRadius;
    QPixmap pixmap ;
    QTimer* explodTime;
    QTimer* explodTime2;

    QPixmap* pixmaps = new QPixmap[5];
public:
    Bomb(int positionX, int positionY, double bombRadius);
    ~Bomb();
    void setExplodeTime(double explodeTime);
    double getExplodeTime();
    int getPositionX();
    int getPositionY();
    double getBombRadius();


    QRectF boundingRect() const override;



public slots:
    void ex1();
    void ex2();
};

#endif //PLAY_WITH_FIRE_BOMB_H
