#ifndef ACTIONS_PERSONNAGE_H
#define ACTIONS_PERSONNAGE_H

#include "entities/entityImage.h"
#include "scenery/scenery.h"
#include <QQueue>

class Action
{
public:
    Action(QString const& name, Dir orientation, ImagesEntity *images);
    QPixmap getImage(int num) { return m_images->getImage(num, m_orientation); }
    bool moves() const { return m_images->enMouvement(); }
    Dir orientation() const { return m_orientation; }
    int length() const { return m_length; }
    QString getName() const { return m_name; }

private:
    int m_length;
    QString m_name;
    Dir m_orientation;
    ImagesAction *m_images;
};

class Actions_personnage
{
    public:

    enum DerniereAction{Aucune,ChangeDeMap, Recettes, Recolter, ARecolter};

    Actions_personnage(EntityModel *uneCreature, QSize const& taille_case);
    ~Actions_personnage();
    QPixmap getImage() const { return m_actionActuelle->getImage(m_imageActuelle); }
    bool suivante(int *decalageX, int *decalageY, int *caseX, int *caseY, DerniereAction *action);
    void decale(int *x, int *y);
    QPoint posALaFin(QPoint actuelle);
    void ajouteAction(QString const& nom, Dir orientation);
    void marche(QQueue<Dir>const&chemin, DerniereAction action);
    void court(QQueue<Dir>const&chemin, DerniereAction action);
    void recolte(QString const& verbe, int nombre_coups, DerniereAction action, Dir direction);
    void effaceActions();
    bool imobile() const { return m_immobile; }
    void redi(int lcase, int hcase);

private:
    Action *m_actionActuelle;
    ImagesEntity *m_images;
    bool m_immobile;
    QSize m_taille_case;
    QQueue<Action*>m_lesactions;
    int m_imageActuelle;
    DerniereAction m_derniere_action;
};

#endif // ACTIONS_PERSONNAGE_H
