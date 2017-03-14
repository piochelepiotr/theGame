#ifndef CREATURE_H
#define CREATURE_H


#include <QString>
#include <QPoint>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "map/point.h"
#include "math.h"
#include "entities/spell.h"
#include "jobs/job.h"

class Donnees_editeur;

class Creature
{
public:
    Creature(const QString &nom, QString const& classe, Donnees_editeur *donnees_editeur);
    ~Creature();
    QString getNom() const { return m_nom; }
    QString getClasse() const { return m_classe; }
    int getNiveau() const { return m_niveau; }

    //caractéristiques

    QString caracteristiques() const;

    int getBaseVie() const { return m_base_vie; }
    int getBaseForce() const { return m_base_force; }
    int getBasePC() const { return m_base_pc; }

    int getBonusVie() const;
    int getBonusForce() const;
    int getBonusPC() const;

    int getTotalVie() const { return m_base_vie+getBonusVie(); }
    int getTotalForce() const { return m_base_force+getBonusForce(); }
    int getTotalPC() const { return m_base_pc+getBonusPC(); }

    //position

    int getPosY() const { return m_posY; }
    int getPosX() const { return m_posX; }
    int getPosZ() const { return m_posZ; }
    Point getPos() const { return Point(m_posX,m_posY,m_posZ); }

    QPoint getPosMap() const { return QPoint(m_posmapx, m_posmapy); }
    int *getaddposmapx() { return &m_posmapx; }//houla ! c'est pas bien ^^
    int *getaddposmapy() { return &m_posmapy; }
    void setPosMap(int x, int y);

    void setPosX(int posX) { m_posX = posX; }
    void setPosY(int posY) { m_posY = posY; }
    void setPosZ(int posZ) { m_posZ = posZ; }


    //

    QString important();//la description pour les autres personnes de la map (à transmettre par le réseau)

    //combats

    int getVie() const { return m_vie; }
    int getPCCombat() { return m_pc_combat; }

    void use_pc(int nbr) { m_pc_combat = m_pc_combat - nbr; }
    void perdVie(int degats);
    void nouveau_tour() { m_pc_combat = getTotalPC(); }  

    void setPret(bool pret) { m_pret = pret; }
    bool pret() const { return m_pret; }

    void setTour(bool tour) { m_monTour = tour; }
    bool monTour() const { return m_monTour; }

    void setEnCombat(bool enCombat);
    bool enCombat() const { return m_enCombat; }

    void setEquipe(int equipe) { m_equipe = equipe; }
    int equipe() const {return m_equipe; }

    QMap<QString,Sort*> sorts() const { return m_sorts; }

    bool peutUtiliserSort(QString const& nom);
    Sort *getSort(QString const& nom);
    QString gagneFinCombat(int, bool victoire);

    //
    Donnees_editeur *donneesEditeur() const { return m_donnees_editeur; }

protected:

    int m_posX;
    int m_posY;
    int m_posZ;
    int m_posmapx;
    int m_posmapy;
    QPoint m_posHorsCombat;
    QString m_nom;
    QString m_classe;
    int m_base_vie;
    int m_base_force;
    int m_base_pc;
    int m_niveau;

    //combat

    int m_vie;
    int m_pc_combat;
    int m_equipe;
    bool m_pret;
    bool m_monTour;
    bool m_enCombat;

    QMap<QString,Sort*>m_sorts;

    //pour s'équiper

    Donnees_editeur *m_donnees_editeur;
};

#endif // CREATURE_H
