#ifndef RECETTES_H
#define RECETTES_H

#include <QVBoxLayout>
#include "jobs/job.h"
#include "graphicElements/items.h"

class AfficheRecette : public QWidget
{
public:
    AfficheRecette(Recette *recette, Metier *metier, LesRessources *lesressources, int num);

private:
    int m_num;
};


class Recettes : public QVBoxLayout
{
    Q_OBJECT
public:
    Recettes(Metier *metier, LesRessources *lesressources);
    
signals:

private:

    Metier *metier;
    
};

#endif // RECETTES_H
