#ifndef DECORS_H
#define DECORS_H

#include <QPixmap>
#include <QMap>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QtAlgorithms>
#include <QPushButton>
#include "additionalActions/constantes.h"
#include "objet.h"
#include "categorie.h"
class Decors
{

public:

    Decors(int lcase = 100, int hcase = 50);
    ~Decors();
    void charge();
    Objet *objet(qint16 num) const { return m_objets[num]; }
    Categorie *categorie(QString const& nom) const { return m_categories[nom]; }
    QStringList categories() const;
    int lcase() const { return m_lcase; }
    int hcase() const { return m_hcase; }
    void resize(int lcase, int mcase);
    void ajouteObjet(Objet *objet);
    void supprimeObjet(Objet *objet);
    void ajouteCategorie(QString const& nom);
    QStringList objets() const;
    QMap<QString, Objet*> objetsParNom() const;

private:

    QMap<QString, Categorie*>m_categories;
    QMap<qint16, Objet*>m_objets;
    int m_lcase;
    int m_hcase;

};



#endif // DECORS_H

//stop
