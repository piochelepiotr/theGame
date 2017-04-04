#include "jobs/recipes.h"

DisplayRecipe::DisplayRecipe(Recipe *recette, Job *metier, Resources *lesresources, int num)
{
    m_num = num;
    QVector<Resss> ingredients = recette->ingredients();
    int lvl_recette = lvlPourXCases(ingredients.size());
    QLabel *texte_recette = new QLabel(recette->objet_cree()->name()+trUtf8(" Niveau ")+QString::number(lvl_recette)+" "+metier->getMetierBase()->verbe_recettes()+" "+QString::number(xpParCase(ingredients.size()))+" xp");
    QHBoxLayout *layout_ingredients = new QHBoxLayout;
    QHBoxLayout *layout_top_recette = new QHBoxLayout;
    QVBoxLayout *layout_recette = new QVBoxLayout;
    layout_top_recette->addWidget(item(lesresources, recette->objet_cree()));
    layout_top_recette->addWidget(texte_recette);
    int k;
    for(k = 0; k < ingredients.size(); k++)
    {
        layout_ingredients->addWidget(item(lesresources, ingredients[k].ress, ingredients[k].nbr));
    }
    for(; k <METIER_NBR_CASES_DEPART+METIER_LVL_MAX/METIER_LVLS_1CASEENPLUS; k++)
    {
        layout_ingredients->addWidget(new ResourceItem());
    }

    setLayout(layout_recette);
    layout_recette->addLayout(layout_top_recette);
    layout_recette->addLayout(layout_ingredients);

    if(lvl_recette > metier->getLvl())
    {
        setEnabled(false);
    }
}


Recipes::Recipes(Job *metier, Resources *lesresources)
{
    QStringList recettes = metier->getMetierBase()->recettes();
    for(int j = 0; j < recettes.size(); j++)
    {
        addWidget(new DisplayRecipe(metier->getMetierBase()->recette(recettes[j]), metier, lesresources, j));
    }
}
