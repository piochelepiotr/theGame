#ifndef UNECREATURE_H
#define UNECREATURE_H

#include <QString>
#include <QMap>
#include "infoMonde/unsort.h"

class UneCreature
{
public:
    UneCreature();
    QMap<QString,UnSort*>sorts() const { return m_sorts; }
    double propX() const { return m_propX; }
    double propY() const { return m_propY; }
    QString classe() const { return m_classe; }
protected:
    QString m_classe;
    QMap<QString,UnSort*>m_sorts;
    double m_propX;
    double m_propY;
};

#endif // UNECREATURE_H
