#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "mainWindow/mainwindow.h"

void perso()
{
    QFile style("../data/interface/style2.css");
    if(!style.open(QIODevice::ReadOnly))
    {
        qDebug() << "fichier style2.css non trouve";
        exit(EXIT_FAILURE);
    }
    QString stylec(style.readAll());
    qApp->setStyleSheet(stylec);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    perso();
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
