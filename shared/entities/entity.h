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

class Data;

class Entity
{
public:
    Entity(const QString &name, QString const& classe, Data *donnees_editeur);
    ~Entity();
    QString getNom() const { return m_name; }
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

    virtual bool isMonster()=0;


    //

    QString important();//la description pour les autres personnes de la map (à transmettre par le réseau)

    //fights

    void setFullLife() { m_vie = m_base_vie; }

    int getVie() const { return m_vie; }
    int getPCFight() { return m_pc_fight; }

    void use_pc(int nbr) { m_pc_fight = m_pc_fight - nbr; }
    void perdVie(int degats);
    void nouveau_tour() { m_pc_fight = getTotalPC(); }  

    void setPret(bool pret) { m_pret = pret; }
    bool pret() const { return m_pret; }

    void setTour(bool tour) { m_monTour = tour; }
    bool monTour() const { return m_monTour; }

    void setFightId(int fightId);
    bool enFight() const { return m_fightId != -1; }
    int getFightId() const { return m_fightId; }

    void setEquipe(int equipe) { m_equipe = equipe; }
    int equipe() const {return m_equipe; }

    QMap<QString,Spell*> spells() const { return m_spells; }

    bool peutUtiliserSpell(QString const& name);
    virtual Spell *getSpell(QString const& name);
    QString gagneFinFight(int, bool victoire);

    //
    Data *donneesEditeur() const { return m_donnees_editeur; }

protected:

    int m_posX;
    int m_posY;
    int m_posZ;
    int m_posmapx;
    int m_posmapy;
    QPoint m_posHorsFight;
    QString m_name;
    QString m_classe;
    int m_base_vie;
    int m_base_force;
    int m_base_pc;
    int m_niveau;

    //fight

    int m_vie;
    int m_pc_fight;
    int m_equipe;
    bool m_pret;
    bool m_monTour;
    int m_fightId;

    QMap<QString,Spell*>m_spells;

    //pour s'équiper

    Data *m_donnees_editeur;
};

#endif // CREATURE_H
