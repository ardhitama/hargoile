#include <QApplication>
#include "Application/Hargoile.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Hargoile::getInstance().run();
    Hargoile hgl;
    hgl.run();
    return app.exec();
}
