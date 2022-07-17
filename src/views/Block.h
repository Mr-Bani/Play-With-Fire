#ifndef PLAY_WITH_FIRE_BLOCK_H
#define PLAY_WITH_FIRE_BLOCK_H
#include <Qstring>
#include <QGraphicsPixmapItem>

class Block :public QGraphicsPixmapItem{
public:
    Block(int x, int y,int width,int height,QString type);
    Block(const Block &b);
    Block& operator=(const Block &other);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);


private:
    int positionX;
    int positionY;
    int width;
    int height;
public:
    int getPositionX() const;

    void setPositionX(int positionX);

    int getPositionY() const;

    void setPositionY(int positionY);

};


#endif //PLAY_WITH_FIRE_BLOCK_H
