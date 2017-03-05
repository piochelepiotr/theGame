#include "decors.h"

Decors::Decors(int lcase, int hcase)
{
    m_lcase = lcase;
    m_hcase = hcase;
    charge();
}

void Decors::charge()
{
    m_objets[0] = new Objet();
    Objet *obj;
    qint16 num;
    QString categorie, nom, ligne;
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
                m_categories[ligne] = new Categorie(ligne);
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
                nom = liste[1];
                categorie = liste[2];
                propx = liste[3].toDouble();
                propy = liste[4].toDouble();
                obj = new Objet(num, nom, categorie, propx, propy, m_lcase, m_hcase);
                m_objets[num] = obj;
                if(m_categories.contains(categorie))
                    m_categories[categorie]->ajouteObjet(obj);
            }
        }

        fichier_objets.close();
    }
}

QStringList Decors::categories() const
{
    QStringList liste;
    for(QMap<QString, Categorie*>::const_iterator it = m_categories.begin(); it != m_categories.end(); it++)
    {
        liste.push_back(it.value()->nom());
    }
    return liste;
}

Decors::~Decors()
{
    for(QMap<QString, Categorie*>::iterator it = m_categories.begin(); it != m_categories.end(); it++)
    {
        delete it.value();
    }
    for(QMap<qint16, Objet*>::iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        delete it.value();
    }
}

void Decors::resize(int lcase, int hcase)
{
    m_lcase = lcase;
    m_hcase  = hcase;
    for(QMap<qint16, Objet*>::iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        it.value()->resize(lcase, hcase);
    }
}

void Decors::ajouteObjet(Objet *objet)
{
    m_categories[objet->categorie()]->ajouteObjet(objet);
    m_objets[objet->numero()] = objet;
}

void Decors::supprimeObjet(Objet *objet)
{
    m_categories[objet->categorie()]->supprimeObjet(objet);
    delete m_objets[objet->numero()];
    m_objets.remove(objet->numero());
}

void Decors::ajouteCategorie(QString const& nom)
{
    m_categories[nom] = new Categorie(nom);
}

QMap<QString, Objet*> Decors::objetsParNom() const
{
    QMap<QString, Objet*>objs;
    for(QMap<qint16, Objet*>::const_iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        if(it.value()->categorie() != "pnj" && !it.value()->nom().isEmpty())
            objs[it.value()->nom()] = it.value();
    }
    return objs;
}

QStringList Decors::objets() const
{
    QStringList liste;
    for(QMap<qint16, Objet*>::const_iterator it = m_objets.begin(); it != m_objets.end(); it++)
    {
        if(it.value()->categorie() != "pnj" && !it.value()->nom().isEmpty())
            liste.push_back(it.value()->nom());
    }
    qSort(liste.begin(), liste.end());
    return liste;
}




//stop
