#include "recette.h"
#include "infoMonde/lesressources.h"

Recette::Recette(Ressource *objet_cree, QStringList & ingredients, LesRessources *ressources)
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
