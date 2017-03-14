#ifndef METIER_BASE_H
#define METIER_BASE_H

#include <QString>
#include "inventory/resource.h"
#include "elementsMonde/objet_coupable.h"
#include "infoMonde/recette.h"

#define METIER_NBR_CASES_DEPART 1
#define METIER_LVLS_1CASEENPLUS 15
#define COUPS_DEPART 16
#define METIER_LVLS_1COUPSENMOINS 10
#define METIER_NBR_LVLS 150
#define METIER_BONUS_LVL_MAX 8
#define METIER_LVL_MAX 150

class LesRessources;
class Decors;

class Metier_Base
{
public:
    Metier_Base(QString const& donnees, Decors *decors, LesRessources *ressources);
    ~Metier_Base();
    QString nom() const { return m_nom; }
    QVector<qint16> ressources_coupables(int lvl);
    Objet_coupable *objet_coupable(qint16 num) const { return m_objets_coupables[num]; }
    QString arme() const { return m_arme; }
    QString verbe() const { return m_verbe; }
    QString raccourci() const { return m_raccourci; }
    QString verbe_recettes() const { return m_verbe_recettes; }
    QStringList recettes() const { return m_recettes.keys(); }
    Recette *recette(QString const& nom) const { return m_recettes[nom]; }
    Objet *objet_recette() const { return m_objet_recettes; }
    QMap<qint16,Objet*> objets_coupables() const;
    QMap<qint16, Objet_coupable*>get_objets_coupables() const { return m_objets_coupables; }
    bool coupe(qint16 num) const { return m_objets_coupables.contains(num); }
private:
    QString m_verbe_recettes;
    QString m_arme;
    QString m_verbe;
    QString m_nom;
    QString m_raccourci;
    Objet *m_objet_recettes;
    QMap<qint16,Objet_coupable*>m_objets_coupables;
    QMap<QString,Recette*>m_recettes;
};

#endif // METIER_BASE_H
