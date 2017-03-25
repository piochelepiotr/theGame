#ifndef DECORS_H
#define DECORS_H

#include <QPixmap>
#include <QMap>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QtAlgorithms>
#include <QPushButton>
#include "scenery/constants.h"
#include "scenery/object.h"
#include "scenery/objectGroup.h"
#include "object.h"
#include "qdir.h"

class Scenery
{

public:

    Scenery(int lcase, int hcase, int mapWidth, int mapHeight);
    ~Scenery();
    void charge();
    Object *objet(qint16 num) const { return m_objets[num]; }
    ObjectGroup *categorie(QString const& nom) const { return m_categories[nom]; }
    QStringList categories() const;
    int lcase() const { return m_lcase; }
    int hcase() const { return m_hcase; }
    void resize(int lcase, int mcase, int mapWidth, int mapHeight);
    void ajouteObjet(Object *objet);
    void supprimeObjet(Object *objet);
    void ajouteCategorie(QString const& nom);
    QStringList objets() const;
    QMap<QString, Object*> objetsParNom() const;

private:

    void loadObjects(int mapWidth, int mapHeight);
    QMap<QString, ObjectGroup*>m_categories;
    QMap<qint16, Object*>m_objets;
    int m_lcase;
    int m_hcase;

};



#endif // DECORS_H

//stop
