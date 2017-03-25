#ifndef UNMONSTRE_H
#define UNMONSTRE_H

#include <QString>
#include <QMap>
#include "entities/entityModel.h"
#include <QStringList>

class Monster;
class Data;


class MonsterModel : public EntityModel
{
public:
    MonsterModel(QString const& text, const QMap<QString, SpellModel *> &sorts);
    QMap<QString,double>ressourcesDropables() const { return m_ressourcesDropables; }
    Monster *genereMonstre(int posX, int posY, int posZ, int posMapX, int posMapY, Data *donnees_editeur, const QString &name);

private:
    int m_niveauMin;
    int m_niveauMax;
    int m_vieMin;
    int m_vieMax;
    QMap<QString,double>m_ressourcesDropables;
};

#endif // UNMONSTRE_H
