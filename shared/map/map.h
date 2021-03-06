﻿#ifndef DATAMAP_H
#define DATAMAP_H

#include <QFile>
#include <QMap>
#include <QPoint>
#include <QPixmap>
#include <QtCore>

class Data;
class Object;
class MonsterModel;
class Gate;

#include "scenery/constants.h"
#include "utils/comparespoints.h"

class Map
{
public:

    static const int mapWidth = 30;
    static const int mapHeight = 60;
    static const int worldWidth;
    static const int worldHeight;
    static const int worldDepth;

    //coté utilisateur
    Map(Data *donnees_editeur, int cooX, int cooY, int cooZ);
    void charge(QString const& nameFichier);
    bool undo();
    void chargeMap(int x,int y,int z);
    void nouvelleMap();
    static bool exist(int cooX, int cooY, int cooZ, int undo = -1);
    static void casePleineDeMap(int cooX,int cooY,int cooZ, qint8 casesPleines[mapWidth] [mapHeight]);
    void coupable(QMap<QPoint, bool> *objetsCoupables);
    bool estCaseDeDepart(int x, int y, int equipe);
    Object *objet(int x,int y) const { return m_objets[x][y]; }
    QPoint caseFight(int equipe,int num) const { return m_casescbt[equipe] [num]; }
    void setCaseFight(int equipe,int num,QPoint p) { m_estEnregistree = false; m_casescbt[equipe] [num] = p; }
    int x() const { return m_cooX; }
    int y() const { return m_cooY; }
    int z() const { return m_cooZ; }
    QVector<QPoint> cases_autour(QPoint const& p);
    int casePleineFight(int i,int j) const { return m_casepleinesFight[i][j]; }
    int casePleine(int i,int j) const { return m_casepleines[i][j]; }

    //pour le jeu
    QPoint caseLibre();
    MonsterModel *nouveauMonstre();
    void charge_contours();
    QPoint case_haut(QPoint lacase);
    QPoint case_bas(QPoint lacase);
    QPoint case_gauche(QPoint lacase);
    QPoint case_droite(QPoint lacase);
    QPoint posDep(int equipe);
    void setCasePleineFight(int i,int j,int value);
    QQueue<Dir> calculchemin(QPoint const& dep, QPoint const& arr);//calcul
    QQueue<Dir> calculcheminJusquaLObjet(QPoint const& dep, QPoint const& position_objet, QPoint *arrivee);

    QQueue<Dir> calculcheminFight(QPoint const& dep, QPoint const& arr, int max_dep);//calcul
    QQueue<Dir> calculcheminJusquaLObjetFight(QPoint const& dep, QPoint const& position_objet, QPoint *arrivee);
    void calculPortee(bool cases_ateignables[Map::mapWidth] [Map::mapHeight], int xdep, int ydep,int min_portee, int max_portee);
    void initialisePortee(bool cases_ateignables[Map::mapWidth] [Map::mapHeight], int xdep, int ydep,int min_portee, int max_portee);

    QMap<QString, double> *getMonstresMap() { return &m_monstres; }
    QVector<QString> *getMusiques() { return &m_musiques; }

    //coté éditeur de map
    void enregistre(bool undo = false);
    void setCasePleine(int i,int j,int value);
    void setObjet(int i,int j,Object *objet) {m_estEnregistree = false; m_objets[i][j] = objet; }
    void vide();

    QPoint ccase(int posx, int posy, int lmap, int hmap, int lcase, int hcase, bool zoom);
    int cposy(int casey,int hcase,bool zoom);
    int cposx(int casex, int casey, int lcase, bool zoom);
    Gate *getTranspo(QPoint const& pos) const { return m_transpos[pos]; }
    void ajouterTranspo(QPoint const& pos, Gate *transpo) { m_transpos[pos] = transpo; }
    void supprimeTranspo(QPoint const& pos) { m_transpos.remove(pos); }
    bool contientTranspo(QPoint const& pos) { return m_transpos.contains(pos); }

    bool estEnregistree() const { return m_estEnregistree; }
    void setEnregistree(bool enregistree) { m_estEnregistree = enregistree; }

    QMap<QPoint,Object*> posCollectedResources();

    void addToBackground(Object *object, QPoint const& pos, int mapWidth, int mapHeight);

    QPixmap getBackground(int mapWidth, int mapHeight) const { return m_background.scaled(mapWidth, mapHeight); }

private:
    bool m_estEnregistree;
    void videObjets();
    void videCasesFight();
    void videCasesPleines();
    int m_cooX;
    int m_cooY;
    int m_cooZ;
    Object *m_objets[Map::mapWidth] [Map::mapHeight];
    QMap <QPoint, Gate*>m_transpos;
    qint8 m_casepleines[Map::mapWidth] [Map::mapHeight];
    int m_casepleinesFight[Map::mapWidth][Map::mapHeight];//même chose que case pleines mais on ne peut pas marcher sur des joueurs par exemple !
    QPixmap m_background;
    QPoint m_casescbt[2] [MAX_PAR_EQUIP];
    QMap<QString, double> m_monstres;
    QVector<QString>m_musiques;
    bool m_haut[(Map::mapWidth-CASESCACHEESX)*2];
    bool m_bas[(Map::mapWidth-CASESCACHEESX)*2];
    bool m_gauche[Map::mapHeight-CASESCACHEESY*2+1];
    bool m_droite[Map::mapHeight-CASESCACHEESY*2+1];
    Data *m_donnees_editeur;
    int m_undo;
};

double calculAngle(int x, int y);
bool auMilieu(double petitAngle,double grandAngle,double milieu,int d);
void droiteExtremes(QList<double>droites,double &max,double &min);
void calculContoursCase(int x,int y,int mlcase,int mhcase,double &max,double &min);
Dir orientation_vers_objet(QPoint const& pos, QPoint const& pos_obj);


#endif // DATAMAP_H
