#ifndef PLAY_WITH_FIRE_GAME_H
#define PLAY_WITH_FIRE_GAME_H

#include <QGraphicsView>
#include <QString>
#include "../views/Player.h"
#include "../views/Box.h"
#include "../views/Wall.h"

class Game : public QGraphicsView{
    Q_OBJECT
public:
    Game();
};


#endif //PLAY_WITH_FIRE_GAME_H
