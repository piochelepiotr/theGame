#ifndef LEJEU2D_H
#define LEJEU2D_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtCore/qmath.h>
#include <QEvent>
#include <QMap>
#include <QFile>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QPoint>
#include <QLabel>
#include <QTextStream>
#include <QQueue>
#include <QLineEdit>
#include "elementsMonde/decors.h"
#include "infoJoueur/personnage.h"
#include <QTcpSocket>
#include "additionalActions/actionObjets.h"
#include "infoMonde/lesressources.h"
#include "additionalActions/constantes.h"
#include "network/reseau.h"
#include "jeu_graphique.h"
#include "additionalActions/rechercheChemin.h"
#include "additionalActions/datamap.h"
#include "combats/combat.h"

class AfficheJoueur;
class Jeu_graphique;

////////////////////////////////////////////////////////////////

enum Etat{HorsCombat,EnPlacement,EnCombat};

class Jeu2d : public QObject
{

    Q_OBJECT

public slots:

    bool charge(int cooX, int cooY, int cooZ);//les deux
    void imagesuivante();//les deux
    void supprimeUnPerso(QString const& nom);//les deux
    void ajouteUnPerso(InfoPerVis perso);//les deux
    void VaChangerDeMap(QPoint const& p);
    void ressourceRecoltee(QPoint pos);
    void ressource_repousse(int posx, int posy);
    void infos_map(QString infos);

signals:

    void pnjclique(qint16 numero, QPoint pos);
    void faitRecette(QString metier);
    void pourChat(QString texte);
    void changePC(int pc);

public:

    Jeu2d(QSize const& size, Personnage *pers, QTcpSocket *sock, Donnees_editeur *donneesediteur);
    ~Jeu2d();
    void redi(QSize const& nouvelle);
    void caseEgale(int i, int j, Objet *objet, int fond);//les deux
    Donnees_editeur *donneesediteur();

    void ajouteTranspo(const QPoint &pos, const Transporteur &transpo);//les deux
    void nouvelle();//les deux
    void changeDeMap(int mapx, int mapy,int mapz, QString const& transpo);
    void changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy);
    void setCasePleine(int i, int j, int value);
    AfficheJoueur *getJoueur(QString const& nom);
    Jeu_graphique *graphique() const;
    void cliqueGauche(int x, int y);
    //void souris_bouge(int x, int y);
    void utileClique(QPoint const& pos);
    void changeMap();
    void fait_recettes();
    void doit_recolter();
    void a_coupe();
    Jeu_graphique * getGraphique() { return m_graphique; }
    //void setEnCombat(bool enCombat, QString leader);
    bool monTour() { return m_personnage->monTour(); }
    void setMonTour(bool monTour);
    Personnage *getPerso() { return m_personnage; }
    void veut_utiliserSort(Sort *sort);
    //void caseCombatPleine(int x, int y, int pleine) { m_dataMap }
    //int **getCasesPleinesCombat() { return m_casespleinesCombat; }
    void portee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep,int portee_min, int portee_max);
    void updateObjet(QPoint pos);

    void phasePlacement(Combat *combat, int equipe);
    void phaseCombat();
    void phaseFinCombat();
    Etat phase() const { return m_combatOuPas; }
    DataMap *dataMap() const { return m_dataMap; }
    void deplaceCombat(QString const& qui, QPoint const& ou);
    Sort *sort() const { return m_sort_a_utiliser; }

    /***
     * deletes all the players and monsters
     * and makes all the resources not collected
     */
    void clearMap();

private:

    DataMap *m_dataMap;
    Personnage *m_personnage;
    QTcpSocket *m_socket;//c
    Jeu_graphique *m_graphique;
    Donnees_editeur *m_donnees_editeur;


    QString m_nomMetier;
    Dir m_orientation;
    QPoint m_pos_ressource;


    //combat !!!!!!!!!

    Etat m_combatOuPas;
    int m_debut_tour;
    Combat *m_combat;
    Sort *m_sort_a_utiliser;

    //changement de map

    int m_maparrx;
    int m_maparry;
    int m_maparrz;
    int m_cooarrx;
    int m_cooarry;
};

Dir orientation_vers_objet(QPoint const& pos, QPoint const& pos_obj);

#endif // LEJEU2D_H
