#include "TextField.h"


TextField::TextField(int width, int height) : width(width), height(height),QGraphicsTextItem(){
    setDefaultTextColor("white");
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
    QStyleOptionGraphicsItem myoption = *option;
    myoption.state = QStyle::State_None;
    QGraphicsTextItem::paint(painter, &myoption, widget);
}
QRectF TextField :: boundingRect() const {
    auto rect = QGraphicsTextItem :: boundingRect();
    rect.setWidth(width);
    rect.setHeight(height);
    return  rect;}

