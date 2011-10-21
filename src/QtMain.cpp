#include "Application/Hargoile.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Hargoile hargoile;
    return app.exec();
}
