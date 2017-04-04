#include "network/compte.h"

Compte::Compte(QString const& donnees, QString const& ndc, Data *donnees_editeur)
{
    m_donnees_editeur = donnees_editeur;
    m_nameDeCompte = ndc;
    QString mot, donnes;
    int i = 1;

    mot = donnees.section('/',0,0);
    m_pseudo = mot;

    while(mot != "END")
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
            m_persos.push_back(new Character(donnes, m_donnees_editeur));
            i--;
        }
    }
}

Compte::~Compte()
{
    for(int i =0; i < m_persos.size(); i++)
    {
        delete m_persos[i];
    }
}

void Compte::ajouteUnPerso(Character *nouveau)
{
    m_persos.push_back(nouveau);
}

void Compte::supprimme(int i)
{
    delete m_persos[i];
    m_persos.remove(i);
}


