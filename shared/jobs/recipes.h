#ifndef RECETTES_H
#define RECETTES_H

#include <QVBoxLayout>
#include "jobs/job.h"
#include "graphic/resourceItems.h"

class DisplayRecipe : public QWidget
{
public:
    DisplayRecipe(Recipe *recette, Job *metier, Resources *lesresources, int num);

private:
    int m_num;
};


class Recipes : public QVBoxLayout
{
    Q_OBJECT
public:
    Recipes(Job *metier, Resources *lesresources);
    
signals:

private:

    Job *metier;
    
};

#endif // RECETTES_H
