#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QString>
#include <QPoint>
#include "infoMonde/ressource.h"
#include "equipement.h"
#include "infoJoueur/arme.h"
#include "infoMonde/lesressources.h"
#include <QVector>
#include "infoJoueur/metier.h"
#include <QFile>
#include <QTextStream>
#include "elementsMonde/donnees_editeur.h"
#include "additionalActions/point.h"
#include "math.h"
#include "infoMonde/creature.h"

#define BASE_POD 1000
#define NBR_PODS_LVL 100


class Personnage : public Creature
{

public:
    Personnage(QString const& donnees, Donnees_editeur *donnees_editeur);
    Personnage(const QString &nom, QString classe, Donnees_editeur *donnees_editeur);
    ~Personnage();
    QStringList getMetiers();
    QString enString() const;
    /*QString getNom() const { return m_nom; }
    QString getClasse() const { return m_classe; }
    QString caracteristiques() const;*/
    int getPods() const;
    int getPodsMax() const;

    void apprendMetier(QString nom);

    /*int getBaseVie() const { return m_base_vie; }
    int getBaseForce() const { return m_base_force; }
    int getBasePC() const { return m_base_pc; }*/

    int getBonusVie() const;
    int getBonusForce() const;
    int getBonusPC() const;

    /*int getTotalVie() const { return m_base_vie+getBonusVie(); }
    int getTotalForce() const { return m_base_force+getBonusForce(); }
    int getTotalPC() const { return m_base_pc+getBonusPC(); }*/

    int getArgent() const { return m_argent; }
    int getXp() const { return m_xp; }
    //int getNiveau() const { return m_niveau; }

    Ressource *ressnum(int i) const { return m_ressources[i].ress; }
    Equipement *equipement_num(int i) const { return m_equipements[i].equipement; }
    Arme *armenum(int i) const { return m_armes[i].arme; }
    Metier *getMetier(QString const& nom) const { return m_metiers[nom]; }
    QVector<Resss>getRessources() const { return m_ressources; }
    QVector<Eqips>getEquipements() const { return m_equipements; }
    QVector<Armes>getArmes() const { return m_armes; }
    void setNombreRessources(int num, Resss ressource);
    void setNombreEquipements(int num, Eqips equipement);
    void setNombreArmes(int num, Armes arme);

    /*int getMaxVie() const { return m_base_vie; }
    int getForce() const { return m_base_force; }

    int getPosY() const { return m_posY; }
    int getPosX() const { return m_posX; }
    int getPosZ() const { return m_posZ; }
    Point getPos() const { return Point(m_posX,m_posY,m_posZ); }

    QPoint getPosMap() const { return QPoint(m_posmapx, m_posmapy); }
    int *getaddposmapx() { return &m_posmapx; }
    int *getaddposmapy() { return &m_posmapy; }
    void setPosMap(int x, int y);

    void setPosX(int posX) { m_posX = posX; }
    void setPosY(int posY) { m_posY = posY; }
    void setPosZ(int posZ) { m_posZ = posZ; }*/

    QString gagneRessources(Ressource *ressource, int nombre, int *indexDernier = 0);

    /////////////////////////////////////////////////

    Equipement *cape() const { return m_cape; }
    void setCape(Equipement *cape) { m_cape = cape; }
    Equipement *coiffe() const { return m_coiffe; }
    void setCoiffe(Equipement *coiffe) { m_coiffe = coiffe; }
    Equipement *anod() const { return m_anod; }
    void setAnod(Equipement *anod) { m_anod = anod; }
    Equipement *anog() const { return m_anog; }
    void setAnog(Equipement *anog) { m_anog = anog; }
    Equipement *amulette() const { return m_amulette; }
    void setAmulette(Equipement *amulette) { m_amulette = amulette; }
    Equipement *ceinture() const { return m_ceinture; }
    void setCeinture(Equipement *ceinture) { m_ceinture = ceinture; }
    Equipement *bottes() const { return m_bottes; }
    void setBottes(Equipement *bottes) { m_bottes = bottes; }
    Arme *arme() const { return m_arme; }
    void setArme(Arme *arme) { m_arme = arme; }

    ///////////////////////////////////////////////


    int indexRessource(Ressource *ressource, int *quantite = 0);
    void enleverRessource(int num, int nbr);


    int indexEquipement(Equipement *equipement, int *quantite = 0);
    void enleverEquipement(int num, int nbr);


    int indexArme(Arme *arme, int *quantite = 0);
    void enleverArme(int num, int nbr);

    int equipeEquipement(int num,QString const& categorie, bool *anneau_gauche = 0);
    int equipeArme(int num);
    int desequipe(int num);
    int desequipeArme();

    bool peutequipe(Equipement *equip);

    //QString important();



    //int getVie() const { return m_vie; }

    /*void nouveau_tour() { m_pc_combat = getTotalPC(); }
    void use_pc(int nbr) { m_pc_combat = m_pc_combat - nbr; }
    int getPCCombat() { return m_pc_combat; }*/

    int ajouterArme(Armes const& armes);
    int ajouterEquipement(Eqips const& equipement);
    int ajouterRessource(Resss const& resss);

    int ajouterArme(Arme *arme);
    int ajouterEquipement(Equipement *equipement);
    int ajouterRessource(Ressource *ressource);

    /*void setEquipe(int equipe) { m_equipe = equipe; }
    int equipe() const {return m_equipe; }

    void setPret(bool pret) { m_pret = pret; }
    bool pret() const { return m_pret; }

    void setTour(bool tour) { m_monTour = tour; }
    bool monTour() const { return m_monTour; }

    void setEnCombat(bool enCombat);
    bool enCombat() const { return m_enCombat; }

    void perdVie(int degats);

    QMap<QString,Sort*> sorts() const { return m_sorts; }
    Donnees_editeur *donneesEditeur() const { return m_donnees_editeur; }

    bool peutUtiliserSort(QString const& nom);*/
    Sort *getSort(QString const& nom);
    QString gagneFinCombat(int niveauAutreEquipe, bool victoire);
    void gagneXp(int xp);
    void metAJourNiveau();
    static int xpDeNiveau(int niveau);

private:

    QVector<Resss>m_ressources;
    QVector<Eqips>m_equipements;
    QVector<Armes>m_armes;
    int m_argent;
    //int m_posX;
    //int m_posY;
    //int m_posZ;
    //int m_posmapx;
    //int m_posmapy;
    //QPoint m_posHorsCombat;
    //QString m_nom;
    //QString m_classe;
   // int m_base_vie;
   // int m_base_force;
   // int m_base_pc;
    int m_xp;
    //int m_niveau;

    //combat

    //int m_vie;
    //int m_pc_combat;
    //int m_equipe;
    //bool m_pret;
    //bool m_monTour;
    //bool m_enCombat;

    Equipement *m_cape;
    Equipement *m_coiffe;
    Equipement *m_anod;
    Equipement *m_anog;
    Equipement *m_bottes;
    Equipement *m_ceinture;
    Equipement *m_amulette;
    Arme *m_arme;
    QMap<QString, Metier*>m_metiers;
    //QMap<QString,Sort*>m_sorts;

    //pour s'équiper

    bool m_met_anneau_gauche;
    //Donnees_editeur *m_donnees_editeur;
};

#endif // PERSONNAGE_H
