#include "inventory/outfitModel.h"

OutfitModel::OutfitModel(Resource *ressource, int bonus_force_min, int bonus_force_max, int bonus_vie_min, int bonus_vie_max, int bonus_points_fight_min, int bonus_points_fight_max)
{
    m_ressource = ressource;
    m_bonus_force[0] = bonus_force_min;
    m_bonus_force[1] = bonus_force_max;
    m_bonus_vie[0] = bonus_vie_min;
    m_bonus_vie[1] = bonus_vie_max;
    m_bonus_points_fight[0] = bonus_points_fight_min;
    m_bonus_points_fight[1] = bonus_points_fight_max;
}

OutfitModel* OutfitModel::nouvel(QString const& nom, const QString &chemin)
{
    return new OutfitModel(Resource::nouvelle(nom, chemin), 0,0,0,0,0,0);
}

QString OutfitModel::description(OutfitModel *equipement)
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
    if(equipement->getBonusPointsFight(0) < 0)
        texte += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusPointsFight(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusPointsFight(1))+QObject::trUtf8(" PC")+"</li>";
    else if(equipement->getBonusPointsFight(1) > 0)
        texte += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusPointsFight(0))+QObject::trUtf8(" à ")+QString::number(equipement->getBonusPointsFight(1))+QObject::trUtf8(" PC")+"</li>";
    return texte;
}

QString OutfitModel::longue_description()
{
    QString texte = getRessource()->longue_description();
    texte += "<p>Effets : </p>";
    texte += OutfitModel::description(this);
    return texte;
}

Outfit *OutfitModel::genere()
{
    int bonus_force = getBonusForce()+qrand()%(getBonusForce(1)-getBonusForce()+1);
    int bonus_vie = getBonusVie()+qrand()%(getBonusVie(1)-getBonusVie()+1);
    int bonus_points_fight = getBonusPointsFight()+qrand()%(getBonusPointsFight(1)-getBonusPointsFight()+1);
    return new Outfit(getRessource(), bonus_force, bonus_vie, bonus_points_fight);
}
