#include "Game.h"
#include <QDebug>

Game::Game() : QGraphicsView() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/input");
    //pixmap.scaled(height(),width(),Qt::AspectRatioMode::KeepAspectRatio);
    auto scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, width(), height());
    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#41E3F0"));

    player1 = new Player("player1", 100, 100, width(), height(), 1);
    player1->setSpeed(20);
    scene->addItem(player1);
    setScene(scene);
    player2 = new Player("player2", 200, 200, width(), height(), 2);
    player2->setSpeed(20);
    scene->addItem(player2);
    setFocus();
    walkingTimer = new QTimer();
    walkingTimer->setInterval(500);
    walkingTimer->start();


}

void Game::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up) {
        player1->setmoving(true);
        if (player1->getPositionY() > 0) {
            player1->goUp();
            player1->setmoving(false);
        }

    } else if (event->key() == Qt::Key_Down) {
        player1->setmoving(true);
        if (player1->getPositionY() + player1->getHeight() < height()) {
            player1->goDown();
            player1->setmoving(false);
        }
    } else if (event->key() == Qt::Key_Left) {
        player1->setmoving(true);
        if (player1->getPositionX() > 0) {
            player1->goLeft();
            player1->setmoving(false);
        }
    } else if (event->key() == Qt::Key_Right) {
        player1->setmoving(true);
        if (player1->getPositionX() + player1->getWidth() < width()) {
            player1->goRight();
            player1->setmoving(false);
        }
    } else if (event->key() == Qt::Key_W) {
        player2->setmoving(true);
        if (player2->getPositionY() > 0) {
            player2->goUp();
            player2->setmoving(false);
        }

    } else if (event->key() == Qt::Key_S) {
        player2->setmoving(true);
        if (player2->getPositionY() + player2->getHeight() < height()) {
            player2->goDown();
            player2->setmoving(false);
        }
    } else if (event->key() == Qt::Key_A) {
        player2->setmoving(true);
        if (player2->getPositionX() > 0) {
            player2->goLeft();
            player2->setmoving(false);
        }
    } else if (event->key() == Qt::Key_D) {
        player2->setmoving(true);
        if (player2->getPositionX() + player2->getWidth() < width()) {
            player2->goRight();
            player2->setmoving(false);
        }
    }

}

