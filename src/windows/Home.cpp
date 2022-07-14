#include "Home.h"
#include "iostream"
using namespace std;


Home::Home() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    QPixmap pixmap(":/images/bg1");
    cout<<height()<<endl<<width();
    //pixmap = pixmap.scaled(height(),width(),Qt::AspectRatioMode::IgnoreAspectRatio);

    auto scene = new QGraphicsScene(this);
    auto textField = new TextField(150,200);
    textField->setPlainText("First Name");
    scene->setSceneRect(0,0,width(),height());
    //scene->setBackgroundBrush(QBrush(pixmap));
    scene->setBackgroundBrush(QBrush("#41E3F0"));

    setScene(scene);
    scene->addItem(textField);
    textField->setPos(width()/2,height()/2);




}
