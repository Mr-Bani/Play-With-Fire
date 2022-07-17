#include "Home.h"
#include "iostream"
#include <QGraphicsScene>
using namespace std;


Home::Home() {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    /*QPixmap pixmap(":/images/bg1");
    cout<<height()<<endl<<width();
    pixmap = pixmap.scaled(height(),width(),Qt::AspectRatioMode::IgnoreAspectRatio);*/
    auto scene = new QGraphicsScene(this);
    auto background = new Background();
    scene->addItem(background);


     textField = new TextField(150,60);
     textField1 = new TextField(150 ,60);

    textField->setPlainText("");
    textField1->setPlainText("");
    scene->setSceneRect(0,0,width(),height());
   // scene->setBackgroundBrush(QBrush(pixmap));
   // scene->setBackgroundBrush(QBrush("#41E3F0"));

    setScene(scene);
    scene->addItem(textField);
    textField->setPos(width()/6,height()/1.5);

    scene->addItem(textField1);
    textField1->setPos(width()/1.4,height()/1.5);

    auto Label = new label();
    Label->setPlainText("player 1:");
    scene->addItem(Label);
    Label->setPos(width()/1.4,(height()/1.6));


    auto Label1 = new label();
    Label1->setPlainText("player 2:");
    scene->addItem(Label1);
    Label1->setPos(width()/6,(height()/1.6));


    auto start = new Button(150,60);
    start->setPlainText("start");
    scene->addItem(start);
    start->setPos(width()/2.4,height()/1.3);

    connect(start, &Button::onPress , this , &Home::onGameStart );
}

void Home::onGameStart() {
   auto name = textField->toPlainText();
   auto name1 =textField1->toPlainText();
}

