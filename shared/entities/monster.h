#ifndef MONSTRE_H
#define MONSTRE_H

#include "entities/entity.h"

class Data;

class Monster : public Entity
{
public:
    Monster(const QString &nom,const QString &classe, Data *donnees_editeur,int posX,int posY,int posZ,int posMapX,int posMapY,int vie,int niveau);
private:
    QMap<QString,double>m_ressourcesDropables;
};

#endif // MONSTRE_H
