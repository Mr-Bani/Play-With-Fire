#include "Game.h"
#include <QDebug>

Game::Game() : QGraphicsView() {
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
    Player* player1 = new Player("player1", 100, 100, width(), height(),2);
    player1->setSpeed(50);
    scene->addItem(player1);
    Player* player2 = new Player("player2", 200, 200, width(), height(),2);
    scene->addItem(player2);
    player2->setSpeed(100);
    setFocus();










}
