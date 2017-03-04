#include "touslesmetiers.h"

TouslesMetiers::TouslesMetiers(LesRessources *ressources, Decors *decors)
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
                m_metiers[ligne.section('/',0,0)] = new Metier_Base(ligne, decors,ressources);
        }
        fichier.close();
        QMap<qint16,Objet_coupable*>objets_coupables;
        for(QMap<QString, Metier_Base*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
        {
            objets_coupables = it.value()->get_objets_coupables();
            for(QMap<qint16,Objet_coupable*>::iterator it2 = objets_coupables.begin(); it2 != objets_coupables.end(); it2++)
            {
                m_souches_to_objets[it2.value()->getSouche()->numero()] = it2.value()->getObjet();
                m_objets_to_souches[it2.value()->getObjet()->numero()] = it2.value()->getSouche();
            }
            m_objets_coupables.unite(it.value()->objets_coupables());
        }
    }
}

TouslesMetiers::~TouslesMetiers()
{
    for(QMap<QString, Metier_Base*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        delete it.value();
    }
}

Metier_Base *TouslesMetiers::forge_to_metier(Objet *forge)
{
    for(QMap<QString, Metier_Base*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        if(it.value()->objet_recette() == forge)
        {
            return it.value();
        }
    }
    return 0;
}

Metier_Base *TouslesMetiers::objet_coupable_to_metier(Objet *objet)
{
    for(QMap<QString, Metier_Base*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        if(it.value()->coupe(objet->numero()))
        {
            return it.value();
        }
    }
    return 0;
}

Objet *TouslesMetiers::getObjetParSouche(qint16 num) const
{
    if(m_souches_to_objets.contains(num))
        return m_souches_to_objets[num];
    else
        return 0;
}

Objet *TouslesMetiers::getSoucheParObjet(qint16 num) const
{
    if(m_objets_to_souches.contains(num))
        return m_objets_to_souches[num];
    else
        return 0;
}
