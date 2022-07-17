#ifndef PLAY_WITH_FIRE_HOME_H
#define PLAY_WITH_FIRE_HOME_H

#include "QGraphicsView"
#include "../views/TextField.h"
#include "../views/Background.h"
#include "../views/label.h"
#include "../windows//Game.h"
#include "../views/Button.h"

class Home : public QGraphicsView {
Q_OBJECT
private:
    TextField *textField;
    TextField *textField1;
public:
    Home();

public slots:

    void onGameStart();

};


#endif //PLAY_WITH_FIRE_HOME_H
