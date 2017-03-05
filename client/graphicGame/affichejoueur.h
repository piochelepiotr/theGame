#ifndef AFFICHEJOUEUR_H
#define AFFICHEJOUEUR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsColorizeEffect>
#include "actions_personnage.h"
#include "tooltip.h"

class GameField;

class AfficheJoueur : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public :

    AfficheJoueur(UneCreature *creature, QString const& nom, const QSize &size, int *poscasex, int*poscasey, GameField *parent);
    AfficheJoueur(UneCreature *creature,QString const& nom, const QSize &size,QPoint const& posmap,GameField *parent);
    void suivante();
    void affiche();
    void redi(int lcase, int hcase);
    void nouveauchemin(QQueue<Dir> chem, Actions_personnage::DerniereAction action = Actions_personnage::Aucune);
    void recolte(QString const& verbe,int nombre_coups,  Dir orientation, Actions_personnage::DerniereAction derniere_action);
    QPoint posALaFin();
    bool isImobile() const { return m_perso->imobile(); }
    ~AfficheJoueur();
    void changePos(int casex, int casey);/////ATTENTION il doit être a l'arrêt
    void changeMap();
    void aide();
    void desaide();
    void setTexteAide(QString const& texte);
    void deplaceAide();

signals:

    void clique();
    void estSurTranspo(QPoint const& pos);

private:

    void creationBulleAide(const QString &texte);
    Actions_personnage *m_perso;
    int *m_caseX;
    int *m_caseY;
    int m_decalageX;
    int m_decalageY;
    GameField *m_parent;
    bool m_pasentier;
    ToolTip *m_toolTip;
    QPixmap m_image;
    QColor m_color;

protected:
    void mousePressEvent ( QGraphicsSceneMouseEvent * event);

};

#endif // AFFICHEJOUEUR_H
