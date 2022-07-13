#ifndef PLAY_WITH_FIRE_GAME_H
#define PLAY_WITH_FIRE_GAME_H

#include <QGraphicsView>
#include <QString>
#include "../views/Player.h"
#include "../views/Box.h"
#include "../views/Wall.h"

class Game : public QGraphicsView{
public:
    Game(Player player1, Player player2);
};


#endif //PLAY_WITH_FIRE_GAME_H
