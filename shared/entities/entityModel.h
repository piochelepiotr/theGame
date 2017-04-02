#ifndef UNECREATURE_H
#define UNECREATURE_H

#include <QString>
#include <QMap>
#include "entities/spellModel.h"

class EntityModel
{
public:
    EntityModel();
    QMap<QString,SpellModel*>getSpells() const { return m_spells; }
    double propX() const { return m_propX; }
    double propY() const { return m_propY; }
    QString getClass() const { return m_class; }
    virtual bool isMonster()const=0;
protected:
    QString m_class;
    QMap<QString,SpellModel*>m_spells;
    double m_propX;
    double m_propY;
};

#endif // UNECREATURE_H
