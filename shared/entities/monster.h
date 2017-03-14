#ifndef MONSTRE_H
#define MONSTRE_H

#include "entities/entity.h"

class Donnees_editeur;

class Monstre : public Creature
{
public:
    Monstre(const QString &nom,const QString &classe, Donnees_editeur *donnees_editeur,int posX,int posY,int posZ,int posMapX,int posMapY,int vie,int niveau);
private:
    QMap<QString,double>m_ressourcesDropables;
};

#endif // MONSTRE_H
