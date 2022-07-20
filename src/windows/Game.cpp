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

    auto blockWidth = width() / 15;
    auto blockHeight = height() / 15;
    setScene(scene);
    player1 = new Player(name1, blockWidth, blockHeight, width(), height(), 1);
    player1->setSpeed(20);
    scene->addItem(player1);
    setScene(scene);
    player2 = new Player(name2, width() - player1->getWidth() - blockWidth,
                         height() - player1->getHeight() - blockHeight, width(), height(), 2);
    player2->setSpeed(10);
    scene->addItem(player2);
    setFocus();


    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j) {
            if (!(i != 0 && i != 14 && j != 0 && j != 14 && (j%3!= 0 || i%2 !=0) )){
            auto wall = new Wall(blockWidth * i, blockHeight * j, blockWidth, blockHeight);
            scene->addItem(wall);
            boxes.append(*wall);}
        }
    qDebug()<<width()<<height();
    for(int i=0;i<boxes.size();i++){
        qDebug()<<boxes[i].getPositionX()<<boxes[i].getPositionY();
    }
}


void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up) {
        player1->setmoving(true);
        if (player1->getPositionY() > 0 && canMove(player1, "Up")) {
            player1->goUp();
        }
        player1->setmoving(false);


    } else if (event->key() == Qt::Key_Down) {
        player1->setmoving(true);
        if (player1->getPositionY() + player1->getHeight() < height() && canMove(player1, "Down")) {
            player1->goDown();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_Left) {
        player1->setmoving(true);
        if (player1->getPositionX() > 0 && canMove(player1, "Left")) {
            player1->goLeft();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_Right) {
        player1->setmoving(true);
        if (player1->getPositionX() + player1->getWidth() < width() && canMove(player1, "Right")) {
            player1->goRight();
        }
        player1->setmoving(false);
    } else if (event->key() == Qt::Key_W) {
        if (player2->getPositionY() > 0 && canMove(player2, "Up")) {
            player2->goUp();
        }
        player2->setmoving(false);

    } else if (event->key() == Qt::Key_S) {
        player2->setmoving(true);
        if (player2->getPositionY() + player2->getHeight() < height() && canMove(player2, "Down")) {
            player2->goDown();
        }
        player2->setmoving(false);
    } else if (event->key() == Qt::Key_A) {
        player2->setmoving(true);
        if (player2->getPositionX() > 0 && canMove(player2, "Left")) {
            player2->goLeft();
        }
        player2->setmoving(false);
    } else if (event->key() == Qt::Key_D) {
        player2->setmoving(true);
        if (player2->getPositionX() + player2->getWidth() < width() && canMove(player2, "Right")) {
            player2->goRight();
        }
        player2->setmoving(false);
    }

}


bool Game::canMove(Player *player, QString direction) {
    for (auto &box: boxes) {
        if (direction == "Up" && ((box.getPositionX() < player->getPositionX() &&
                                   box.getPositionX() + box.getWidth() > player->getPositionX()) ||
                                  (box.getPositionX() < player->getPositionX() + player->getWidth() &&
                                   box.getPositionX() + box.getWidth() >
                                   player->getPositionX() + player->getWidth()))) {
            if ((box.getPositionY() < player->getPositionY() - player->getSpeed()) &&
                (box.getPositionY() + box.getHeight() > player->getPositionY() - player->getSpeed())) {
                return false;
            }
        } else if (direction == "Down" && ((box.getPositionX() < player->getPositionX() &&
                                            box.getPositionX() + box.getWidth() > player->getPositionX()) ||
                                           (box.getPositionX() < player->getPositionX() + player->getWidth() &&
                                            box.getPositionX() + box.getWidth() >
                                            player->getPositionX() + player->getWidth()))) {
            if ((box.getPositionY() < player->getPositionY() + player->getSpeed() + player->getHeight()) &&
                (box.getPositionY() + box.getHeight() >
                 player->getPositionY() + player->getSpeed() + player->getHeight())) {
                return false;
            }
        } else if (direction == "Left" && ((box.getPositionY() < player->getPositionY() &&
                                            box.getPositionY() + box.getHeight() > player->getPositionY()) ||
                                           (box.getPositionY() < player->getPositionY() + player->getHeight() &&
                                            box.getPositionY() + box.getHeight() >
                                            player->getPositionY() + player->getHeight()))) {
            qDebug()<<"left1\n";
            if ((box.getPositionX() < player->getPositionX() - player->getSpeed()) &&
                (box.getPositionX() + box.getWidth() > player->getPositionX() - player->getSpeed())) {
                qDebug()<<"left2\n";
                return false;
            }
        } else if (direction == "Right" && ((box.getPositionY() <= player->getPositionY() &&
                                             box.getPositionY() + box.getHeight() > player->getPositionY()) ||
                                            (box.getPositionY() < player->getPositionY() + player->getHeight() &&
                                             box.getPositionY() + box.getHeight() >=
                                             player->getPositionY() + player->getHeight()))) {
            qDebug()<<"right1\n";
            if (((box.getPositionX() < player->getPositionX() + player->getSpeed() + player->getWidth()) &&
                 (box.getPositionX() + box.getWidth() >
                  player->getPositionX() + player->getSpeed() + player->getWidth())) ) {
                qDebug()<<"right2\n";
                return false;
            }
        }
    }
    return true;
}
