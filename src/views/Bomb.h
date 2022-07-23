#ifndef PLAY_WITH_FIRE_BOMB_H
#define PLAY_WITH_FIRE_BOMB_H

#include <QString>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QSet>
#include "Player.h"
#include <QPainter>

class Bomb : public QObject,public QGraphicsPixmapItem {
private:
    int positionX, positionY, width, height,whichPixmap{0};
    int radius, explosionTime;
    QPixmap *pixmaps;
    QGraphicsPixmapItem* explosionItems;
    QTimer *explosionTimer;
    Player *player;
    QGraphicsView* game;
    QGraphicsItem* rNear,*lNear,*uNear,*dNear;
    int rDistance,lDistance,uDistance,dDistance;
    QSet<QGraphicsItem*> removingItems;
    int explosionWidth,explosionHeight;
public:
    Q_OBJECT
public slots:
    void explode();
    void explodeit();


public:
    Bomb(Player* player,int x, int y, int bombRadius, int explosionTime,int screenWidth,int screenHeight,QGraphicsView* game);
    ~Bomb();

    int getPositionX() const;

    void setPositionX(int positionX);

    int getPositionY() const;

    void setPositionY(int positionY);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    void nearestObject();

};

#endif // PLAY_WITH_FIRE_BOMB_H