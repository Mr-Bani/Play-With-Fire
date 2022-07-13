#include <QApplication>
#include <QPushButton>
#include "src/windows/Home.h"
#include "src/windows/Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Player p1;
    Player p2;
    auto game = new Game(p1,p2);
    game->show();
    return QApplication::exec();
}
