
#ifndef PLAY_WITH_FIRE_BACKGROUND_H
#define PLAY_WITH_FIRE_BACKGROUND_H

#include <QGraphicsPixmapItem>


class Background : public QGraphicsPixmapItem {
private:
    bool initialized = false;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    Background(QGraphicsItem * parent = nullptr);
};


#endif //PLAY_WITH_FIRE_BACKGROUND_H
