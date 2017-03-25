#include "inventory/resources.h"

Resources::Resources()
{
    QStringList liste;
    QString ligne;
    QFile fichier_ressources("../data/Ressources/ressources.txt");
    QFile fichier_equipements("../data/Ressources/equipements.txt");
    QFile fichier_armes("../data/Ressources/armes.txt");

    QFile fichier_sorts(QString(DONNEES)+QString("sorts.txt"));
    if(fichier_sorts.open(QIODevice::ReadOnly))
    {
        QTextStream stream_sorts(&fichier_sorts);
        while(!stream_sorts.atEnd())
        {
            ligne = stream_sorts.readLine();
            if(!ligne.isEmpty())
            {
                m_sorts[ligne.section('/', 0, 0)] = new SpellModel(ligne);
            }
        }
        fichier_sorts.close();
    }


    if(fichier_ressources.open(QIODevice::ReadOnly) && fichier_equipements.open(QIODevice::ReadOnly)&& fichier_armes.open(QIODevice::ReadOnly))
    {
        QTextStream stream_ressources(&fichier_ressources), stream_equipements(&fichier_equipements), stream_armes(&fichier_armes);

        while(!stream_ressources.atEnd())
        {
            ligne = stream_ressources.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_ressources[liste[0]] = new Resource(liste[0], liste[1].toInt(), liste[2], liste[3].toInt(), liste[4]);
            }
        }

        while(!stream_equipements.atEnd())
        {
            ligne = stream_equipements.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_equipements[liste[0]] = new OutfitModel(m_ressources[liste[0]], liste[1].toInt(), liste[2].toInt(), liste[3].toInt(), liste[4].toInt(), liste[5].toInt(), liste[6].toInt());
            }
        }

        while(!stream_armes.atEnd())
        {
            ligne = stream_armes.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_armes[liste[0]] = new WeaponModel(m_equipements[liste[0]], m_sorts[liste[1]]);
            }
        }

        fichier_ressources.close();
        fichier_equipements.close();
        fichier_armes.close();
    }

    QFile fichier_classes(QString(DONNEES)+QString("classes.txt"));
    if(fichier_classes.open(QIODevice::ReadOnly))
    {
        QTextStream stream_classes(&fichier_classes);
        while(!stream_classes.atEnd())
        {
            ligne = stream_classes.readLine();
            if(!ligne.isEmpty())
            {
                m_classes[ligne.section('/', 0, 0)] = new CharacterModel(ligne, m_sorts);
            }
        }
        fichier_classes.close();
        for(QMap<QString, CharacterModel*>::iterator it = m_classes.begin(); it != m_classes.end(); it++)
        {
            m_numClasses.push_back(it.key());
        }
    }
    QFile fichier_monstres(QString(DONNEES)+QString("monstres.txt"));
    if(fichier_monstres.open(QIODevice::ReadOnly))
    {
        QTextStream stream_monstres(&fichier_monstres);
        while(!stream_monstres.atEnd())
        {
            ligne = stream_monstres.readLine();
            if(!ligne.isEmpty())
            {
                m_monstres[ligne.section('/', 0, 0)] = new MonsterModel(ligne, m_sorts);
            }
        }
        fichier_monstres.close();
    }
}

void Resources::ajouteRessource(Resource *ressource)
{
    m_ressources[ressource->nom()] = ressource;
}

void Resources::ajouteEquipement(OutfitModel *equipement)
{
    ajouteRessource(equipement->getRessource());
    m_equipements[equipement->getRessource()->nom()] = equipement;
}

void Resources::ajouteArme(WeaponModel *arme)
{
    ajouteEquipement(arme->getEquipement());
    m_armes[arme->getEquipement()->getRessource()->nom()] = arme;
}

void Resources::ajouteSort(SpellModel *sort)
{
    m_sorts[sort->nom()] = sort;
}

void Resources::enleveRessource(QString const& nom)
{
    if(m_ressources.contains(nom))
    {
        delete m_ressources[nom];
        m_ressources.remove(nom);
    }
}

void Resources::enleveEquipement(QString const& nom)
{
    if(m_equipements.contains(nom))
    {
        delete m_equipements[nom];
        m_equipements.remove(nom);
    }
}

void Resources::enleveArme(QString const& nom)
{
    if(m_armes.contains(nom))
    {
        delete m_armes[nom];
        m_armes.remove(nom);
    }
}

void Resources::enleveSort(QString const& nom)
{
    if(m_sorts.contains(nom))
    {
        delete m_sorts[nom];
        m_sorts.remove(nom);
    }
}

Resource *Resources::getRessource(QString const& nom) const
{
    if(nom == "-1" || !m_ressources.contains(nom))
        return 0;
    return m_ressources[nom];
}

OutfitModel *Resources::getEquipement(QString const& nom) const
{
    if(nom == "-1" || !m_equipements.contains(nom))
        return 0;
    return m_equipements[nom];
}

WeaponModel *Resources::getArme(QString const& nom) const
{
    if(nom == "-1" || !m_armes.contains(nom))
        return 0;
    return m_armes[nom];
}

SpellModel *Resources::getSort(const QString &nom) const
{
    if(nom == "-1" || !m_sorts.contains(nom))
        return 0;
    return m_sorts[nom];
}

CharacterModel *Resources::getClasse(QString const& nom) const
{
    if(!m_classes.contains(nom))
        return 0;
    return m_classes[nom];
}

MonsterModel *Resources::getMonstre(QString const& nom) const
{
    if(!m_monstres.contains(nom))
        return 0;
    return m_monstres[nom];
}

EntityModel *Resources::getCreature(QString const& name) const
{
    EntityModel *creature = getMonstre(name);
    if(!creature)
        creature = getClasse(name);
    return creature;
}

QStringList Resources::sorts() const
{
    QStringList liste;
    for(QMap<QString, SpellModel*>::const_iterator it = m_sorts.begin(); it != m_sorts.end(); it++)
    {
        liste.push_back(it.key());
    }
    return liste;
}

QStringList Resources::ressources() const
{
    QStringList liste;
    for(QMap<QString, Resource*>::const_iterator it = m_ressources.begin(); it != m_ressources.end(); it++)
    {
        liste.push_back(it.key());
    }
    return liste;
}

QString Resources::classeSuivante(QString const& actuelle)
{
    int num = m_numClasses.indexOf(actuelle);
    num++;
    if(num > m_numClasses.size()-1)
        num = 0;
    return m_numClasses[num];
}

QString Resources::classePrecedente(QString const& actuelle)
{
    int num = m_numClasses.indexOf(actuelle);
    num--;
    if(num < 0)
        num = m_numClasses.size()-1;
    return m_numClasses[num];
}

Resources::~Resources()
{
    for(QMap<QString, Resource*>::iterator it = m_ressources.begin(); it != m_ressources.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, OutfitModel*>::iterator it = m_equipements.begin(); it != m_equipements.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, WeaponModel*>::iterator it = m_armes.begin(); it != m_armes.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, SpellModel*>::iterator it = m_sorts.begin(); it != m_sorts.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, CharacterModel*>::iterator it = m_classes.begin(); it != m_classes.end(); it++)
    {
        delete it.value();
    }
}


