#ifndef RECETTE_H
#define RECETTE_H

class Resources;
#include "inventory/resource.h"

class Recipe
{
public:
    Recipe(Resource *objet_cree, QStringList & ingredients, Resources *ressources);
    Resource *objet_cree() const { return m_objet_cree; }
    QVector<Resss> ingredients() const { return m_ingredients; }
    int nombre_cases() const { return m_ingredients.size(); }

private:
    Resource *m_objet_cree;
    QVector<Resss>m_ingredients;
};

#endif // RECETTE_H
