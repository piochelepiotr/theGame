#include "inventory/weaponModel.h"
#include "inventory/resources.h"

ArmeBase::ArmeBase(EquipementBase *equipementBase, UnSort *sortBase)
{
    m_equipement_base = equipementBase;
    m_sort_base = sortBase;
}

ArmeBase *ArmeBase::nouvelle(QString const& nom, const QString &chemin, LesRessources *ressources)
{
    return new ArmeBase(EquipementBase::nouvel(nom, chemin), ressources->getSort("Coup de poing"));
}

Arme *ArmeBase::genere()
{
    return new Arme(getEquipement()->genere(), getSort()->sortNiveau(0));
}

QString ArmeBase::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += Sort::decrit(getSort()->sortNiveau(0));
    return texte;
}
