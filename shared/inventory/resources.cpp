#include "inventory/resources.h"

LesRessources::LesRessources()
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
                m_sorts[ligne.section('/', 0, 0)] = new UnSort(ligne);
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
                m_ressources[liste[0]] = new Ressource(liste[0], liste[1].toInt(), liste[2], liste[3].toInt(), liste[4]);
            }
        }

        while(!stream_equipements.atEnd())
        {
            ligne = stream_equipements.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_equipements[liste[0]] = new EquipementBase(m_ressources[liste[0]], liste[1].toInt(), liste[2].toInt(), liste[3].toInt(), liste[4].toInt(), liste[5].toInt(), liste[6].toInt());
            }
        }

        while(!stream_armes.atEnd())
        {
            ligne = stream_armes.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_armes[liste[0]] = new ArmeBase(m_equipements[liste[0]], m_sorts[liste[1]]);
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
                m_classes[ligne.section('/', 0, 0)] = new Classe(ligne, m_sorts);
            }
        }
        fichier_classes.close();
        for(QMap<QString, Classe*>::iterator it = m_classes.begin(); it != m_classes.end(); it++)
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
                m_monstres[ligne.section('/', 0, 0)] = new UnMonstre(ligne, m_sorts);
            }
        }
        fichier_monstres.close();
    }
}

void LesRessources::ajouteRessource(Ressource *ressource)
{
    m_ressources[ressource->nom()] = ressource;
}

void LesRessources::ajouteEquipement(EquipementBase *equipement)
{
    ajouteRessource(equipement->getRessource());
    m_equipements[equipement->getRessource()->nom()] = equipement;
}

void LesRessources::ajouteArme(ArmeBase *arme)
{
    ajouteEquipement(arme->getEquipement());
    m_armes[arme->getEquipement()->getRessource()->nom()] = arme;
}

void LesRessources::ajouteSort(UnSort *sort)
{
    m_sorts[sort->nom()] = sort;
}

void LesRessources::enleveRessource(QString const& nom)
{
    if(m_ressources.contains(nom))
    {
        delete m_ressources[nom];
        m_ressources.remove(nom);
    }
}

void LesRessources::enleveEquipement(QString const& nom)
{
    if(m_equipements.contains(nom))
    {
        delete m_equipements[nom];
        m_equipements.remove(nom);
    }
}

void LesRessources::enleveArme(QString const& nom)
{
    if(m_armes.contains(nom))
    {
        delete m_armes[nom];
        m_armes.remove(nom);
    }
}

void LesRessources::enleveSort(QString const& nom)
{
    if(m_sorts.contains(nom))
    {
        delete m_sorts[nom];
        m_sorts.remove(nom);
    }
}

Ressource *LesRessources::getRessource(QString const& nom) const
{
    if(nom == "-1" || !m_ressources.contains(nom))
        return 0;
    return m_ressources[nom];
}

EquipementBase *LesRessources::getEquipement(QString const& nom) const
{
    if(nom == "-1" || !m_equipements.contains(nom))
        return 0;
    return m_equipements[nom];
}

ArmeBase *LesRessources::getArme(QString const& nom) const
{
    if(nom == "-1" || !m_armes.contains(nom))
        return 0;
    return m_armes[nom];
}

UnSort *LesRessources::getSort(const QString &nom) const
{
    if(nom == "-1" || !m_sorts.contains(nom))
        return 0;
    return m_sorts[nom];
}

Classe *LesRessources::getClasse(QString const& nom) const
{
    if(!m_classes.contains(nom))
        return 0;
    return m_classes[nom];
}

UnMonstre *LesRessources::getMonstre(QString const& nom) const
{
    if(!m_monstres.contains(nom))
        return 0;
    return m_monstres[nom];
}

UneCreature *LesRessources::getCreature(QString const& name) const
{
    UneCreature *creature = getMonstre(name);
    if(!creature)
        creature = getClasse(name);
    return creature;
}

QStringList LesRessources::sorts() const
{
    QStringList liste;
    for(QMap<QString, UnSort*>::const_iterator it = m_sorts.begin(); it != m_sorts.end(); it++)
    {
        liste.push_back(it.key());
    }
    return liste;
}

QStringList LesRessources::ressources() const
{
    QStringList liste;
    for(QMap<QString, Ressource*>::const_iterator it = m_ressources.begin(); it != m_ressources.end(); it++)
    {
        liste.push_back(it.key());
    }
    return liste;
}

QString LesRessources::classeSuivante(QString const& actuelle)
{
    int num = m_numClasses.indexOf(actuelle);
    num++;
    if(num > m_numClasses.size()-1)
        num = 0;
    return m_numClasses[num];
}

QString LesRessources::classePrecedente(QString const& actuelle)
{
    int num = m_numClasses.indexOf(actuelle);
    num--;
    if(num < 0)
        num = m_numClasses.size()-1;
    return m_numClasses[num];
}

LesRessources::~LesRessources()
{
    for(QMap<QString, Ressource*>::iterator it = m_ressources.begin(); it != m_ressources.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, EquipementBase*>::iterator it = m_equipements.begin(); it != m_equipements.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, ArmeBase*>::iterator it = m_armes.begin(); it != m_armes.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, UnSort*>::iterator it = m_sorts.begin(); it != m_sorts.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, Classe*>::iterator it = m_classes.begin(); it != m_classes.end(); it++)
    {
        delete it.value();
    }
}


