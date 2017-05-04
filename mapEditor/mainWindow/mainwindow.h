#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QResizeEvent>
#include "jeu2d.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QAction>
#include <QMenu>
#include "scenery/scenery.h"
#include "additionalWindows/editobject.h"
#include "additionalWindows/editgate.h"
#include "scenery/sceneryChange.h"
#include <QFileDialog>
#include "additionalWindows/editnpcs.h"
#include "additionalWindows/editmapmonsters.h"
#include "additionalWindows/editmusics.h"
#include "additionalWindows/editjob.h"
#include "additionalWindows/editmonsters.h"
#include "additionalWindows/editclasses.h"
#include "additionalWindows/editspells.h"
#include "additionalWindows/editresources.h"
#include "inventory/resources.h"
#include <QPixmap>
#include <QtDebug>
#include <QTime>
#include "mainWindow/bottomtab.h"
#include "map/computePath.h"
#include "boutonimg.h"


enum Outil{Outil_objets, Outil_transporteur, Outil_case_marchables, Outil_case_fight, Outil_case_po};

enum Cote{Droite, Gauche, Bas, Haut};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void deplaceMap(Cote cote);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Jeu2d *m_jeu;
    bool m_appuyer;
    Outil m_outil;
    bool m_au_moins_une_case_en_glisser;
    Data *m_donnees_editeur;

//////////barre d'outil

    BottomTab *m_tabbar;
        QMainWindow *m_objets_2;


public slots:

    void musiques();
    void monstresDeLaMap();
    void petiteTaille();
    void moyenneTaille();
    void grandeTaille();
    void nouvelle();

    /*void calque1();
    void calque2();
    void calque3();*/

    void equipeUne();
    void equipeDeux();
    void chargeMap();
    void nouveauThemeObjet();
    void nouveauObjetPourTheme();
    void chargeThemeObjet(int num);
    void selectionNouveauObjet(qint16 numero = 0);
    void editObject();

    void ajouteUnTransporteur(int x, int y, bool spell = false);

    void outil_objets();
    void outil_transporteurs();
    void outil_cases_marchables();
    void outil_cases_fight();
    void outil_cases_po();

    void charger_contours();
    void changeZoom();
    void annuler();


protected:

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
