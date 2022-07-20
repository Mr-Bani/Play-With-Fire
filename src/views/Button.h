
#ifndef PLAY_WITH_FIRE_BUTTON_H
#define PLAY_WITH_FIRE_BUTTON_H
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
class Button : public QGraphicsTextItem{
    Q_OBJECT
private:
    int width{};
    int height{};
public:
    Button(int width ,int height);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    signals:
    void onPress();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //PLAY_WITH_FIRE_BUTTON_H
