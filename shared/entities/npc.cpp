#include "entities/npc.h"

bool repliqueFinale(QString const& replique)
{
    if(replique == "quitter" || replique == "metier_bucheron" || replique == "quete")
        return true;
    return false;
}

Dialog::Dialog(QString donnees, QString *reste)
{
    m_reponse = donnees.section('/', 0,0);
    m_replique = donnees.section('/', 1,1);
    *reste = donnees.section('/', 2);
    m_reponses = new Answers(*reste, reste);
}

Dialog::~Dialog()
{
    delete m_reponses;
}

Answers::Answers(QString donnees, QString *reste)
{
    *reste = donnees;
    while(reste->section('/',0,0) != "fin")
    {
        m_pistes.push_back(new Dialog(*reste, reste));
    }
    *reste = reste->section('/', 1);
}

Answers::~Answers()
{
    for(int i = 0; i < m_pistes.size(); i++)
    {
        delete m_pistes[i];
    }
}

NPC::NPC(QString donnes)
{
    QString reste;
    m_name = donnes.section('/', 0,0);
    m_replique = donnes.section('/',1,1);
    m_reponses = new Answers(donnes.section('/', 2), &reste);
}

NPC::~NPC()
{
    delete m_reponses;
}
