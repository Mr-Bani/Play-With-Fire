//
// Created by Mahdi on 7/23/2022.
//

#ifndef PLAY_WITH_FIRE_SCOREBOARD_H
#define PLAY_WITH_FIRE_SCOREBOARD_H
#include <QGraphicsView>
#include "../views/label.h"

class ScoreBoard : public QGraphicsView {
public:
    ScoreBoard(QString winner, int score1,QString loser,int score2);
    ~ScoreBoard();

private:
    label *Label1,*Label2;
};


#endif //PLAY_WITH_FIRE_SCOREBOARD_H
