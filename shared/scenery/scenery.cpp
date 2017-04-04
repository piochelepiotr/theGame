#include "scenery/scenery.h"

Scenery::Scenery(int lcase, int hcase,int mapWidth, int mapHeight)
{
    m_lcase = lcase;
    m_hcase = hcase;
    charge();
    loadObjects(mapWidth,mapHeight);
}

void Scenery::loadObjects(int mapWidth, int mapHeight)
{
    /*QDir dir("../data/objects");
    if(!dir.exists())
    {
        qDebug() << "Impossible to open path with objects";
        return;
    }
    QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    foreach(QFileInfo file,files)
    {
        m_objects[file.fileName()] = new Object(file.fileName(),mapWidth,mapHeight);
    }*/
}

void Scenery::charge()
{
    m_objets[0] = new Object();
    Object *obj;
    qint16 num;
    QString categorie, name, ligne;
    QStringList liste;
    double propx, propy;

    QFile fichier_themes("../data/objets/themes.txt");
    if(fichier_themes.open(QIODevice::ReadOnly))
    {
        QTextStream stream_themes(&fichier_themes);
        while(!stream_themes.atEnd())
        {
            ligne = stream_themes.readLine();
            if(!ligne.isEmpty())
            {
                m_categories[ligne] = new ObjectGroup(ligne);
            }
        }
        fichier_themes.close();
    }
    QFile fichier_objets("../data/objets/objets.txt");
    if(fichier_objets.open(QIODevice::ReadOnly))
    {
        QTextStream stream_objets(&fichier_objets);

        while(!stream_objets.atEnd())
        {
            ligne = stream_objets.readLine();
            if(!ligne.isEmpty())
            {
                liste = ligne.split('/');
                num = liste[0].toInt();
                name = liste[1];
                categorie = liste[2];
                propx = liste[3].toDouble();
                propy = liste[4].toDouble();
                obj = new Object(num, name, categorie, propx, propy, m_lcase, m_hcase);
                m_objets[num] = obj;
                if(m_categories.contains(categorie))
                    m_categories[categorie]->ajouteObjet(obj);
            }
        }

        fichier_objets.close();
    }
}

QStringList Scenery::categories() const
{
    QStringList liste;
    for(QMap<QString, ObjectGroup*>::const_iterator it = m_categories.begin(); it != m_categories.end(); it++)
    {
        liste.push_back(it.value()->name());
    }
    return liste;
}

Scenery::~Scenery()
{
    for(QMap<QString, ObjectGroup*>::iterator it = m_categories.begin(); it != m_categories.end(); it++)
    {
        delete it.value();
    }
    for(QMap<qint16, Object*>::iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        delete it.value();
    }
}

void Scenery::resize(int lcase, int hcase,int mapWidth, int mapHeight)
{
    m_lcase = lcase;
    m_hcase  = hcase;
    for(auto it : m_objets)
    {
        it->resize(lcase, hcase);
    }
    /*for(auto it : m_objects)
    {
        it->resize(mapWidth,mapHeight);
    }*/
}

void Scenery::ajouteObjet(Object *objet)
{
    m_categories[objet->categorie()]->ajouteObjet(objet);
    m_objets[objet->numero()] = objet;
}

void Scenery::supprimeObjet(Object *objet)
{
    m_categories[objet->categorie()]->supprimeObjet(objet);
    delete m_objets[objet->numero()];
    m_objets.remove(objet->numero());
}

void Scenery::ajouteCategorie(QString const& name)
{
    m_categories[name] = new ObjectGroup(name);
}

QMap<QString, Object*> Scenery::objetsParNom() const
{
    QMap<QString, Object*>objs;
    for(QMap<qint16, Object*>::const_iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        if(it.value()->categorie() != "pnj" && !it.value()->name().isEmpty())
            objs[it.value()->name()] = it.value();
    }
    return objs;
}

QStringList Scenery::objets() const
{
    QStringList liste;
    for(QMap<qint16, Object*>::const_iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        if(it.value()->categorie() != "pnj" && !it.value()->name().isEmpty())
            liste.push_back(it.value()->name());
    }
    qSort(liste.begin(), liste.end());
    return liste;
}




//stop
