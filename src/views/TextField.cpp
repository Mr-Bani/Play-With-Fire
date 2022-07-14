#include "TextField.h"
#include <QFont>
#include <QPainter>
#include <QTextDocument>

TextField::TextField(int width, int height) : width(width), height(height),QGraphicsTextItem(){
    setDefaultTextColor("black");
    QFont f;
    f.setBold(true);
    f.setPixelSize(15);
    setFont(f);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setTextWidth(width);
    document()->setDocumentMargin(18);

}

void TextField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap(":/images/input");
    pixmap = pixmap.scaled(width,height);
    painter->setBrush(pixmap);
    painter->drawRect(boundingRect());
    setTextWidth(width);
    QGraphicsTextItem::paint(painter, option, widget);
}
QRectF TextField :: boundingRect() const {
    auto rect = QGraphicsTextItem :: boundingRect();
    rect.setWidth(width);
    rect.setHeight(height);
    return  rect;}

