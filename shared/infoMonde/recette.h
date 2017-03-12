#ifndef RECETTE_H
#define RECETTE_H

class LesRessources;
#include "ressource.h"

class Recette
{
public:
    Recette(Ressource *objet_cree, QStringList & ingredients, LesRessources *ressources);
    Ressource *objet_cree() const { return m_objet_cree; }
    QVector<Resss> ingredients() const { return m_ingredients; }
    int nombre_cases() const { return m_ingredients.size(); }

private:
    Ressource *m_objet_cree;
    QVector<Resss>m_ingredients;
};

#endif // RECETTE_H
