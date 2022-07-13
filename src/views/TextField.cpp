#include "TextField.h"
#include <QFont>
#include <QPainter>

TextField::TextField(int width, int height) : width(width), height(height),QGraphicsTextItem(){
    setDefaultTextColor("white");
    QFont f;
    f.setBold(true);
    f.setPixelSize(24);
    setFont(f);
    setTextInteractionFlags(Qt::TextEditorInteraction);

}

void TextField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap(":/images/input");
    pixmap = pixmap.scaled(width,height);


    painter->setBrush(QBrush("#FF8223"));
    painter->drawRect(boundingRect());
    setTextWidth(width);
    QGraphicsTextItem::paint(painter, option, widget);
}


