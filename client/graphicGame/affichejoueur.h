#ifndef AFFICHEJOUEUR_H
#define AFFICHEJOUEUR_H

#include "actions_personnage.h"
#include "graphic/objectItem.h"

class GameField;

class AfficheJoueur : public ObjectItem
{
public :

    AfficheJoueur(EntityModel *entityModel, QString const& name, const QSize &size, int *poscasex, int*poscasey, GameField *parent, int mapWidth);
    AfficheJoueur(EntityModel *entityModel, QString const& name, const QSize &size, QPoint const& posmap, GameField *parent, int mapWidth);
    void suivante();
    void affiche();
    void resize(int lcase, int hcase);
    void nouveauchemin(QQueue<Dir> chem, Actions_personnage::DerniereAction action = Actions_personnage::Aucune);
    void recolte(QString const& verbe,int nombre_coups,  Dir orientation, Actions_personnage::DerniereAction derniere_action);
    QPoint posALaFin();
    bool isImobile() const { return m_perso->imobile(); }
    ~AfficheJoueur();
    void changePos(int casex, int casey);/////ATTENTION il doit être a l'arrêt
    void changeMap();
    EntityModel *getEntityModel() const { return m_entityModel; }

private:

    EntityModel *m_entityModel;
    Actions_personnage *m_perso;
    int *m_caseX;
    int *m_caseY;
    int m_decalageX;
    int m_decalageY;
    bool m_pasentier;
    QPixmap m_image;
    GameField *m_game;
    QString m_name;

protected:
    //void mousePressEvent ( QGraphicsSceneMouseEvent * event);

};

#endif // AFFICHEJOUEUR_H
