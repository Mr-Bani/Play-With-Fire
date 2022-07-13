#include "Game.h"

Game::Game(Player player1, Player player2) : QGraphicsView(){
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    //QPixmap pixmap(":/images/bg1");
    //pixmap = pixmap.scaled(height(),width(),Qt::AspectRatioMode::IgnoreAspectRatio);

    auto scene = new QGraphicsScene(this);
    //auto textField = new TextField(150,200);
    //textField->setPlainText("First Name");
    scene->setSceneRect(0,0,width(),height());
    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#41E3F0"));
    setScene(scene);


}
