#include "Game.h"
#include <QDebug>


Game::Game(QString name, QString name1) : QGraphicsView() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    QPixmap pixmap(":/images/input");
    //pixmap.scaled(height(),width(),Qt::AspectRatioMode::KeepAspectRatio);
    auto scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, width(), height());
    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#41E3F0"));
    setScene(scene);
    Player* player1 = new Player("player1", 1, 1, width(), height(),1);
    player1->setSpeed(20);
    scene->addItem(player1);


    auto blockWidth = width()/15;
    auto blockHeight = height()/15;


    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j) {
            if(i !=0 && i!= 14 && j!= 0 && j!=14 &&(j%2 != 0 || i % 2 != 0))
 continue;
            auto wall = new Wall(blockWidth,blockHeight);
            scene->addItem(wall);
            wall->setPos(blockWidth*i,blockHeight*j);
        }
}
