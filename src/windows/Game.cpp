#include "Game.h"
#include <QDebug>


Game::Game(QString name1, QString character1, QString name2, QString character2, int lives) : QGraphicsView() {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();


    //pixmap.scaled(height(),width(),Qt::AspectRatioMode::KeepAspectRatio);
    auto scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width() - 10, height() - 10);

    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#75FA8D"));



    auto blockWidth = (width()) / 15;
    auto blockHeight = (height() - height() / 10) / 12;
    setScene(scene);
    qInfo()<<"hi";
    player1 = new Player(name1, blockWidth+5, blockHeight+5, width(), height(), 1, character1, 3, lives);
    scene->addItem(player1);
    setScene(scene);
    player2 = new Player(name2, width() - player1->getWidth() - blockWidth - 5,
                         height() - player1->getHeight() - blockHeight - height()/10 - 5 , width(), height(), 2, character2, 3, lives);
    scene->addItem(player2);
    this->installEventFilter(this);
    keyTimer = new QTimer(this);
    keyTimer->setInterval(1);
    connect(keyTimer, &QTimer::timeout, this, &Game::handleKeyPress);
    keyTimer->start();
    setFocus();

    Score1 = new label();
    Score1->setPlainText(player1->getName()+" Score:"+ QString::number(player2->getScore())  +" Lives: "+QString::number(player1->getLifeCount()));
    scene->addItem(Score1);

    Score2 = new label();
    Score2->setPlainText(player2->getName()+" Score: 0 Lives: "+QString::number(player2->getLifeCount()));
    scene->addItem(Score2);
    Score1->setPos((width()/8),height() - height()/9);
    Score1->setDefaultTextColor("red");
    Score2->setPos(width()-width()/5,height() - height()/9);
    Score2->setDefaultTextColor("red");
    scoreTimer = new QTimer();
    scoreTimer->setInterval(10);
    scoreTimer->start();
    connect(scoreTimer, &QTimer::timeout, this, &Game::updateScores);



    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i == 0 || i == 14 || j == 0 || j == 11) {
                auto wall = new Wall(blockWidth * (i), blockHeight * j, blockWidth, blockHeight);
                scene->addItem(wall);
                blocks.append(*wall);
            }
            else if((i==1 || i==13)&&(j!=1 && j!=10 &&j!=2 && j!=9) || ((j==2 || j==10)&&(i>=3 && i<=11))){
                auto box = new Boxx(blockWidth * (i), blockHeight * j, blockWidth, blockHeight);
                scene->addItem(box);
                blocks.append(*box);
            }
            else if(j!=1 && j!=10 &&j!=2 && j!=9 && i%2==1){
                auto box = new Boxx(blockWidth * (i), blockHeight * j, blockWidth, blockHeight);
                scene->addItem(box);
                blocks.append(*box);
            }
            else if(i%2==0 &&j%2==1){
                auto wall = new Wall(blockWidth * (i), blockHeight * j, blockWidth, blockHeight);
                scene->addItem(wall);
                blocks.append(*wall);
            }


        }
    }

}


