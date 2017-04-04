#ifndef CATEGORIE_H
#define CATEGORIE_H

#include "scenery/object.h"
#include <QMap>

class ObjectGroup
{
public:
    ObjectGroup(QString const& name);
    void ajouteObjet(Object *objet);
    void supprimeObjet(Object *objet);
    QString name() const { return m_name; }
    QMap<qint16, Object*> objets() { return m_objets; }
private:
    QMap<qint16, Object*>m_objets;
    QString m_name;
};

#endif // CATEGORIE_H
