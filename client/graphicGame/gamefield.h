#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "graphicElements/gamescene.h"
#include <QTcpSocket>
#include "infoJoueur/personnage.h"
#include "combats/combat.h"

class AfficheJoueur;

enum Etat{HorsCombat,EnPlacement,EnCombat};

class GameField : public GameScene
{
public slots:

signals:
    void pnjclique(qint16 numero, QPoint pos);
    void faitRecette(QString metier);
    void pourChat(QString texte);
    void changePC(int pc);
public:
    GameField(QSize const& size, Personnage *pers, QTcpSocket *sock, Donnees_editeur *donneesediteur);
    ~GameField();
    void redi(QSize const& nouvelle);
    void cliqueGauche(int x, int y);
    void setMonTour(bool monTour);
    void veut_utiliserSort(Sort *sort);
    void deplaceCombat(const QString &qui, const QPoint &ou);
    void phaseFinCombat();
    void phaseCombat();
    void phasePlacement(Combat *combat,int equipe);
    void infos_map(QString infos);
    void a_coupe();
    void ressource_repousse(int posx, int posy);
    void ressourceRecoltee(QPoint pos);
    void doit_recolter();
    void fait_recettes();
    void changeMap();
    void utileClique(QPoint const& pos);
    AfficheJoueur *getJoueur(QString const& nom);
    void supprimeUnPerso(QString const& nom);
    void ajouteUnPerso(InfoPerVis perso);
    void changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy);
    bool monTour() { return m_personnage->monTour(); }
    Personnage *getPerso() { return m_personnage; }
    Etat phase() const { return m_combatOuPas; }
    DataMap *dataMap() const { return m_dataMap; }
    Sort *sort() const { return m_sort_a_utiliser; }
    void utiliseSort(Sort *sort);
private:
    Personnage *m_personnage;
    QTcpSocket *m_socket;
    QString m_nomMetier;
    Dir m_orientation;
    QPoint m_pos_ressource;
    Etat m_combatOuPas;
    int m_debut_tour;
    Combat *m_combat;
    Sort *m_sort_a_utiliser;
    QString m_nom;
    QPoint m_posFleche;
    Dir m_directionChangeMap;
    QGraphicsPixmapItem *m_fleche;
    //changement de map

    int m_maparrx;
    int m_maparry;
    int m_maparrz;
    int m_cooarrx;
    int m_cooarry;
protected:
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *);
};

#endif // GAMEFIELD_H