bool Game::canMove(Player *player, QString direction) {
    for (auto &item: items()) {
        Block *block = dynamic_cast<Block *>(item);
        if (block != nullptr) {

            if (direction == "Up" && ((block->getPositionX() < player->getPositionX() &&
                                       block->getPositionX() + block->getWidth() > player->getPositionX()) ||
                                      (block->getPositionX() < player->getPositionX() + player->getWidth() &&
                                       block->getPositionX() + block->getWidth() >
                                       player->getPositionX() + player->getWidth()))) {
                if ((block->getPositionY() < player->getPositionY() - player->getSpeed()) &&
                    (block->getPositionY() + block->getHeight() > player->getPositionY() - player->getSpeed())) {
                    return false;
                }
            } else if (direction == "Down" && ((block->getPositionX() < player->getPositionX() &&
                                                block->getPositionX() + block->getWidth() > player->getPositionX()) ||
                                               (block->getPositionX() < player->getPositionX() + player->getWidth() &&
                                                block->getPositionX() + block->getWidth() >
                                                player->getPositionX() + player->getWidth()))) {
                if ((block->getPositionY() < player->getPositionY() + player->getSpeed() + player->getHeight()) &&
                    (block->getPositionY() + block->getHeight() >
                     player->getPositionY() + player->getSpeed() + player->getHeight())) {
                    return false;
                }
            } else if (direction == "Left" && ((block->getPositionY() < player->getPositionY() &&
                                                block->getPositionY() + block->getHeight() > player->getPositionY()) ||
                                               (block->getPositionY() < player->getPositionY() + player->getHeight() &&
                                                block->getPositionY() + block->getHeight() >
                                                player->getPositionY() + player->getHeight()))) {

                if ((block->getPositionX() < player->getPositionX() - player->getSpeed()) &&
                    (block->getPositionX() + block->getWidth() > player->getPositionX() - player->getSpeed())) {
                    return false;
                }
            } else if (direction == "Right" && ((block->getPositionY() < player->getPositionY() &&
                                                 block->getPositionY() + block->getHeight() > player->getPositionY()) ||
                                                (block->getPositionY() < player->getPositionY() + player->getHeight() &&
                                                 block->getPositionY() + block->getHeight() >
                                                 player->getPositionY() + player->getHeight()))) {
                if ((block->getPositionX() < player->getPositionX() + player->getSpeed() + player->getWidth()) &&
                    (block->getPositionX() + block->getWidth() >
                     player->getPositionX() + player->getSpeed() + player->getWidth())) {
                    return false;
                }
            }
        } else {
            Bomb *bomb = dynamic_cast<Bomb *>(item);
            if (bomb != nullptr) { continue; }
            Player *p = dynamic_cast<Player *>(item);

            if (p != nullptr) {
                if (direction == "Up" && ((p->getPositionX() < player->getPositionX() &&
                                           p->getPositionX() + p->getWidth() > player->getPositionX()) ||
                                          (p->getPositionX() < player->getPositionX() + player->getWidth() &&
                                           p->getPositionX() + p->getWidth() >
                                           player->getPositionX() + player->getWidth()))) {
                    if ((p->getPositionY() < player->getPositionY() - player->getSpeed()) &&
                        (p->getPositionY() + p->getHeight() > player->getPositionY() - player->getSpeed())) {
                        return false;
                    }
                } else if (direction == "Down" && ((p->getPositionX() < player->getPositionX() &&
                                                    p->getPositionX() + p->getWidth() > player->getPositionX()) ||
                                                   (p->getPositionX() <
                                                    player->getPositionX() + player->getWidth() &&
                                                    p->getPositionX() + p->getWidth() >
                                                    player->getPositionX() + player->getWidth()))) {
                    if ((p->getPositionY() < player->getPositionY() + player->getSpeed() + player->getHeight()) &&
                        (p->getPositionY() + p->getHeight() >
                         player->getPositionY() + player->getSpeed() + player->getHeight())) {
                        return false;
                    }
                } else if (direction == "Left" && ((p->getPositionY() < player->getPositionY() &&
                                                    p->getPositionY() + p->getHeight() > player->getPositionY()) ||
                                                   (p->getPositionY() <
                                                    player->getPositionY() + player->getHeight() &&
                                                    p->getPositionY() + p->getHeight() >
                                                    player->getPositionY() + player->getHeight()))) {

                    if ((p->getPositionX() < player->getPositionX() - player->getSpeed()) &&
                        (p->getPositionX() + p->getWidth() > player->getPositionX() - player->getSpeed())) {
                        return false;
                    }
                } else if (direction == "Right" && ((p->getPositionY() < player->getPositionY() &&
                                                     p->getPositionY() + p->getHeight() > player->getPositionY()) ||
                                                    (p->getPositionY() <
                                                     player->getPositionY() + player->getHeight() &&
                                                     p->getPositionY() + p->getHeight() >
                                                     player->getPositionY() + player->getHeight()))) {
                    if (((p->getPositionX() < player->getPositionX() + player->getSpeed() + player->getWidth()) &&
                         (p->getPositionX() + p->getWidth() >
                          player->getPositionX() + player->getSpeed() + player->getWidth()))) {
                        return false;
                    }
                }
            } else {

                continue;
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
    if (pressedKeys.contains(Qt::Key_Up) && !player1->isDead()) {
        player1->setState("Walking");
        if (player1->getPositionY() > 0 && canMove(player1, "Up")) {
            player1->goUp();
        }
    }
    if (pressedKeys.contains(Qt::Key_Down) && !player1->isDead()) {
        player1->setState("Walking");
        if (player1->getPositionY() + player1->getHeight() < height() && canMove(player1, "Down")) {
            player1->goDown();
        }
    }
    if (pressedKeys.contains(Qt::Key_Left) && !player1->isDead()) {
        player1->setState("Walking");
        if (!player1->isFlipped()) { player1->flip(); }
        else {
            if (player1->getPositionX() > 0 && canMove(player1, "Left")) {
                player1->goLeft();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_Right) && !player1->isDead()) {
        player1->setState("Walking");
        if (player1->isFlipped()) { player1->flip(); }
        else {
            if (player1->getPositionX() + player1->getWidth() < width() && canMove(player1, "Right")) {
                player1->goRight();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_W) && !player2->isDead()) {
        player2->setState("Walking");
        if (player2->getPositionY() > 0 && canMove(player2, "Up")) {
            player2->goUp();
        }

    }
    if (pressedKeys.contains(Qt::Key_S) && !player2->isDead()) {
        player2->setState("Walking");
        if (player2->getPositionY() + player2->getHeight() < height() && canMove(player2, "Down")) {
            player2->goDown();
        }
    }
    if (pressedKeys.contains(Qt::Key_A) && !player2->isDead()) {
        player2->setState("Walking");
        if (!player2->isFlipped()) { player2->flip(); }
        else {
            if (player2->getPositionX() > 0 && canMove(player2, "Left")) {
                player2->goLeft();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_D) && !player2->isDead()) {
        player2->setState("Walking");
        if (player2->isFlipped()) { player2->flip(); }
        else {
            if (player2->getPositionX() + player2->getWidth() < width() && canMove(player2, "Right")) {
                player2->goRight();
            }
        }
    }
    if (pressedKeys.contains(Qt::Key_Space) && !player2->isDroppedBomb() && !player2->isDead()) {
        auto bomb = new Bomb(player2, player2->getPositionX(), player2->getPositionY() + player2->getHeight() / 3,
                             player2->getBombRadius(), 2, width(), height(), this);
        scene()->addItem(bomb);
    }
    if (pressedKeys.contains(Qt::Key_Shift) && !player1->isDroppedBomb() && !player1->isDead()) {
        auto bomb = new Bomb(player1, player1->getPositionX(), player1->getPositionY() + player1->getHeight() / 3,
                             player1->getBombRadius(), 2, width(), height(), this);
        scene()->addItem(bomb);
    }

}

void Game::updateScores() {
    Score1->setPlainText(player1->getName()+" Score:"+ QString::number(player2->getScore())  +" Lives: "+QString::number(player1->getLifeCount()));
    Score2->setPlainText(player2->getName()+" Score: 0 Lives: "+QString::number(player2->getLifeCount()));
    if(player1->getLifeCount() == 0 && player2->getLifeCount() != 0){
        scoreBoard = new ScoreBoard(player2->getName(), player2->getScore(),player1->getName(), player1->getScore());
        close();
    }
    else if(player2->getLifeCount() == 0 && player1->getLifeCount() != 0){
        scoreBoard = new ScoreBoard(player1->getName(), player1->getScore(),player2->getName(), player2->getScore());
        close();

    }
}

