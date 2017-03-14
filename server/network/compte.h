#ifndef COMPTE_H
#define COMPTE_H

#include <QString>
#include <QVector>
#include "entities/character.h"
#include "inventory/resources.h"
#include "scenery/scenery.h"
#include "network/database.h"

class Compte
{

public:

    Compte(QString const& donnees, QString const& ndc, Donnees_editeur *donnees_editeur);
    ~Compte();
    Personnage* getPerso(int num) const { return m_persos[num]; }
    int getNbrPerso() const { return m_persos.size(); }
    void ajouteUnPerso(Personnage *nouveau);
    void supprimme(int i);
    void save(DataBase *m_db);

    QString getPseudo() const { return m_pseudo; }
    QString getNdc() const { return m_nomDeCompte; }

private:

    QVector<Personnage*>m_persos;
    QString m_pseudo;
    QString m_nomDeCompte;
    Donnees_editeur *m_donnees_editeur;

};

#endif // COMPTE_H
