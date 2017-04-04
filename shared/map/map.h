#ifndef DATAMAP_H
#define DATAMAP_H

#include <QFile>
#include <QMap>
#include <QPoint>
#include "scenery/constants.h"
#include "scenery/sceneryChange.h"
#include "map/computePath.h"
#include "point.h"
#include "scenery/data.h"
#include <QtCore>
#include "map/gate.h"

class Map
{
public:

    //coté utilisateur
    Map(Data *donnees_editeur, int cooX, int cooY, int cooZ);
    void charge(QString const& nomFichier);
    bool undo();
    void chargeMap(int x,int y,int z);
    void nouvelleMap();
    static bool exist(int cooX, int cooY, int cooZ, int undo = -1);
    static void casePleineDeMap(int cooX,int cooY,int cooZ, qint8 casesPleines[NBR_CASES_L] [NBR_CASES_H]);
    void coupable(QMap<QPoint, bool> *objetsCoupables);
    bool estCaseDeDepart(int x, int y, int equipe);
    Object *objet(int x,int y,int calque) const { return m_objets[calque][x][y]; }
    QPoint caseFight(int equipe,int num) const { return m_casescbt[equipe] [num]; }
    void setCaseFight(int equipe,int num,QPoint p) { m_estEnregistree = false; m_casescbt[equipe] [num] = p; }
    int x() const { return m_cooX; }
    int y() const { return m_cooY; }
    int z() const { return m_cooZ; }
    QVector<QPoint> cases_autour(QPoint const& p);
    QString fond() const { return m_fond; }
    void setFond(QString const& fond) { m_estEnregistree = false; m_fond = fond; }
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
    void calculPortee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep,int min_portee, int max_portee);
    void initialisePortee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep,int min_portee, int max_portee);

    QMap<QString, double> *getMonstresMap() { return &m_monstres; }
    QVector<QString> *getMusiques() { return &m_musiques; }

    //coté éditeur de map
    void enregistre(bool undo = false);
    void setCasePleine(int i,int j,int value);
    void setObjet(int i,int j,int calque,Object *objet) {m_estEnregistree = false; m_objets[calque][i][j] = objet; }
    void vide();

    QPoint ccase(int posx, int posy, int lmap, int hmap, int lcase, int hcase, bool zoom);
    int cposy(int casey,int hcase,bool zoom);
    int cposx(int casex, int casey, int lcase, bool zoom);
    Gate getTranspo(QPoint const& pos) const { return m_transpos[pos]; }
    void ajouterTranspo(QPoint const& pos, Gate const& transpo) { m_transpos[pos] = transpo; }
    void supprimeTranspo(QPoint const& pos) { m_transpos.remove(pos); }
    bool contientTranspo(QPoint const& pos) { return m_transpos.contains(pos); }

    bool estEnregistree() const { return m_estEnregistree; }
    void setEnregistree(bool enregistree) { m_estEnregistree = enregistree; }

    QMap<QPoint,Object*> posCollectedResources();

private:
    bool m_estEnregistree;
    void videObjets();
    void videCasesFight();
    void videCasesPleines();
    int m_cooX;
    int m_cooY;
    int m_cooZ;
    Object *m_objets[3] [NBR_CASES_L] [NBR_CASES_H];
    QMap <QPoint, Gate>m_transpos;
    qint8 m_casepleines[NBR_CASES_L] [NBR_CASES_H];
    int m_casepleinesFight[NBR_CASES_L][NBR_CASES_H];//même chose que case pleines mais on ne peut pas marcher sur des joueurs par exemple !
    QString m_fond;
    QPoint m_casescbt[2] [MAX_PAR_EQUIP];
    QMap<QString, double> m_monstres;
    QVector<QString>m_musiques;
    bool m_haut[(NBR_CASES_L-CASESCACHEESX)*2];
    bool m_bas[(NBR_CASES_L-CASESCACHEESX)*2];
    bool m_gauche[NBR_CASES_H-CASESCACHEESY*2+1];
    bool m_droite[NBR_CASES_H-CASESCACHEESY*2+1];
    Data *m_donnees_editeur;
    int m_undo;
};

double calculAngle(int x, int y);
bool auMilieu(double petitAngle,double grandAngle,double milieu,int d);
void droiteExtremes(QList<double>droites,double &max,double &min);
void calculContoursCase(int x,int y,int mlcase,int mhcase,double &max,double &min);
Dir orientation_vers_objet(QPoint const& pos, QPoint const& pos_obj);


#endif // DATAMAP_H
