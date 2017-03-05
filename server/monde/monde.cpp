#include "monde.h"

Monde::Monde(Donnees_editeur *donnees_editeur,Ecran *ecran)
{
    m_ecran = ecran;
    m_donnees_editeur = donnees_editeur;

    for(int i = 0; i < NBR_DE_MAPS_X; i++)
    {
        for(int j = 0; j < NBR_DE_MAPS_Y; j++)
        {
            for(int z = 0; z < NBR_DE_MAPS_Z; z++)
            {
                if(DataMap::exist(i,j,z))
                {
                    Point p(i,j,z);
                    m_maps[p] = new Map(donnees_editeur, this, p,ecran);
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
    for(QMap<Point,Map*>::iterator it = m_maps.begin(); it != m_maps.end(); it++)
    {
        delete it.value();
    }
}

void Monde::connectPlayer(Joueur *player)
{
    m_players[player->getPersoActuel()->getNom()] = player;
    m_maps[player->getPersoActuel()->getPos()]->connectPlayer(player);
}

void Monde::disconnectPlayer(QString const& nom)
{
    Joueur *player = m_players[nom];
    if(player)
    {
        m_maps[player->getPersoActuel()->getPos()]->disconnectPlayer(nom);
        player->changePerso();
        m_players.remove(nom);
    }
}

void Monde::sendMessage(QString const& nom, QString const& message)
{
    m_players[nom]->envoi(message);
}

