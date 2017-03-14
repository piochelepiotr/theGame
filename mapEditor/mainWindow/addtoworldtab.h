#ifndef ADDTOWORLDTAB_H
#define ADDTOWORLDTAB_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "inventory/resources.h"

class MainWindow;
class Jeu2d;


class AddToWorldTab : public QWidget
{
    Q_OBJECT
public:
    explicit AddToWorldTab(MainWindow *mainWindow, Jeu2d *gamePanel,LesRessources *ressources);

    MainWindow *m_mainWindow;
    Jeu2d *m_jeu;
    LesRessources *m_ressources;

    QGridLayout *m_layajouteMonde;
    QPushButton *m_editeRessources;
    QPushButton *m_editePnj;
        QPushButton *m_editeMetiers;
        QPushButton *m_editeMonstres;
        QPushButton *m_editeSorts;
        QPushButton *m_editeClasses;

public slots:
        void editeMetiers();
        void editeMonstres();
        void editeSorts();
        void editeClasses();
        void editerRessources();
        void editerPnjs();

};

#endif // ADDTOWORLDTAB_H
