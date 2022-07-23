#ifndef PLAY_WITH_FIRE_GAME_H
#define PLAY_WITH_FIRE_GAME_H

#include <QGraphicsView>
#include <QString>
#include "../views/Player.h"
#include "../views/Boxx.h"
#include "../views/Wall.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QSet>
#include "../views/Bomb.h"
#include "../views/Label.h"
#include "ScoreBoard.h"

class Game : public QGraphicsView {
Q_OBJECT
public:
    Player *player1, *player2;
    QTimer *walkingTimer, *keyTimer;

    Game(QString name1, QString character1, QString name2, QString character2, int lives);


protected:
    bool eventFilter(QObject *object, QEvent *event) override;

public:


    bool canMove(Player *player, QString direction);

public slots:

    void handleKeyPress();

    void updateScores();

private:
    QVector<Block> blocks;
    QSet<int> pressedKeys;
    label *Score1, *Score2;
    QTimer *scoreTimer;
    ScoreBoard *scoreBoard;
};


#endif //PLAY_WITH_FIRE_GAME_H
