#include "jobs/recipe.h"
#include "inventory/resources.h"

Recipe::Recipe(Resource *objet_cree, QStringList & ingredients, Resources *ressources)
{
    m_objet_cree = objet_cree;
    Resss resss;
    while(ingredients[0] != "FR")
    {
        resss.ress = ressources->getRessource(ingredients[0]);
        ingredients.pop_front();
        resss.nbr = ingredients[0].toInt();
        ingredients.pop_front();
        m_ingredients.push_back(resss);
    }
    ingredients.pop_front();
}
