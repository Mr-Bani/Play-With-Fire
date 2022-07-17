#include "Game.h"
#include <QDebug>


Game::Game(QString name1, QString name2) : QGraphicsView() {
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
    player1 = new Player(name1, 0, 0, width(), height(), 1);
    player1->setSpeed(10);
    scene->addItem(player1);
    setScene(scene);
    player2 = new Player(name2, width()-player1->getWidth(), height()-player1->getHeight(), width(), height(), 2);
    player2->setSpeed(5);
    scene->addItem(player2);
    setFocus();

    auto blockWidth = width()/15;
    auto blockHeight = height()/15;


    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j) {
            if(i !=0 && i!= 14 && j!= 0 && j!=14 &&(j%3 != 0 || i % 4 == 0))
                continue;
            auto wall = new Wall(blockWidth*i,blockHeight*j,blockWidth,blockHeight);
            scene->addItem(wall);
        }
}














    void Game::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up) {
        player1->setmoving(true);
        if (player1->getPositionY() > 0) {
            player1->goUp();
        }
        player1->setmoving(false);

    } else if (event->key() == Qt::Key_Down) {
        player1->setmoving(true);
        if (player1->getPositionY() + player1->getHeight() < height()) {
            player1->goDown();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_Left) {
        player1->setmoving(true);
        if (player1->getPositionX() > 0) {
            player1->goLeft();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_Right) {
        player1->setmoving(true);
        if (player1->getPositionX() + player1->getWidth() < width()) {
            player1->goRight();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_W) {
        player2->setmoving(true);
        if (player2->getPositionY() > 0) {
            player2->goUp();
        }
        player2->setmoving(false);

    } else if (event->key() == Qt::Key_S) {
        player2->setmoving(true);
        if (player2->getPositionY() + player2->getHeight() < height()) {
            player2->goDown();
        }
        player2->setmoving(false);
    } else if (event->key() == Qt::Key_A) {
        player2->setmoving(true);
        if (player2->getPositionX() > 0) {
            player2->goLeft();
        }
        player2->setmoving(false);
    } else if (event->key() == Qt::Key_D) {
        player2->setmoving(true);
        if (player2->getPositionX() + player2->getWidth() < width()) {
            player2->goRight();
        }
        player2->setmoving(false);
    }

}

