#include "infoJoueur/equipementbase.h"

EquipementBase::EquipementBase(Ressource *ressource, int bonus_force_min, int bonus_force_max, int bonus_vie_min, int bonus_vie_max, int bonus_points_combat_min, int bonus_points_combat_max)
{
    m_ressource = ressource;
    m_bonus_force[0] = bonus_force_min;
    m_bonus_force[1] = bonus_force_max;
    m_bonus_vie[0] = bonus_vie_min;
    m_bonus_vie[1] = bonus_vie_max;
    m_bonus_points_combat[0] = bonus_points_combat_min;
    m_bonus_points_combat[1] = bonus_points_combat_max;
}

EquipementBase* EquipementBase::nouvel(QString const& nom, const QString &chemin)
{
    return new EquipementBase(Ressource::nouvelle(nom, chemin), 0,0,0,0,0,0);
}

QString EquipementBase::description(EquipementBase *equipement)
{
    QString texte;
    if(equipement->getBonusForce(0) < 0)
        texte += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusForce(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusForce(1))+QObject::trUtf8(" force")+"</li>";
    else if(equipement->getBonusForce(1) > 0)
        texte += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusForce(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusForce(1))+QObject::trUtf8(" force")+"</li>";
    if(equipement->getBonusVie(0) < 0)
        texte += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusVie(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusVie(1))+QObject::trUtf8(" vie")+"</li>";
    else if(equipement->getBonusVie(1) > 0)
        texte += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusVie(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusVie(1))+QObject::trUtf8(" vie")+"</li>";
    if(equipement->getBonusPointsCombat(0) < 0)
        texte += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusPointsCombat(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusPointsCombat(1))+QObject::trUtf8(" PC")+"</li>";
    else if(equipement->getBonusPointsCombat(1) > 0)
        texte += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusPointsCombat(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusPointsCombat(1))+QObject::trUtf8(" PC")+"</li>";
    return texte;
}
