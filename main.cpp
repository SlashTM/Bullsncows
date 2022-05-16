#include "bullsncows.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bullsncows w;
    w.show();
    return a.exec();
}
