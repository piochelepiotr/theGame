#ifndef JEU_GRAPHIQUE_H
#define JEU_GRAPHIQUE_H

#include <QGraphicsScene>
#include <QMap>
#include "graphicGame/lejeu2d.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include "additionalActions/constantes.h"
#include <QFile>
#include <QTextStream>
#include "infoMonde/lesressources.h"
#include <QToolTip>
#include <QFontMetricsF>
#include <QDebug>
#include "objsurscene.h"
#include "affichejoueur.h"
#include "additionalActions/rechercheChemin.h"
#include "additionalActions/datamap.h"

class Jeu2d;
class Jeu_graphique;


class Jeu_graphique : public QGraphicsScene
{
    Q_OBJECT
public:
    Jeu_graphique(QSize const& size, QString const& nom, Jeu2d *parent, Donnees_editeur *donneesediteur);
    ~Jeu_graphique();
    void ajouteUnPerso(InfoPerVis perso);//les deux
    void supprimeUnPerso(QString const& nom);//les deux
    void changeDeMap(int largX, int largY);
    bool contientTranspo(QPoint const& pos);
    void imagesuivante();
    void deplace(QString const& nom, QQueue<Dir> const& chem, Actions_personnage::DerniereAction action = Actions_personnage::Aucune);
    void ajouteTranspo(const QPoint &pos);
    AfficheJoueur *getJoueur(QString const& nom) { return m_persos[nom]; }
    void fondEgal(QString const& nom);
    void utileClique(QPoint const& pos);
    void changeMap();
    QPoint fleche() const { return m_posFleche; }
    Dir direction_fleche() const { return m_directionChangeMap; }
    void faitRecettes();
    void doit_recolter();
    void effaceChemin();
    void afficheChemin(QPoint dep, QQueue<Dir> chem);
    void marche_pas(DataMap *dataMap);
    void affichePortee();
    void afficheCasesCombat(DataMap *dataMap);
    void masqueCaseCombat();
    void charge(DataMap *dataMap);
    void chargeObjets(DataMap *dataMap);
    bool contientJoueur(QPoint const& pos);
    QPoint posCaseVisee() const { return m_posCaseVisee; }
    void stopUtiliseSort();
    Jeu2d *getJeu() const { return m_parent; }

public slots:

    void changePos(QString const& qui, int x,int y);
    void redi(QSize const& nouvelle, DataMap *dataMap);
    void redi_case();
    void grille();
    void caseEgale(int i, int j, Objet *objet, int calque);
    void updateObjet(int i,int j, Objet *objet);
    int getlcase() const { return m_lcase; }
    int gethcase() const { return m_hcase; }
    int getlmap() const { return m_lmap; }
    int gethmap() const { return m_hmap; }

    Donnees_editeur *donneesediteur() { return m_donneesediteur; }
    void ajouteChemin(QString const& nom, QQueue<Dir> const& chemin);
    void nouvelle();
    QString contientJoueur();
    void setCasepleine(int i, int j, int value);
    void recolte(const QString &nom, QString const& verbe, Dir orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    void recolte(const QString &nom, QString const& verbe, int orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action = Actions_personnage::Aucune);
    void a_recolte();
    void utiliseSort(Sort *sort);
    void setVie(QString const& nom, int vie);
    void meurt(QString const& nom);

private:



    QGraphicsPixmapItem *m_casesDep[NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_casesPortee[NBR_CASES_L] [NBR_CASES_H];
    QGraphicsPixmapItem *m_casesVisee[NBR_CASES_L] [NBR_CASES_H];

    QGraphicsPolygonItem *m_grille[NBR_CASES_L] [NBR_CASES_H];
    ObjSurScene *m_lesobjets [3] [NBR_CASES_L] [NBR_CASES_H];
    bool m_cases_ateignables [NBR_CASES_L] [NBR_CASES_H];
    QMap <QPoint, QGraphicsPixmapItem*>m_lesimagestransports;
    QMap<QString,AfficheJoueur*>m_persos;
    QGraphicsPixmapItem *m_fond;
    QGraphicsPixmapItem *m_imgcasescbt[2] [MAX_PAR_EQUIP];
    QGraphicsPixmapItem *m_imgCaseVisee;

    int m_lcase;
    int m_hcase;
    int m_mlcase;
    int m_mhcase;
    int m_lmap;
    int m_hmap;
    Donnees_editeur *m_donneesediteur;
    QString m_nom;
    Jeu2d *m_parent;
    QString m_nomfond;
    QPoint m_posFleche;
    Dir m_directionChangeMap;
    QGraphicsPixmapItem *m_fleche;
    QPoint m_ancienne;

    QPoint m_posCaseVisee;

protected:
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *);
};

bool estdansScene(int x, int y);

#endif // JEU_GRAPHIQUE_H
