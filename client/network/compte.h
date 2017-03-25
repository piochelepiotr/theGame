#ifndef COMPTE_H
#define COMPTE_H

#include <QString>
#include <QVector>
#include "entities/character.h"
#include "inventory/resources.h"
#include "scenery/scenery.h"

class Compte
{

public:

    Compte(QString const& donnees, QString const& ndc, Data *donnees_editeur);
    ~Compte();
    Character* getPerso(int num) const { return m_persos[num]; }
    int getNbrPerso() const { return m_persos.size(); }
    void ajouteUnPerso(Character *nouveau);
    void supprimme(int i);

    QString getPseudo() const { return m_pseudo; }
    QString getNdc() const { return m_nomDeCompte; }

private:

    QVector<Character*>m_persos;
    QString m_pseudo;
    QString m_nomDeCompte;
    Data *m_donnees_editeur;

};

#endif // COMPTE_H
