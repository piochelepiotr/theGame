#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "graphic/gamescene.h"
#include <QTcpSocket>
#include "entities/character.h"
#include "fights/fight.h"
#include "actions_personnage.h"

class AfficheJoueur;
class LayoutBarreOutil;

enum Etat{HorsFight,EnPlacement,EnFight};

class GameField : public GameScene
{
    Q_OBJECT
public slots:
    void addEntity(EntityInfo perso);
    void removeEntity(QString const& name);
    void resource_repousse(int posx, int posy);
    void resourceRecoltee(QPoint pos);
    void recolte(const QString &name, QString const& verbe, int orientation, int quantity_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    void changePos(QString const& qui, int x, int y);
    void imagesuivante();
    void infos_map(QString infos);
    void phaseFight();
    void phasePlacement(int equipe);
    void setVie(QString const& name, int vie);
    void yourTurn() { setMonTour(true); }
signals:
    void pnjclique(qint16 numero, QPoint pos);
    void faitRecette(QString metier);
    void pourChat(QString texte);
public:
    GameField(QSize const& size, Character *pers, QTcpSocket *sock, Data *donneesediteur);
    ~GameField();
    void resize(QSize const& newSize);
    void cliqueGauche(int x, int y);
    void setMonTour(bool monTour);
    void veut_utiliserSpell(Spell *spell);
    void deplaceFight(const QString &qui, const QPoint &ou);
    void deplace(QString const& name, QQueue<Dir> const& chem, Actions_personnage::DerniereAction action = Actions_personnage::Aucune);
    void phaseFinFight();
    void a_coupe();
    void doit_recolter();
    void fait_recettes();
    void changeMap();
    virtual void utileClique(QPoint const& pos);
    AfficheJoueur *getJoueur(QString const& name);
    void changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy);
    bool monTour() { return m_character->monTour(); }
    Character *getPerso() { return m_character; }
    Etat phase() const { return m_fightOuPas; }
    Map *dataMap() const { return m_dataMap; }
    Spell *spell() const { return m_spell_a_utiliser; }
    void utiliseSpell(Spell *spell);
    void changePlayerMap(int largX, int largY);
    void ajouteChemin(QString const& name, QQueue<Dir> const& chemin);
    QString contientJoueur();
    void meurt(QString const& name);
    void faitRecettes();
    void recolte(const QString &name, QString const& verbe, Dir orientation, int quantity_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    QPoint fleche() const { return m_posFleche; }
    Dir direction_fleche() const { return m_directionChangeMap; }
    bool contientJoueur(QPoint const& pos);
    QPoint posCaseVisee() const { return m_posCaseVisee; }
    void marche_pas();
    void setLayoutBarreOutil(LayoutBarreOutil *layoutBarreOutil) { m_layoutBarreOutil = layoutBarreOutil; }
private:
    void removeEntities();
    LayoutBarreOutil *m_layoutBarreOutil;
    Character *m_character;
    QMap<QString,AfficheJoueur*>m_persos;
    QTcpSocket *m_socket;
    QString m_nameMetier;
    Dir m_orientation;
    QPoint m_pos_resource;
    Etat m_fightOuPas;
    int m_debut_tour;
    Fight *m_fight;
    Spell *m_spell_a_utiliser;
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
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *);
};

#endif // GAMEFIELD_H
