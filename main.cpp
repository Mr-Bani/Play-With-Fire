#include <QApplication>
#include <QPushButton>
#include "src/windows/Home.h"
#include "src/windows/Game.h"
#include "src/windows/ScoreBoard.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    auto home = new Home();
    home->show();
    return QApplication::exec();
}
