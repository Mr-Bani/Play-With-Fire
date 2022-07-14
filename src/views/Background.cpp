#include <QGraphicsScene>
#include "Background.h"

Background::Background(QGraphicsItem *parent ) : QGraphicsPixmapItem(parent) {

}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    if (!initialized) {
        auto sceneWidth = scene()->sceneRect().width();
        auto sceneHeight = scene()->sceneRect().height();
        QPixmap pixmap(":/images/bg1");
        pixmap.scaled(sceneWidth, sceneHeight, Qt::IgnoreAspectRatio);
        setPixmap(pixmap);
        setPos(0, 0);


        initialized = true;
    }
}
