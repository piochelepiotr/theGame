#include "infoMonde/persnonj.h"

bool repliqueFinale(QString const& replique)
{
    if(replique == "quitter" || replique == "metier_bucheron" || replique == "quete")
        return true;
    return false;
}

Piste::Piste(QString donnees, QString *reste)
{
    m_reponse = donnees.section('/', 0,0);
    m_replique = donnees.section('/', 1,1);
    *reste = donnees.section('/', 2);
    m_reponses = new Reponses(*reste, reste);
}

Piste::~Piste()
{
    delete m_reponses;
}

Reponses::Reponses(QString donnees, QString *reste)
{
    *reste = donnees;
    while(reste->section('/',0,0) != "fin")
    {
        m_pistes.push_back(new Piste(*reste, reste));
    }
    *reste = reste->section('/', 1);
}

Reponses::~Reponses()
{
    for(int i = 0; i < m_pistes.size(); i++)
    {
        delete m_pistes[i];
    }
}

PersNonJ::PersNonJ(QString donnes)
{
    QString reste;
    m_nom = donnes.section('/', 0,0);
    m_replique = donnes.section('/',1,1);
    m_reponses = new Reponses(donnes.section('/', 2), &reste);
}

PersNonJ::~PersNonJ()
{
    delete m_reponses;
}
