#ifndef INFOMAPTAB_H
#define INFOMAPTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>


class MainWindow;
class Jeu2d;

class InfoMapTab : public QWidget
{
    Q_OBJECT
public:
    explicit InfoMapTab(MainWindow *mainWindow);

    QVBoxLayout *m_layinfomap;
        QPushButton *m_choixdufond;
        QPushButton *m_monstresDeLaMap;
        QPushButton *m_musiques;

signals:

public slots:

};

#endif // INFOMAPTAB_H
