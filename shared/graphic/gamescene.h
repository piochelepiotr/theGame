#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "scenery/constants.h"
#include <QLabel>
#include "map/map.h"
#include "graphic/objectItem.h"
#include "graphic/subwindow.h"
#include "utils/comparespoints.h"

class Scenery;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void enregistre() { m_dataMap->enregistre(); }
    void nouvelle();
    void charge(int cooX = -1, int cooY = -1, int cooZ = -1);
    void remplire();
    void calcObject();
    void calcBacground();
    void equipe1() { m_equipe = 0; }
    void equipe2() { m_equipe = 1; }
    void setEffaceIm(bool efface) { m_enlevercaseim = efface; }
    void tailleun() { m_tailleci = 1; }
    void tailletrois() { m_tailleci = 3; }
    void taillecinq() { m_tailleci = 5; }
    void changeValeurZoom();
    void undo();
    void ajouteEvent();
public:
    GameScene(QSize const& size, QLabel *texte, Data *donnees_editeur);
    ~GameScene();
    Map *dataMap() const { return m_dataMap; }
    void resize(QSize const& nouvelle);
    void actualise();
    void largethautcase();
    void grille();
    void changementSele(QPoint const& nouvelle);
    void souriBouge(QPoint const& poscase, const QPoint &pos);
    void setObjetActuel(Object *nouveau);
    void caseEgale(int i, int j, Object *objet);
    Object *getObjActuel() const { return m_objetActuel; }
    int getlcase() const { return m_lcase; }
    int gethcase() const { return m_hcase; }
    int getlmap() const { return m_lmap; }
    int gethmap() const { return m_hmap; }
    Scenery *decors();
    void ajouteTranspo(const QPoint &pos, Gate *transpo);
    void supprimeTranspo(const QPoint &pos);
    void remplitCaseIm(int i, int j);
    void rend_case_immarchable(int i, int j);
    void change_portee_case(QPoint const& lacase);
    bool case_sans_portee(int i, int j);
    bool case_avec_portee(int i, int j);
    QPoint case_selectionnee() { return m_caseSele; }
    void case_prend_valeur(QPoint const& poscase, const QPoint &pos);
    void chargeContours();
    void supprimeCasecbt(int x, int y);
    void ajouteCasecbt(int x, int y);

    void affiche_casesMarchable();
    void masque_casesMarchable();
    void affiche_casesFight();
    void masque_casesFight();
    void affiche_casesPO();
    void masque_casesPO();

    bool zoom() const { return m_zoom_active; }
    void updateObjet(int i,int j, Object *objet);
    void updateObjet(QPoint pos);
    void afficheChemin(QPoint dep, QQueue<Dir>chem);
    void effaceChemin();
    void stopUtiliseSpell();
    void affichePortee();
    virtual void utileClique(QPoint const& pos);
    Data *donneesediteur() { return m_donnees_editeur; }
    void setSubWinOpened(bool opened) { m_subWinOpened = opened; }

protected:
    bool m_displayGrid;
    void zoomChanged();
    QGraphicsRectItem *m_cadred;
    QGraphicsRectItem *m_cadreg;
    QGraphicsRectItem *m_cadreb;
    QGraphicsRectItem *m_cadreh;
    QGraphicsPixmapItem *m_caseImmarchables[NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_casesDep[NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_casesPortee[NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_imgcasescbt[2] [MAX_PAR_EQUIP];
    QGraphicsPolygonItem *m_grille[NBR_CASES_L] [NBR_CASES_H];
    ObjectItem *m_imagesObjets [NBR_CASES_L] [NBR_CASES_H];
    bool m_cases_ateignables [NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_imageBackground;
    QGraphicsPixmapItem *m_fond;
    QMap <QPoint, QGraphicsPixmapItem*>m_lesimagestransports;
    QGraphicsPixmapItem *m_imgCaseVisee;
    int m_lcase;
    int m_hcase;
    int m_mlcase;
    int m_mhcase;
    int m_lmap;
    int m_hmap;
    QPoint m_caseSele;
    QLabel *m_texte;
    Object *m_objet;
    Object *m_objetActuel;
    Data *m_donnees_editeur;
    bool m_calcObject;
    bool m_enlevercaseim;
    int m_tailleci;
    bool m_zoom_active;
    int m_equipe;
    Map *m_dataMap;
    QPoint m_ancienne;
    QPoint m_posCaseVisee;
    SubWindow *m_subWindow;
    bool m_subWinOpened;
};

#endif // GAMESCENE_H
