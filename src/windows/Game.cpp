#include "Game.h"
#include <QDebug>


Game::Game(QString name1, QString name2) : QGraphicsView() {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();

    QPixmap pixmap(":/images/input");
    //pixmap.scaled(height(),width(),Qt::AspectRatioMode::KeepAspectRatio);
    auto scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width()-10, height()-10);

    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#75FA8D"));

    auto blockWidth = (width()-10) / 15;
    auto blockHeight = (height()-10) / 15;
    setScene(scene);
    QVector<int> mikeVector;
    mikeVector.append(15);
    mikeVector.append(15);
    mikeVector.append(15);
    mikeVector.append(15);
    auto characters = *new QMap<QString, QVector<int>>();
    player1 = new Player(name1, height() / 2 + blockWidth, blockHeight, width(), height(), 1, "mike", characters);
    player1->setSpeed(3);
    scene->addItem(player1);
    setScene(scene);
    player2 = new Player(name2, width() - player1->getWidth() - height() / 2 - blockWidth,
                         height() - player1->getHeight() - blockHeight, width(), height(), 2, "mike", characters);
    player2->setSpeed(4);
    scene->addItem(player2);
    this->installEventFilter(this);
    keyTimer = new QTimer(this);
    keyTimer->setInterval(1);
    connect(keyTimer, &QTimer::timeout, this, &Game::handleKeyPress);
    keyTimer->start();
    setFocus();


/*
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j) {
            if (!(i != 0 && i != 14 && j != 0 && j != 14 && (j%3!= 0 || i%2 !=0) )){
            auto wall = new Wall(blockWidth * (i-1) , blockHeight * j , blockHeight, blockHeight);
            scene->addItem(wall);
            boxes.append(*wall);}
        }
    qDebug()<<width()<<height();
    for(int i=0;i<boxes.size();i++){
        qDebug()<<boxes[i].getPositionX()<<boxes[i].getPositionY();
    }*/
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
            qDebug() << "left1\n";
            if ((box.getPositionX() < player->getPositionX() - player->getSpeed()) &&
                (box.getPositionX() + box.getWidth() > player->getPositionX() - player->getSpeed())) {
                qDebug() << "left2\n";
                return false;
            }
        } else if (direction == "Right" && ((box.getPositionY() <= player->getPositionY() &&
                                             box.getPositionY() + box.getHeight() > player->getPositionY()) ||
                                            (box.getPositionY() < player->getPositionY() + player->getHeight() &&
                                             box.getPositionY() + box.getHeight() >=
                                             player->getPositionY() + player->getHeight()))) {
            if (((box.getPositionX() < player->getPositionX() + player->getSpeed() + player->getWidth()) &&
                 (box.getPositionX() + box.getWidth() >
                  player->getPositionX() + player->getSpeed() + player->getWidth()))) {
                return false;
            }
        }
    }
    return true;
}

bool Game::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        pressedKeys += ((QKeyEvent *) event)->key();
    } else if (event->type() == QEvent::KeyRelease) {
        pressedKeys -= ((QKeyEvent *) event)->key();
    }


    return false;
}

void Game::handleKeyPress() {
    if (pressedKeys.contains(Qt::Key_Up)) {
        player1->setState("Walking");
        if (player1->getPositionY() > 0 && canMove(player1, "Up")) {
            player1->goUp();
        }
    }
    if (pressedKeys.contains(Qt::Key_Down)) {
        player1->setState("Walking");
        if (player1->getPositionY() + player1->getHeight() < height() && canMove(player1, "Down")) {
            player1->goDown();
        }
    }
    if (pressedKeys.contains(Qt::Key_Left)) {
        player1->setState("Walking");
        if (!player1->isFlipped()) { player1->flip(); }
        else {
            if (player1->getPositionX() > 0 && canMove(player1, "Left")) {
                player1->goLeft();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_Right)) {
        player1->setState("Walking");
        if (player1->isFlipped()) { player1->flip(); }
        else {
            if (player1->getPositionX() + player1->getWidth() < width() && canMove(player1, "Right")) {
                player1->goRight();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_W)) {
        player2->setState("Walking");
        if (player2->getPositionY() > 0 && canMove(player2, "Up")) {
            player2->goUp();
        }

    }
    if (pressedKeys.contains(Qt::Key_S)) {
        player2->setState("Walking");
        if (player2->getPositionY() + player2->getHeight() < height() && canMove(player2, "Down")) {
            player2->goDown();
        }
    }
    if (pressedKeys.contains(Qt::Key_A)) {
        player2->setState("Walking");
        if (!player2->isFlipped()) { player2->flip(); }
        else {
            if (player2->getPositionX() > 0 && canMove(player2, "Left")) {
                player2->goLeft();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_D)) {
        player2->setState("Walking");
        if (player2->isFlipped()) { player2->flip(); }
        else {
            if (player2->getPositionX() + player2->getWidth() < width() && canMove(player2, "Right")) {
                player2->goRight();
            }
        }
    }

}

