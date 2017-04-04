#include "jobs/jobs.h"

Jobs::Jobs(Resources *resources, Scenery *decors)
{
    QFile fichier(QString(DONNEES)+QString("metiers.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        QString ligne;
        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
                m_metiers[ligne.section('/',0,0)] = new JobModel(ligne, decors,resources);
        }
        fichier.close();
        QMap<qint16,InteractiveObject*>objets_coupables;
        for(QMap<QString, JobModel*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
        {
            objets_coupables = it.value()->get_objets_coupables();
            for(QMap<qint16,InteractiveObject*>::iterator it2 = objets_coupables.begin(); it2 != objets_coupables.end(); it2++)
            {
                m_souches_to_objets[it2.value()->getSouche()->numero()] = it2.value()->getObjet();
                m_objets_to_souches[it2.value()->getObjet()->numero()] = it2.value()->getSouche();
            }
            m_objets_coupables.unite(it.value()->objets_coupables());
        }
    }
}

Jobs::~Jobs()
{
    for(QMap<QString, JobModel*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        delete it.value();
    }
}

JobModel *Jobs::forge_to_metier(Object *forge)
{
    for(QMap<QString, JobModel*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        if(it.value()->objet_recette() == forge)
        {
            return it.value();
        }
    }
    return 0;
}

JobModel *Jobs::objet_coupable_to_metier(Object *objet)
{
    for(QMap<QString, JobModel*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        if(it.value()->coupe(objet->numero()))
        {
            return it.value();
        }
    }
    return 0;
}

Object *Jobs::getObjetParSouche(qint16 num) const
{
    if(m_souches_to_objets.contains(num))
        return m_souches_to_objets[num];
    else
        return 0;
}

Object *Jobs::getSoucheParObjet(qint16 num) const
{
    if(m_objets_to_souches.contains(num))
        return m_objets_to_souches[num];
    else
        return 0;
}
