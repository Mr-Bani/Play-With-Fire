
#ifndef PLAY_WITH_FIRE_LABEL_H
#define PLAY_WITH_FIRE_LABEL_H
#include <QGraphicsTextItem>
#include <QFont>
#include <QTextDocument>
#include <QPainter>
#include "QStyleOptionGraphicsItem"
#include <QTextDocument>

class label : public QGraphicsTextItem {
public:
    label();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};


#endif //PLAY_WITH_FIRE_LABEL_H

