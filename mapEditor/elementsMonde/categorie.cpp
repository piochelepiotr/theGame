#include "categorie.h"

Categorie::Categorie(const QString &nom)
{
    m_nom = nom;
}

void Categorie::ajouteObjet(Objet *objet)
{
    m_objets[objet->numero()] = objet;
}

void Categorie::supprimeObjet(Objet *objet)
{
    m_objets.remove(objet->numero());
}
