#ifndef FAIRERECETTES_H
#define FAIRERECETTES_H

#include <QDialog>
#include "scenery/scenery.h"
#include "entities/character.h"
#include "inventory/inventory.h"
#include "infoMonde/recettes.h"
#include "network/reseau.h"
#include <QTimer>

class Ressource_type
{
public:

    enum Type{AucunType, UneRessource,UnEquipement, UneArme};

    Ressource_type();
    Ressource_type(Arme *arme, int nombre = 1);
    Ressource_type(Equipement *equipement, int nombre = 1);
    Ressource_type(Ressource *ressource, int nombre = 1);
    void setVide();
    void setArme(Arme *arme, int nombre = 1);
    void setEquipement(Equipement *equipement, int nombre = 1);
    void setRessource(Ressource *ressource, int nombre = 1);
    Type type() const { return m_type; }
    Arme *arme() const { return m_arme; }
    Equipement *equipement() const { return m_equipement; }
    Ressource *ressource() const { return m_ressource; }
    void ajoute(int nombre = 1) { m_nombre += nombre; }
    bool enleve(int nombre = 1);
    int nombre() const { return m_nombre; }

private:

    Type m_type;
    Arme *m_arme;
    Equipement *m_equipement;
    Ressource *m_ressource;
    int m_nombre;
};


namespace Ui{
class FaireRecettes;
}

class FaireRecettes : public QDialog
{
    Q_OBJECT
    
public:
    FaireRecettes(QWidget *parent,QString const& metier, Donnees_editeur *donnees_editeur, Personnage *personnage, Reseau *reseau);
    ~FaireRecettes();
    Recette *chercheRecette(int *quantite);
    void metAJourRecette();

public slots:
    void double_clique_armes(int num);
    void double_clique_equipements(int num);
    void double_clique_ressources(int num);

    void double_clicue_ingredients(int num);
    void lance1fois();
    void lancexfois();
    void encoreUneFois();
    void vide(bool efface_ingredients);
    
private:
    Reseau *m_reseau;
    Inventaire_complet *m_inventaire;
    Items *m_items;
    Ui::FaireRecettes *ui;
    Metier *m_metier;
    Donnees_editeur *m_donnees_editeur;
    Personnage *m_personnage;
    QVector<Ressource_type>m_ingredients;
    Item *m_objet_cree;
    Recette *m_recette;
};

#endif // FAIRERECETTES_H
