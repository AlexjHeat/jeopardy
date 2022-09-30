#include "controlwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.show();

    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(onExit()));

    return a.exec();
}
