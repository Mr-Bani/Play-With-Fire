 #ifndef PLAY_WITH_FIRE_TEXTFIELD_H
#define PLAY_WITH_FIRE_TEXTFIELD_H
#include <QGraphicsTextItem>



class TextField : public QGraphicsTextItem{
private:
    int width{};
    int height{};
public:
    TextField(int width,int height);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const ;
};


#endif //PLAY_WITH_FIRE_TEXTFIELD_H
