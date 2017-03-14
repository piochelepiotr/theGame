#ifndef TOUSLESMETIERS_H
#define TOUSLESMETIERS_H

#include "inventory/resources.h"
#include "scenery/scenery.h"
#include "jobs/jobModel.h"

class TouslesMetiers
{
public:
    TouslesMetiers(LesRessources *ressources, Decors *decors);
    Metier_Base *metier(QString const& nom) const { return m_metiers[nom]; }
    ~TouslesMetiers();
    QStringList metiers() const { return m_metiers.keys(); }
    Metier_Base *forge_to_metier(Objet *forge);
    bool est_un_objet_coupable(qint16 num) { return m_objets_coupables.contains(num); }
    bool est_un_objet_coupe(qint16 num) { return m_souches_to_objets.contains(num); }
    Metier_Base *objet_coupable_to_metier(Objet *objet);
    Objet *getObjetParSouche(qint16 num) const;
    Objet *getSoucheParObjet(qint16 num) const;

private:
    QMap<QString,Metier_Base*>m_metiers;
    QMap<qint16, Objet*>m_objets_coupables;
    QMap<qint16,Objet*>m_souches_to_objets;
    QMap<qint16,Objet*>m_objets_to_souches;
};
#endif // TOUSLESMETIERS_H
