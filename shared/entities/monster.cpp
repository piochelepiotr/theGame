#include "entities/monster.h"
#include "scenery/data.h"

Monstre::Monstre(const QString &nom, const QString &classe, Donnees_editeur *donnees_editeur,int posX,int posY,int posZ,int posMapX,int posMapY,int vie,int niveau) : Creature(nom,classe,donnees_editeur)
{
    m_posX = posX;
    m_posY = posY;
    m_posZ = posZ;
    m_posmapx = posMapX;
    m_posmapy = posMapY;
    m_base_vie = vie;
    m_niveau = niveau;
    m_ressourcesDropables = donnees_editeur->ressources->getMonstre(classe)->ressourcesDropables();
}
