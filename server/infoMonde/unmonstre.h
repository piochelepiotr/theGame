#ifndef UNMONSTRE_H
#define UNMONSTRE_H

#include <QString>
#include <QMap>
#include "unecreature.h"
#include <QStringList>

class Monstre;
class Donnees_editeur;


class UnMonstre : public UneCreature
{
public:
    UnMonstre(QString const& text, const QMap<QString, UnSort *> &sorts);
    QMap<QString,double>ressourcesDropables() const { return m_ressourcesDropables; }
    Monstre *genereMonstre(int posX, int posY, int posZ, int posMapX, int posMapY, Donnees_editeur *donnees_editeur);

private:
    int m_niveauMin;
    int m_niveauMax;
    int m_vieMin;
    int m_vieMax;
    QMap<QString,double>m_ressourcesDropables;
};

#endif // UNMONSTRE_H
