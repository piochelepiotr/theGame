#include "monde.h"

Monde::Monde(Data *donnees_editeur,Ecran *ecran)
{
    m_ecran = ecran;
    m_donnees_editeur = donnees_editeur;

    for(int i = 0; i < NBR_DE_MAPS_X; i++)
    {
        for(int j = 0; j < NBR_DE_MAPS_Y; j++)
        {
            for(int z = 0; z < NBR_DE_MAPS_Z; z++)
            {
                if(Map::exist(i,j,z))
                {
                    Point p(i,j,z);
                    m_maps[p] = new ServerMap(donnees_editeur, this, p,ecran);
                }
            }
        }
    }
}

/*void Monde::envoie(QString qui,QString message)
{
    emit s_envoie(qui,message);
}*/

Monde::~Monde()
{
    for(auto it : m_maps)
    {
        delete it;
    }
}

void Monde::connectPlayer(Joueur *player)
{
    m_players[player->getPersoActuel()->getNom()] = player;
    m_maps[player->getPersoActuel()->getPos()]->connectPlayer(player);
}

void Monde::disconnectPlayer(QString const& name)
{
    Joueur *player = m_players[name];
    if(player)
    {
        m_maps[player->getPersoActuel()->getPos()]->disconnectPlayer(name);
        player->changePerso();
        m_players.remove(name);
    }
}

void Monde::sendMessage(QString const& name, QString const& message)
{
    m_players[name]->envoi(message);
}

