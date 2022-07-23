//
// Created by Mahdi on 7/23/2022.
//

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(QString winner, int score1, QString loser, int score2) {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();

    auto scene = new QGraphicsScene(this);

    Label1 = new label();
    Label1->setPlainText("Winner: " + winner + " with score: " + QString::number(score1));
    Label1->setDefaultTextColor("green");
    scene->addItem(Label1);
    Label1->setPos(width() / 2, (height() / 5));


    Label2 = new label();
    Label2->setPlainText("Loser: " + loser + " with score: " + QString::number(score2));
    Label2->setDefaultTextColor("red");
    scene->addItem(Label2);
    Label2->setPos(width() / 2, (height() / 2));

    setScene(scene);



}

ScoreBoard::~ScoreBoard() {
    delete Label1;
    delete Label2;

}
