#ifndef UNECREATURE_H
#define UNECREATURE_H

#include <QString>
#include <QMap>
#include "entities/spellModel.h"

class EntityModel
{
public:
    EntityModel();
    QMap<QString,SpellModel*>sorts() const { return m_sorts; }
    double propX() const { return m_propX; }
    double propY() const { return m_propY; }
    QString classe() const { return m_classe; }
protected:
    QString m_classe;
    QMap<QString,SpellModel*>m_sorts;
    double m_propX;
    double m_propY;
};

#endif // UNECREATURE_H
