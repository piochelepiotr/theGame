#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <QString>
#include <QPoint>
#include "inventory/resource.h"
#include "inventory/outfit.h"
#include "inventory/weapon.h"
#include "inventory/resources.h"
#include <QVector>
#include "jobs/job.h"
#include <QFile>
#include <QTextStream>
#include "scenery/data.h"
#include "map/point.h"
#include "math.h"
#include "entities/entity.h"

#define BASE_POD 1000
#define NBR_PODS_LVL 100


class Character : public Entity
{

public:
    Character(QString const& donnees, Data *donnees_editeur);
    Character(const QString &nom, QString classe, Data *donnees_editeur);
    ~Character();
    QStringList getJobs();
    QString toString() const;
    int getPods() const;
    int getPodsMax() const;
    void learnJob(QString nom);
    int getBonusVie() const;
    int getBonusForce() const;
    int getBonusPC() const;
    int getArgent() const { return m_argent; }
    int getXp() const { return m_xp; }

    Resource *ressnum(int i) const { return m_resources[i].ress; }
    Outfit *equipement_num(int i) const { return m_equipements[i].equipement; }
    Weapon *armenum(int i) const { return m_armes[i].arme; }
    Job *getMetier(QString const& nom) const { return m_metiers[nom]; }
    QVector<Resss>getRessources() const { return m_resources; }
    QVector<Eqips>getEquipements() const { return m_equipements; }
    QVector<Armes>getArmes() const { return m_armes; }
    void setNombreRessources(int num, Resss resource);
    void setNombreEquipements(int num, Eqips equipement);
    void setNombreArmes(int num, Armes arme);

    QString gagneRessources(Resource *resource, int quantity, int *indexDernier = 0);

    /////////////////////////////////////////////////

    Outfit *cape() const { return m_cape; }
    void setCape(Outfit *cape) { m_cape = cape; }
    Outfit *coiffe() const { return m_coiffe; }
    void setCoiffe(Outfit *coiffe) { m_coiffe = coiffe; }
    Outfit *anod() const { return m_anod; }
    void setAnod(Outfit *anod) { m_anod = anod; }
    Outfit *anog() const { return m_anog; }
    void setAnog(Outfit *anog) { m_anog = anog; }
    Outfit *amulette() const { return m_amulette; }
    void setAmulette(Outfit *amulette) { m_amulette = amulette; }
    Outfit *ceinture() const { return m_ceinture; }
    void setCeinture(Outfit *ceinture) { m_ceinture = ceinture; }
    Outfit *bottes() const { return m_bottes; }
    void setBottes(Outfit *bottes) { m_bottes = bottes; }
    Weapon *arme() const { return m_arme; }
    void setArme(Weapon *arme) { m_arme = arme; }

    ///////////////////////////////////////////////


    int indexRessource(Resource *resource, int *quantite = 0);
    void enleverRessource(int num, int nbr);


    int indexEquipement(Outfit *equipement, int *quantite = 0);
    void enleverEquipement(int num, int nbr);


    int indexArme(Weapon *arme, int *quantite = 0);
    void enleverArme(int num, int nbr);

    int equipeEquipement(int num,QString const& categorie, bool *anneau_gauche = 0);
    int equipeArme(int num);
    int desequipe(int num);
    int desequipeArme();

    bool peutequipe(Outfit *equip);

    int ajouterArme(Armes const& armes);
    int ajouterEquipement(Eqips const& equipement);
    int ajouterRessource(Resss const& resss);

    int ajouterArme(Weapon *arme);
    int ajouterEquipement(Outfit *equipement);
    int ajouterRessource(Resource *resource);
    Spell *getSpell(QString const& nom);
    QString gagneFinFight(int niveauAutreEquipe, bool victoire);
    void gagneXp(int xp);
    void metAJourNiveau();
    static int xpDeNiveau(int niveau);

    virtual bool isMonster() { return false; }

private:

    QVector<Resss>m_resources;
    QVector<Eqips>m_equipements;
    QVector<Armes>m_armes;
    int m_argent;
    int m_xp;

    Outfit *m_cape;
    Outfit *m_coiffe;
    Outfit *m_anod;
    Outfit *m_anog;
    Outfit *m_bottes;
    Outfit *m_ceinture;
    Outfit *m_amulette;
    Weapon *m_arme;
    QMap<QString, Job*>m_metiers;

    bool m_met_anneau_gauche;
};

#endif // PERSONNAGE_H
