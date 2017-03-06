#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "graphicElements/gamescene.h"
#include <QTcpSocket>
#include "infoJoueur/personnage.h"
#include "combats/combat.h"
#include "actions_personnage.h"

class AfficheJoueur;

enum Etat{HorsCombat,EnPlacement,EnCombat};

class GameField : public GameScene
{
    Q_OBJECT
public slots:
    void ajouteUnPerso(InfoPerVis perso);
    void supprimeUnPerso(QString const& nom);
    void ressource_repousse(int posx, int posy);
    void ressourceRecoltee(QPoint pos);
    void recolte(const QString &nom, QString const& verbe, int orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    void changePos(QString const& qui, int x, int y);
    void imagesuivante();
    void infos_map(QString infos);
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
    void deplace(QString const& nom, QQueue<Dir> const& chem, Actions_personnage::DerniereAction action = Actions_personnage::Aucune);
    void phaseFinCombat();
    void phaseCombat();
    void phasePlacement(Combat *combat,int equipe);
    void a_coupe();
    void doit_recolter();
    void fait_recettes();
    void changeMap();
    virtual void utileClique(QPoint const& pos);
    AfficheJoueur *getJoueur(QString const& nom);
    void changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy);
    bool monTour() { return m_personnage->monTour(); }
    Personnage *getPerso() { return m_personnage; }
    Etat phase() const { return m_combatOuPas; }
    DataMap *dataMap() const { return m_dataMap; }
    Sort *sort() const { return m_sort_a_utiliser; }
    void utiliseSort(Sort *sort);
    void changePlayerMap(int largX, int largY);
    void ajouteChemin(QString const& nom, QQueue<Dir> const& chemin);
    QString contientJoueur();
    void meurt(QString const& nom);
    void setVie(QString const& nom, int vie);
    void faitRecettes();
    void recolte(const QString &nom, QString const& verbe, Dir orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    QPoint fleche() const { return m_posFleche; }
    Dir direction_fleche() const { return m_directionChangeMap; }
    bool contientJoueur(QPoint const& pos);
    QPoint posCaseVisee() const { return m_posCaseVisee; }
    void marche_pas();
private:
    Personnage *m_personnage;
    QMap<QString,AfficheJoueur*>m_persos;
    QTcpSocket *m_socket;
    QString m_nomMetier;
    Dir m_orientation;
    QPoint m_pos_ressource;
    Etat m_combatOuPas;
    int m_debut_tour;
    Combat *m_combat;
    Sort *m_sort_a_utiliser;
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
