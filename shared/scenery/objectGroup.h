#ifndef CATEGORIE_H
#define CATEGORIE_H

#include "scenery/object.h"
#include <QMap>

class ObjectGroup
{
public:
    ObjectGroup(QString const& nom);
    void ajouteObjet(Object *objet);
    void supprimeObjet(Object *objet);
    QString nom() const { return m_nom; }
    QMap<qint16, Object*> objets() { return m_objets; }
private:
    QMap<qint16, Object*>m_objets;
    QString m_nom;
};

#endif // CATEGORIE_H
