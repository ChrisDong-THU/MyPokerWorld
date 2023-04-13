#include "mainscene.h"

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource("./poker.rcc");

    MainScene w;
    w.show();
    return a.exec();
}
