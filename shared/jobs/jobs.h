#ifndef TOUSLESMETIERS_H
#define TOUSLESMETIERS_H

#include "inventory/resources.h"
#include "scenery/scenery.h"
#include "jobs/jobModel.h"

class Jobs
{
public:
    Jobs(Resources *resources, Scenery *decors);
    JobModel *metier(QString const& nom) const { return m_metiers[nom]; }
    ~Jobs();
    QStringList metiers() const { return m_metiers.keys(); }
    JobModel *forge_to_metier(Object *forge);
    bool est_un_objet_coupable(qint16 num) { return m_objets_coupables.contains(num); }
    bool est_un_objet_coupe(qint16 num) { return m_souches_to_objets.contains(num); }
    JobModel *objet_coupable_to_metier(Object *objet);
    Object *getObjetParSouche(qint16 num) const;
    Object *getSoucheParObjet(qint16 num) const;

private:
    QMap<QString,JobModel*>m_metiers;
    QMap<qint16, Object*>m_objets_coupables;
    QMap<qint16,Object*>m_souches_to_objets;
    QMap<qint16,Object*>m_objets_to_souches;
};
#endif // TOUSLESMETIERS_H
