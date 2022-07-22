#include "Home.h"
#include "iostream"
#include <QGraphicsScene>
#include <QTextDocument>
#include <QMessageBox>
#include <QPixmap>
using namespace std;


Home::Home() {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();

    auto scene = new QGraphicsScene(this);
    auto background = new Background();
    scene->addItem(background);


     textField = new TextField(150,60);
     textField1 = new TextField(150 ,60);

    textField->setPlainText("");
    textField1->setPlainText("");
    scene->setSceneRect(0,0,width(),height());

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

    QGraphicsPixmapItem *pixmap = new QGraphicsPixmapItem();
    pixmap->setPixmap(QPixmap(":/images/player-copy").scaled(150,150));
    pixmap->setPos(width()/6,height()/2.5);
    scene->addItem(pixmap);

    QGraphicsPixmapItem *pixmap2 = new QGraphicsPixmapItem();
    pixmap2->setPixmap(QPixmap(":/images/player-copy2").scaled(150,150));
    pixmap2->setPos(width()/1.4,height()/2.5);
    scene->addItem(pixmap2);



    auto comboBox = new QComboBox();
    comboBox->addItem("Mike");
    comboBox->addItem("Ansherli");
    comboBox->addItem("Rex");
    comboBox->addItem("Santa");

}

void Home::onGameStart() {
   auto name = textField->toPlainText();
   auto name1 =textField1->toPlainText();
   if(textField->document()->isEmpty()== true && textField1->document()->isEmpty()==true){
       QMessageBox messageBox;
       messageBox.critical(0,"Error","please enter players names!");
       messageBox.setFixedSize(500,200);
   }
    if( textField1->document()->isEmpty()==true){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","please enter player 1 name!");
        messageBox.setFixedSize(500,200);
    }
    if(textField->document()->isEmpty()== true ){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","please enter player 2 name!");
        messageBox.setFixedSize(500,200);
    }

    if(textField->document()->isEmpty()== false && textField1->document()->isEmpty()==false) {
        close();
        (new Game(name,name1))->show();
    }
}

