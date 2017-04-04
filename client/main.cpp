#include <QApplication>
#include "mainWindow/fenprin.h"
#include <QString>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QWidget>
#include <QPushButton>

void perso()
{
    QFile style("../data/interface/style.css");
    if(!style.open(QIODevice::ReadOnly))
    {
        qDebug() << "fichier style.css non trouve";
        exit(EXIT_FAILURE);
    }
    QString stylec(style.readAll());
    qApp->setStyleSheet(stylec);
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTime time = QTime::currentTime();//quantitys aléatoires
    qsrand((uint)time.msec());
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    perso();
    FenPrin fenetre;
    fenetre.show();
    return app.exec();
}
