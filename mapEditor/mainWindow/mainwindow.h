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
#include "elementsMonde/decors.h"
#include "additionalWindows/editerunobjet.h"
#include "additionalWindows/editertransporteur.h"
#include "additionalActions/actionObjets.h"
#include <QFileDialog>
#include "additionalWindows/editerpnjs.h"
#include "additionalWindows/editermonstredelamap.h"
#include "additionalWindows/editermusiques.h"
#include "additionalWindows/editermetier.h"
#include "additionalWindows/editermonstres.h"
#include "additionalWindows/editerclasses.h"
#include "additionalWindows/editersorts.h"
#include "additionalWindows/editerressources.h"
#include "inventory/resources.h"
#include <QPixmap>
#include <QtDebug>
#include <QTime>
#include "mainWindow/bottomtab.h"
#include "additionalActions/rechercheChemin.h"
#include "boutonimg.h"


enum Outil{Outil_objets, Outil_transporteur, Outil_case_marchables, Outil_case_combat, Outil_case_po};

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
    Donnees_editeur *m_donnees_editeur;

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

    void calque1();
    void calque2();
    void calque3();

    void equipeUne();
    void equipeDeux();
    void chargefond();
    void chargeMap();
    void nouveauThemeObjet();
    void nouveauObjetPourTheme();
    void chargeThemeObjet(int num);
    void selectionNouveauObjet(qint16 numero = 0);
    void editerObjet();

    void ajouteUnTransporteur(int x, int y, bool editer = false);

    void outil_objets();
    void outil_transporteurs();
    void outil_cases_marchables();
    void outil_cases_combat();
    void outil_cases_po();

    void charger_contours();
    void changeZoom();
    void annuler();


protected:

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
