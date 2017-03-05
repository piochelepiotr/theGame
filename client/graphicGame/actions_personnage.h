#ifndef ACTIONS_PERSONNAGE_H
#define ACTIONS_PERSONNAGE_H

#include "infoMonde/images_classe.h"
#include "elementsMonde/decors.h"
#include <QQueue>

class Action
{
public:
    Action(QString const& nom, Dir orientation, Images_Classe *images);
    QPixmap getImage(int num) { return m_images->getImage(num, m_orientation); }
    bool enMouvement() const { return m_images->enMouvement(); }
    int nombre_images() const { return m_nbrImages; }
    Dir orientation() const { return m_orientation; }

private:
    QString m_nom;
    Dir m_orientation;
    Images_action *m_images;
    int m_nbrImages;
};

class Actions_personnage
{
    public:

    enum DerniereAction{Aucune,ChangeDeMap, Recettes, Recolter, ARecolter};

    Actions_personnage(UneCreature *uneCreature, QSize const& taille_case);
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
    Images_Classe *m_images;
    bool m_immobile;
    QSize m_taille_case;
    QQueue<Action*>m_lesactions;
    int m_imageActuelle;
    DerniereAction m_derniere_action;
};

#endif // ACTIONS_PERSONNAGE_H
