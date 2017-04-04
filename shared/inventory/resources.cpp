#include "inventory/resources.h"

Resources::Resources()
{
    QStringList liste;
    QString ligne;
    QFile fichier_resources("../data/Ressources/resources.txt");
    QFile fichier_equipements("../data/Ressources/equipements.txt");
    QFile fichier_armes("../data/Ressources/armes.txt");

    QFile fichier_spells(QString(DONNEES)+QString("spells.txt"));
    if(fichier_spells.open(QIODevice::ReadOnly))
    {
        QTextStream stream_spells(&fichier_spells);
        while(!stream_spells.atEnd())
        {
            ligne = stream_spells.readLine();
            if(!ligne.isEmpty())
            {
                m_spells[ligne.section('/', 0, 0)] = new SpellModel(ligne);
            }
        }
        fichier_spells.close();
    }


    if(fichier_resources.open(QIODevice::ReadOnly) && fichier_equipements.open(QIODevice::ReadOnly)&& fichier_armes.open(QIODevice::ReadOnly))
    {
        QTextStream stream_resources(&fichier_resources), stream_equipements(&fichier_equipements), stream_armes(&fichier_armes);

        while(!stream_resources.atEnd())
        {
            ligne = stream_resources.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_resources[liste[0]] = new Resource(liste[0], liste[1].toInt(), liste[2], liste[3].toInt(), liste[4]);
            }
        }

        while(!stream_equipements.atEnd())
        {
            ligne = stream_equipements.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_equipements[liste[0]] = new OutfitModel(m_resources[liste[0]], liste[1].toInt(), liste[2].toInt(), liste[3].toInt(), liste[4].toInt(), liste[5].toInt(), liste[6].toInt());
            }
        }

        while(!stream_armes.atEnd())
        {
            ligne = stream_armes.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                m_armes[liste[0]] = new WeaponModel(m_equipements[liste[0]], m_spells[liste[1]]);
            }
        }

        fichier_resources.close();
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
                m_classes[ligne.section('/', 0, 0)] = new CharacterModel(ligne, m_spells);
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
                m_monstres[ligne.section('/', 0, 0)] = new MonsterModel(ligne, m_spells);
            }
        }
        fichier_monstres.close();
    }
}

void Resources::ajouteRessource(Resource *resource)
{
    m_resources[resource->name()] = resource;
}

void Resources::ajouteEquipement(OutfitModel *equipement)
{
    ajouteRessource(equipement->getRessource());
    m_equipements[equipement->getRessource()->name()] = equipement;
}

void Resources::ajouteArme(WeaponModel *arme)
{
    ajouteEquipement(arme->getEquipement());
    m_armes[arme->getEquipement()->getRessource()->name()] = arme;
}

void Resources::ajouteSpell(SpellModel *spell)
{
    m_spells[spell->name()] = spell;
}

void Resources::enleveRessource(QString const& name)
{
    if(m_resources.contains(name))
    {
        delete m_resources[name];
        m_resources.remove(name);
    }
}

void Resources::enleveEquipement(QString const& name)
{
    if(m_equipements.contains(name))
    {
        delete m_equipements[name];
        m_equipements.remove(name);
    }
}

void Resources::enleveArme(QString const& name)
{
    if(m_armes.contains(name))
    {
        delete m_armes[name];
        m_armes.remove(name);
    }
}

void Resources::enleveSpell(QString const& name)
{
    if(m_spells.contains(name))
    {
        delete m_spells[name];
        m_spells.remove(name);
    }
}

Resource *Resources::getRessource(QString const& name) const
{
    if(name == "-1" || !m_resources.contains(name))
        return 0;
    return m_resources[name];
}

OutfitModel *Resources::getEquipement(QString const& name) const
{
    if(name == "-1" || !m_equipements.contains(name))
        return 0;
    return m_equipements[name];
}

WeaponModel *Resources::getArme(QString const& name) const
{
    if(name == "-1" || !m_armes.contains(name))
        return 0;
    return m_armes[name];
}

SpellModel *Resources::getSpell(const QString &name) const
{
    if(name == "-1" || !m_spells.contains(name))
        return 0;
    return m_spells[name];
}

CharacterModel *Resources::getClasse(QString const& name) const
{
    if(!m_classes.contains(name))
        return 0;
    return m_classes[name];
}

MonsterModel *Resources::getMonstre(QString const& name) const
{
    if(!m_monstres.contains(name))
        return 0;
    return m_monstres[name];
}

EntityModel *Resources::getCreature(QString const& name) const
{
    EntityModel *creature = getMonstre(name);
    if(!creature)
        creature = getClasse(name);
    return creature;
}

QStringList Resources::spells() const
{
    QStringList liste;
    for(QMap<QString, SpellModel*>::const_iterator it = m_spells.begin(); it != m_spells.end(); it++)
    {
        liste.push_back(it.key());
    }
    return liste;
}

QStringList Resources::resources() const
{
    QStringList liste;
    for(QMap<QString, Resource*>::const_iterator it = m_resources.begin(); it != m_resources.end(); it++)
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
    for(QMap<QString, Resource*>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
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
    for(QMap<QString, SpellModel*>::iterator it = m_spells.begin(); it != m_spells.end(); it++)
    {
        delete it.value();
    }
    for(QMap<QString, CharacterModel*>::iterator it = m_classes.begin(); it != m_classes.end(); it++)
    {
        delete it.value();
    }
}


