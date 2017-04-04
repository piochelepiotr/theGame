#include "jobs/jobModel.h"
#include "inventory/resources.h"
#include "scenery/scenery.h"

JobModel::JobModel(const QString &donnees, Scenery *decors, Resources *resources)
{
    QStringList liste = donnees.split('/');
    m_name = liste[0];
    liste.pop_front();
    m_objet_recettes = decors->objet(liste[0].toInt());
    liste.pop_front();
    m_verbe_recettes = liste[0];
    liste.pop_front();
    m_raccourci = liste[0];
    liste.pop_front();
    m_arme = liste[0];
    liste.pop_front();
    m_verbe = liste[0];
    liste.pop_front();
    qint16 numObj, numSouche;
    QString resource;
    int lvl;
    while(liste[0] != "RECETTES")
    {
        resource = liste[0];
        liste.pop_front();
        numObj = liste[0].toInt();
        liste.pop_front();
        numSouche = liste[0].toInt();
        liste.pop_front();
        lvl = liste[0].toInt();
        liste.pop_front();
        m_objets_coupables[numObj] = new InteractiveObject(decors->objet(numObj),decors->objet(numSouche), resources->getRessource(resource), lvl);
    }
    liste.pop_front();
    while(liste[0] != "FINRECETTES")
    {
        resource = liste[0];
        liste.pop_front();
        m_recettes[resource] = new Recipe(resources->getRessource(resource), liste, resources);
    }
}

QVector<qint16> JobModel::resources_coupables(int lvl)
{
    QVector<qint16>objets;
    for(QMap<qint16,InteractiveObject*>::iterator it = m_objets_coupables.begin(); it != m_objets_coupables.end(); it++)
    {
        if(it.value()->lvl() <= lvl)
        {
            objets.push_back(it.key());
        }
    }
    return objets;
}

QMap<qint16,Object*> JobModel::objets_coupables() const
{
    QMap<qint16, Object*>objets;
    for(QMap<qint16,InteractiveObject*>::const_iterator it = m_objets_coupables.begin(); it != m_objets_coupables.end(); it++)
    {
        objets[it.key()] = it.value()->getObjet();
    }
    return objets;
}

JobModel::~JobModel()
{
    for(QMap<qint16,InteractiveObject*>::iterator it = m_objets_coupables.begin(); it != m_objets_coupables.end(); it++)
    {
        delete it.value();
    }

    for(QMap<QString,Recipe*>::iterator it = m_recettes.begin(); it != m_recettes.end(); it++)
    {
        delete it.value();
    }
}
