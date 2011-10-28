#include <QApplication>
#include "Application/Hargoile.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Hargoile::getInstance().run();
    return app.exec();
}
