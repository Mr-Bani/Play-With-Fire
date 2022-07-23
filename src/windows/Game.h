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

class Game : public QGraphicsView {
Q_OBJECT
public:
    Player *player1, *player2;
    QTimer* walkingTimer,*keyTimer;
    Game(QString name1,QString character1, QString name2,QString character2,int lives);


protected:
    bool eventFilter(QObject *object, QEvent *event) override;

public:


    bool canMove(Player *player, QString direction);

public slots:
    void handleKeyPress();
private:
    QVector <Block> boxes;
    QSet<int> pressedKeys;
};


#endif //PLAY_WITH_FIRE_GAME_H
