#include <QApplication>
#include "graphic/ecran.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);


    QTime time = QTime::currentTime();//nombres aléatoires
    qsrand((uint)time.msec());

    Ecran ecran;
    ecran.show();

    return app.exec();
}
