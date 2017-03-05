#ifndef TOUSLESMETIERS_H
#define TOUSLESMETIERS_H

#include "infoMonde/lesressources.h"
#include "decors.h"
#include "infoMonde/metier_base.h"

class TouslesMetiers
{
public:
    TouslesMetiers(LesRessources *ressources, Decors *decors);
    Metier_Base *metier(QString const& nom) const { return m_metiers[nom]; }
    ~TouslesMetiers();
    QStringList metiers() const { return m_metiers.keys(); }
    Metier_Base *forge_to_metier(Objet *forge);
    bool est_un_objet_coupable(qint16 num) { return m_objets_coupables.contains(num); }
    Metier_Base *objet_coupable_to_metier(Objet *objet);
    Objet *getObjetParSouche(qint16 num) const { return m_souches_to_objets[num]; }
    Objet *getSoucheParObjet(qint16 num) const { return m_objets_to_souches[num]; }

private:
    QMap<QString,Metier_Base*>m_metiers;
    QMap<qint16, Objet*>m_objets_coupables;
    QMap<qint16,Objet*>m_souches_to_objets;
    QMap<qint16,Objet*>m_objets_to_souches;
};
#endif // TOUSLESMETIERS_H
