#include "Button.h"
#include <QFont>
#include <QPainter>
#include <QTextDocument>
Button::Button(int width, int height) :width(width), height(height), QGraphicsTextItem(){
    setDefaultTextColor("black");
    QFont f;
    f.setBold(true);
    f.setPixelSize(15);
    setFont(f);
    setTextWidth(width);
    document()->setDocumentMargin(20);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap(":/images/start");
    pixmap = pixmap.scaled(width,height);
    painter->setBrush(pixmap);
    painter->drawRect(boundingRect());
    setTextWidth(width);
    QGraphicsTextItem::paint(painter, option, widget);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);

    emit onPress();
}
