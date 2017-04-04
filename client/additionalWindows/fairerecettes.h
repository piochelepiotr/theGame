#ifndef FAIRERECETTES_H
#define FAIRERECETTES_H

#include <QDialog>
#include "scenery/scenery.h"
#include "entities/character.h"
#include "inventory/inventory.h"
#include "jobs/recipes.h"
#include "network/reseau.h"
#include <QTimer>

class Ressource_type
{
public:

    enum Type{AucunType, UneRessource,UnEquipement, UneArme};

    Ressource_type();
    Ressource_type(Weapon *arme, int quantity = 1);
    Ressource_type(Outfit *equipement, int quantity = 1);
    Ressource_type(Resource *resource, int quantity = 1);
    void setVide();
    void setArme(Weapon *arme, int quantity = 1);
    void setEquipement(Outfit *equipement, int quantity = 1);
    void setRessource(Resource *resource, int quantity = 1);
    Type type() const { return m_type; }
    Weapon *arme() const { return m_arme; }
    Outfit *equipement() const { return m_equipement; }
    Resource *resource() const { return m_resource; }
    void ajoute(int quantity = 1) { m_quantity += quantity; }
    bool enleve(int quantity = 1);
    int quantity() const { return m_quantity; }

private:

    Type m_type;
    Weapon *m_arme;
    Outfit *m_equipement;
    Resource *m_resource;
    int m_quantity;
};


namespace Ui{
class FaireRecettes;
}

class FaireRecettes : public QDialog
{
    Q_OBJECT
    
public:
    FaireRecettes(QWidget *parent,QString const& metier, Data *donnees_editeur, Character *personnage, Reseau *reseau);
    ~FaireRecettes();
    Recipe *chercheRecette(int *quantite);
    void metAJourRecette();

public slots:
    void double_clique_armes(int num);
    void double_clique_equipements(int num);
    void double_clique_resources(int num);

    void double_clicue_ingredients(int num);
    void lance1fois();
    void lancexfois();
    void encoreUneFois();
    void vide(bool efface_ingredients);
    
private:
    Reseau *m_reseau;
    Inventaire_complet *m_inventaire;
    ResourceItems *m_items;
    Ui::FaireRecettes *ui;
    Job *m_metier;
    Data *m_donnees_editeur;
    Character *m_personnage;
    QVector<Ressource_type>m_ingredients;
    ResourceItem *m_objet_cree;
    Recipe *m_recette;
};

#endif // FAIRERECETTES_H
