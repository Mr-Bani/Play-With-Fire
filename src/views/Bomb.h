#ifndef PLAY_WITH_FIRE_BOMB_H
#define PLAY_WITH_FIRE_BOMB_H
#include <QGraphicsItem>


class Bomb : public QGraphicsItem
{
private:
    double explodeTime;
    int positionX,positionY;
    double bombRadius;
public:
    Bomb(int positionX, int positionY, double bombRadius);
    void setExplodeTime(double explodeTime);
    double getExplodeTime();
    int getPositionX();
    int getPositionY();
    double getBombRadius();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};



#endif //PLAY_WITH_FIRE_BOMB_H
