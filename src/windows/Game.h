#ifndef PLAY_WITH_FIRE_GAME_H
#define PLAY_WITH_FIRE_GAME_H

#include <QGraphicsView>
#include <QString>
#include "../views/Player.h"
#include "../views/Box.h"
#include "../views/Wall.h"
#include <QTimer>

class Game : public QGraphicsView {
Q_OBJECT
public:
    Player *player1, *player2;
    QTimer* walkingTimer;
    Game();

    void keyPressEvent(QKeyEvent *event);
    bool canImove(int x, int y);
};


#endif //PLAY_WITH_FIRE_GAME_H
