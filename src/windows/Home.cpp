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
    background = new Background();
    scene->addItem(background);

    name1 = new TextField(150, 60);
    name2 = new TextField(150, 60);
    livesNumber = new TextField(100, 60);

    name1->setPlainText("");
    name2->setPlainText("");
    scene->setSceneRect(0, 0, width(), height());

    setScene(scene);
    scene->addItem(name1);
    name1->setPos(width() / 6, height() / 1.5);

    scene->addItem(name2);
    name2->setPos(width() / 1.4, height() / 1.5);

    scene->addItem(livesNumber);
    livesNumber->setPos((width()-100) / 2, height() / 1.5);
    QFile historyFile("history.txt");
    if (historyFile.open(QIODevice::ReadOnly)) {
        name1->setPlainText(historyFile.readLine());
        name2->setPlainText(historyFile.readLine());
        livesNumber->setPlainText(historyFile.readLine());
    }
    historyFile.close();
    Label1 = new label();
    Label1->setPlainText("Player 2:");
    scene->addItem(Label1);
    Label1->setPos(width() / 1.4, (height() / 1.7));


    Label2 = new label();
    Label2->setPlainText("Player 1:");
    scene->addItem(Label2);
    Label2->setPos(width() / 6, (height() / 1.7));

    Label3 = new label();
    Label3->setPlainText("Lives:");
    scene->addItem(Label3);
    Label3->setPos((width()-100) / 2, (height() / 1.7));

    scene->addPixmap(QPixmap(":/images/logo").scaled(width() / 3, height() / 3, Qt::IgnoreAspectRatio))->setPos(width() / 2 - width() / 6, height() / 5 -height()/6);


    start = new Button(150, 60);
    scene->addItem(start);
    start->setPos((width()-150) / 2, height() / 1.3);
    connect(start, &Button::onPress, this, &Home::onGameStart);

    character1 = "mike";
    character2 = "mike";
    fillFramesInfo();
    readPixmaps(1);
    readPixmaps(2);


    pixmap = new QGraphicsPixmapItem();
    pixmap->setPixmap(pixmaps1[0]);
    pixmap->setPos(width() / 6, height() / 2.5);
    scene->addItem(pixmap);

    pixmap2 = new QGraphicsPixmapItem();
    pixmap2->setPixmap(pixmaps2[0]);
    pixmap2->setPos(width() / 1.4, height() / 2.5);
    scene->addItem(pixmap2);


    comboBox1 = new QComboBox();
    comboBox1->addItem("mike");
    comboBox1->addItem("ansherli");
    comboBox1->addItem("rex");
    comboBox1->addItem("santa");

    scene->addWidget(comboBox1);
    comboBox1->move(width() / 6, height() / 1.2);
    connect(comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(changePixmap1(int)));

    comboBox2 = new QComboBox();
    comboBox2->addItem("mike");
    comboBox2->addItem("ansherli");
    comboBox2->addItem("rex");
    comboBox2->addItem("santa");
    scene->addWidget(comboBox2);
    comboBox2->move(width() / 1.4, height() / 1.2);
    connect(comboBox2, SIGNAL(currentIndexChanged(int)), this, SLOT(changePixmap2(int)));

    framesTimer = new QTimer();
    framesTimer->setInterval(100);
    framesTimer->start();
    connect(framesTimer, SIGNAL(timeout()), this, SLOT(frameUpdater()));

}

void Home::onGameStart() {
    auto namee1 = name1->toPlainText();
    auto namee2 = name2->toPlainText();
    auto lives = livesNumber->toPlainText().toInt();

    if (name1->document()->isEmpty() == true && name2->document()->isEmpty() == true) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "please enter players names!");
        messageBox.setFixedSize(500, 200);
    }
    else if (name2->document()->isEmpty() == true) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "please enter player 1 name!");
        messageBox.setFixedSize(500, 200);
    }
    else if (name1->document()->isEmpty() == true) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "please enter player 2 name!");
        messageBox.setFixedSize(500, 200);
    }
    else if(livesNumber->document()->isEmpty() || lives<=0) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "please enter valid lives number!");
        messageBox.setFixedSize(500, 200);
    }
    else if (name1->document()->isEmpty() == false && name2->document()->isEmpty() == false) {
        (new Game(namee1,character1, namee2,character2,lives))->show();
        QFile file("history.txt");
        if (file.open(QIODevice::WriteOnly )){
            file.write(namee1.toUtf8()+"\n"+namee2.toUtf8()+"\n"+QString::number(lives).toUtf8());
        }
        file.close();
        close();
    }
}

void Home::changePixmap1(int x) {
    character1 = characters[x];
    fillFramesInfo();
    readPixmaps(1);
}

void Home::changePixmap2(int x) {
    character2 = characters[x];
    fillFramesInfo();
    readPixmaps(2);
}

void Home::readPixmaps(int id) {
    if (id == 1) {
        for (int i = 0; i < framesCount1; i++) {
            pixmaps1[i] = (QPixmap(":/images/"+character1+"/idle" + QString::number(i + 1))).scaled((scene()->width())/10, (scene()->width())/10, Qt::IgnoreAspectRatio,
                                                                                                      Qt::SmoothTransformation);

        }
    } else {
        for (int i = 0; i < framesCount2; i++) {
            pixmaps2[i] = (QPixmap(":/images/"+character2+"/idle" + QString::number(i + 1))).scaled((scene()->width())/10, (scene()->width())/10, Qt::IgnoreAspectRatio,
                                                                                                      Qt::SmoothTransformation);

        }
    }

}

void Home::fillFramesInfo() {

    if (character1 == "mike") {
        framesCount1 = 15;
    } else if (character1 == "ansherli") {
        framesCount1 = 16;
    } else if (character1 == "rex") {
        framesCount1 = 10;
    } else if (character1 == "santa") {
        framesCount1 = 16;
    }

    if (character2 == "mike") {
        framesCount2 = 15;
    } else if (character2 == "ansherli") {
        framesCount2 = 16;

    } else if (character2 == "rex") {
        framesCount2 = 10;
    } else if (character2 == "santa") {
        framesCount2 = 16;

    }

}

void Home::frameUpdater() {
    pixmap->setPixmap(pixmaps1[whichPixmap1++]);
    whichPixmap1%=framesCount1;
    pixmap2->setPixmap(pixmaps2[whichPixmap2++]);
    whichPixmap2%=framesCount2;
}

Home::~Home() {
    delete background;
    delete name1;
    delete name2;
    delete livesNumber;
    delete start;
    delete pixmap;
    delete pixmap2;
    delete comboBox1;
    delete comboBox2;
    delete framesTimer;
    delete start;
    delete Label1;
    delete Label2;
    delete Label3;
    delete framesTimer;
}
