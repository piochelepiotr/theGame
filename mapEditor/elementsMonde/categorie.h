#ifndef CATEGORIE_H
#define CATEGORIE_H

#include "objet.h"
#include <QMap>



class Categorie
{
public:
    Categorie(QString const& nom);
    void ajouteObjet(Objet *objet);
    void supprimeObjet(Objet *objet);
    QString nom() const { return m_nom; }
    QMap<qint16, Objet*> objets() { return m_objets; }
private:
    QMap<qint16, Objet*>m_objets;
    QString m_nom;
};

#endif // CATEGORIE_H
