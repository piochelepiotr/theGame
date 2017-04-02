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
    MonsterModel(QString const& text, const QMap<QString, SpellModel *> &getSpells);
    QMap<QString,double>ressourcesDropables() const { return m_ressourcesDropables; }
    Monster *generateMonster(int posX, int posY, int posZ, int posMapX, int posMapY, Data *donnees_editeur, const QString &name);
    virtual bool isMonster() const { return true; }

private:
    int m_levelMin;
    int m_levelMax;
    int m_lifeMin;
    int m_lifeMax;
    QMap<QString,double>m_ressourcesDropables;
};

#endif // UNMONSTRE_H
