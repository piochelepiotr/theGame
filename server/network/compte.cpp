#include "network/compte.h"

Compte::Compte(QString const& donnees, QString const& ndc, Donnees_editeur *donnees_editeur)
{
    m_donnees_editeur = donnees_editeur;
    m_nomDeCompte = ndc;
    QString mot, donnes;
    int i = 1;

    mot = donnees.section('/',0,0);
    m_pseudo = mot;
    mot = "";
    qDebug() << donnees.section('/',i,i);
    while(mot != "END")//houlala pas terrible du tout cette façon de charger c'est moche d'ailleurs il y a déjà eu
        // une boucle infini avec ça !
    {
        mot = donnees.section('/',i,i);
        i++;
        if(mot == "PERSO")
        {
            donnes.clear();
            do
            {
                donnes += mot;
                donnes += '/';
                mot = donnees.section('/',i,i);
                i++;
            }while(mot != "PERSO" && mot != "END");
            m_persos.push_back(new Personnage(donnes, m_donnees_editeur));
            i--;
        }
    }
}

void Compte::save(DataBase *m_db)
{
    QString texte;
    for(int i = 0; i < getNbrPerso(); i++)
    {
        texte+="PERSO/";
        texte += getPerso(i)->enString();
    }
    texte += "END/";
    m_db->savePlayer(m_pseudo,texte);
}

Compte::~Compte()
{
    for(int i =0; i < m_persos.size(); i++)
    {
        delete m_persos[i];
    }
}

void Compte::ajouteUnPerso(Personnage *nouveau)
{
    m_persos.push_back(nouveau);
}

void Compte::supprimme(int i)
{
    delete m_persos[i];
    m_persos.remove(i);
}


