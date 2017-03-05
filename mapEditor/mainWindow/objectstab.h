#ifndef OBJECTSTAB_H
#define OBJECTSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QScrollArea>
#include "boutonimg.h"


class MainWindow;
class Jeu2d;


class ObjectsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectsTab(MainWindow *mainWindow, Jeu2d *gamePanel);

    QVBoxLayout *m_objets;
    QHBoxLayout *m_hautobjets;
    QComboBox *m_themesObjet;
    QPushButton *m_ajouterUnThemeObjet;
            QPushButton *m_ajouterUnObjet;
            QGroupBox *m_groupCalc;
                QHBoxLayout *m_laycalc;
                QRadioButton *m_calc1;
                QRadioButton *m_calc2;
                QRadioButton *m_calc3;
        QHBoxLayout *m_lay_bas_objets;
            QVBoxLayout *m_lay_actions_objet;
                QPushButton *m_effaceurobjet;
                QPushButton *m_remplire;
                QPushButton *m_bout_editobj;
            QHBoxLayout *m_lay_imagesObjets;
            QScrollArea *m_scroll_imagesObjets;
            QWidget *m_wid_imagesObjets;
            QVector<BoutonImg *>m_imagesObjets;

signals:

public slots:

};

#endif // OBJECTSTAB_H
