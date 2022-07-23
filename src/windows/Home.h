#ifndef PLAY_WITH_FIRE_HOME_H
#define PLAY_WITH_FIRE_HOME_H

#include "QGraphicsView"
#include "../views/TextField.h"
#include "../views/Background.h"
#include "../views/label.h"
#include "../windows//Game.h"
#include "../views/Button.h"
#include <QComboBox>

class Home : public QGraphicsView {
Q_OBJECT
private:
    TextField *name1,*name2,*livesNumber;
    label *Label1,*Label2,*Label3;
    QGraphicsPixmapItem* pixmap,*pixmap2;
    QString character1,character2;
    QString characters[4] = {"mike","ansherli","rex","santa"};
    QComboBox *comboBox1,*comboBox2;
    QPixmap* pixmaps1 = new QPixmap[30];
    QPixmap* pixmaps2 = new QPixmap[30];
    int framesCount1,framesCount2;
    int whichPixmap1{0},whichPixmap2{0};
    QTimer* framesTimer;
    Background* background;
    Button* start;
public:
    Home();
    void readPixmaps(int id);
    void fillFramesInfo();
    ~Home();

public slots:

    void onGameStart();
    void changePixmap1(int x);
    void changePixmap2(int x);
    void frameUpdater();



};


#endif //PLAY_WITH_FIRE_HOME_H
