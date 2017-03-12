#include "infoJoueur/equipement.h"
#include "infoMonde/lesressources.h"

Equipement::Equipement(QString const& donnees, LesRessources *ressources)
{
    QStringList liste = donnees.split('/');
    m_ressource = ressources->getRessource(liste[0]);
    m_bonus_force = liste[1].toInt();
    m_bonus_vie = liste[2].toInt();
    m_bonus_points_combat = liste[3].toInt();
}

Equipement::Equipement(Ressource *ressource, int bonus_force, int bonus_vie, int bonus_points_combat)
{
    m_ressource = ressource;
    m_bonus_force = bonus_force;
    m_bonus_vie = bonus_vie;
    m_bonus_points_combat = bonus_points_combat;
}

Equipement::Equipement(Equipement const& autre)
{
    m_ressource = autre.m_ressource;
    m_bonus_force = autre.m_bonus_force;
    m_bonus_vie = autre.m_bonus_vie;
    m_bonus_points_combat = autre.m_bonus_points_combat;
}

QString Equipement::descr_effet(Equipement *equipement)
{
    QString effet;
    if(equipement->getBonusForce() < 0)
        effet += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusForce())+QObject::trUtf8(" force")+"</li>";
    else if(equipement->getBonusForce() > 0)
        effet += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusForce())+QObject::trUtf8(" force")+"</li>";
    if(equipement->getBonusVie() < 0)
        effet += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusVie())+QObject::trUtf8(" vie")+"</li>";
    else if(equipement->getBonusVie() > 0)
        effet += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusVie())+QObject::trUtf8(" vie")+"</li>";
    if(equipement->getBonusPointsCombat() < 0)
        effet += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusPointsCombat())+QObject::trUtf8(" PC")+"</li>";
    else if(equipement->getBonusPointsCombat() > 0)
        effet += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusPointsCombat())+QObject::trUtf8(" PC")+"</li>";
    return effet;
}

QString Equipement::enString(Eqips const& equipements)
{
    return QString::number(equipements.nbr)+ '/' + enString(equipements.equipement);
}

QString Equipement::enString(Equipement *equipement)
{
    QString texte;
    if(equipement)
    {
        texte += equipement->getRessource()->nom() + '/';
        texte += QString::number(equipement->getBonusForce())+'/';
        texte += QString::number(equipement->getBonusVie())+'/';
        texte += QString::number(equipement->getBonusPointsCombat())+'/';
    }
    else
    {
        texte = "-1/-1/-1/-1/";
    }
    return texte;
}


Eqips Equipement::chargeEquipements(QString const& donnees,Ressource *ressource)
{
    Eqips objs;
    objs.nbr = donnees.section('/', 0,0).toInt();
    objs.equipement = chargeEquipement(donnees.section('/', 1), ressource);
    return objs;
}

Equipement *Equipement::chargeEquipement(const QString &donnees,Ressource *ressource)
{
    QStringList liste = donnees.split('/');
    if(liste[0].toInt() == -1)
        return 0;
    return new Equipement(ressource, liste[1].toInt(), liste[2].toInt(), liste[3].toInt());
}

QString Equipement::longue_description()
{
    QString texte = getRessource()->longue_description();
    texte += "<p>Effets : </p>";
    texte += Equipement::descr_effet(this);
    return texte;
}

bool operator==(Equipement const& a, Equipement const& b)
{
    if(a.getRessource() != b.getRessource())
        return false;
    if(a.getBonusForce() != b.getBonusForce())
        return false;
    if(a.getBonusVie() != b.getBonusVie())
        return false;
    if(a.getBonusPointsCombat() != b.getBonusPointsCombat())
        return false;
    return true;
}
