#include "label.h"

label::label() {
    setDefaultTextColor("white");
    QFont f;
    f.setBold(true);
    f.setPixelSize(18);
    setFont(f);
    document()->setDocumentMargin(18);
}

void label::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QStyleOptionGraphicsItem myOption = *option;
    myOption.state &= ~QStyle::State_None;
    QGraphicsTextItem::paint(painter, &myOption, widget);
}
