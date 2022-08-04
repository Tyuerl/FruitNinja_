#include "widget.h"
#include "menuwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    MenuWidget isMw;
    isMw.show();
    return a.exec();
}
