#include "jobs/jobModel.h"
#include "inventory/resources.h"
#include "scenery/scenery.h"

JobModel::JobModel(const QString &donnees, Scenery *decors, Resources *ressources)
{
    QStringList liste = donnees.split('/');
    m_nom = liste[0];
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
    QString ressource;
    int lvl;
    while(liste[0] != "RECETTES")
    {
        ressource = liste[0];
        liste.pop_front();
        numObj = liste[0].toInt();
        liste.pop_front();
        numSouche = liste[0].toInt();
        liste.pop_front();
        lvl = liste[0].toInt();
        liste.pop_front();
        m_objets_coupables[numObj] = new InteractiveObject(decors->objet(numObj),decors->objet(numSouche), ressources->getRessource(ressource), lvl);
    }
    liste.pop_front();
    while(liste[0] != "FINRECETTES")
    {
        ressource = liste[0];
        liste.pop_front();
        m_recettes[ressource] = new Recipe(ressources->getRessource(ressource), liste, ressources);
    }
}

QVector<qint16> JobModel::ressources_coupables(int lvl)
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
