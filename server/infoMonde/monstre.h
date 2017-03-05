#ifndef MONSTRE_H
#define MONSTRE_H

#include "creature.h"

class LesRessources;

class Monstre : public Creature
{
public:
    Monstre(const QString &nom, QString const& classe, Donnees_editeur *donnees_editeur,int posX,int posY,int posZ,int posMapX,int posMapY,int vie,int niveau);
private:
    QMap<QString,double>m_ressourcesDropables;
};

#endif // MONSTRE_H
