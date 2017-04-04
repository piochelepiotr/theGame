#ifndef ACTIONS_PERSONNAGE_H
#define ACTIONS_PERSONNAGE_H

#include "entities/entityImage.h"
#include "scenery/scenery.h"
#include <QQueue>

class Action
{
public:
    Action(QString const& name, Dir orientation, ImagesEntity *images);
    QPixmap getImage() { return m_images->getImage(m_currentImg, m_orientation); }
    bool moves() const { return m_images->enMouvement(); }
    Dir orientation() const { return m_orientation; }
    int length() const { return m_length; }
    int getNbrOfImg() const { return m_nbrOfImg; }
    QString getName() const { return m_name; }
    void nextImage();
    bool isAtEnd() const { return m_currentStep == m_length - 1; }
    int getCurrentImage() const { return m_currentImg; }
    int getCurrentStep() const { return m_currentStep; }
    void setCurrentImg(int image) { m_currentImg = image % m_nbrOfImg; }

private:
    int m_length;
    QString m_name;
    Dir m_orientation;
    ImagesAction *m_images;
    int m_nbrOfImg;
    int m_currentImg;
    int m_currentStep;
};

class Actions_personnage
{
    public:

    enum DerniereAction{Aucune,ChangeDeMap, Recettes, Recolter, ARecolter};

    Actions_personnage(EntityModel *uneCreature, QSize const& taille_case);
    ~Actions_personnage();
    QPixmap getImage() const { return m_actionActuelle->getImage(); }
    bool suivante(int *decalageX, int *decalageY, int *caseX, int *caseY, DerniereAction *action);
    void decale(int *x, int *y);
    QPoint posALaFin(QPoint actuelle);
    void ajouteAction(QString const& name, Dir orientation);
    void marche(QQueue<Dir>const&chemin, DerniereAction action);
    void court(QQueue<Dir>const&chemin, DerniereAction action);
    void recolte(QString const& verbe, int quantity_coups, DerniereAction action, Dir direction);
    void effaceActions();
    bool imobile() const { return m_immobile; }
    void redi(int lcase, int hcase);

private:
    Action *m_actionActuelle;
    ImagesEntity *m_images;
    bool m_immobile;
    QSize m_taille_case;
    QQueue<Action*>m_lesactions;
    DerniereAction m_derniere_action;
};

#endif // ACTIONS_PERSONNAGE_H
