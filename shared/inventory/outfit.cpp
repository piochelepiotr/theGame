#include "inventory/outfit.h"
#include "inventory/resources.h"

Outfit::Outfit(QString const& donnees, Resources *resources)
{
    QStringList liste = donnees.split('/');
    m_resource = resources->getRessource(liste[0]);
    m_bonus_force = liste[1].toInt();
    m_bonus_vie = liste[2].toInt();
    m_bonus_points_fight = liste[3].toInt();
}

Outfit::Outfit(Resource *resource, int bonus_force, int bonus_vie, int bonus_points_fight)
{
    m_resource = resource;
    m_bonus_force = bonus_force;
    m_bonus_vie = bonus_vie;
    m_bonus_points_fight = bonus_points_fight;
}

Outfit::Outfit(Outfit const& autre)
{
    m_resource = autre.m_resource;
    m_bonus_force = autre.m_bonus_force;
    m_bonus_vie = autre.m_bonus_vie;
    m_bonus_points_fight = autre.m_bonus_points_fight;
}

QString Outfit::descr_effet(Outfit *equipement)
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
    if(equipement->getBonusPointsFight() < 0)
        effet += "<li style=\"color:rgb(220,20,20);\" >"+QString::number(equipement->getBonusPointsFight())+QObject::trUtf8(" PC")+"</li>";
    else if(equipement->getBonusPointsFight() > 0)
        effet += "<li style=\"color:rgb(20,220,20);\" >"+QString::number(equipement->getBonusPointsFight())+QObject::trUtf8(" PC")+"</li>";
    return effet;
}

QString Outfit::enString(Eqips const& equipements)
{
    return QString::number(equipements.nbr)+ '/' + enString(equipements.equipement);
}

QString Outfit::enString(Outfit *equipement)
{
    QString texte;
    if(equipement)
    {
        texte += equipement->getRessource()->name() + '/';
        texte += QString::number(equipement->getBonusForce())+'/';
        texte += QString::number(equipement->getBonusVie())+'/';
        texte += QString::number(equipement->getBonusPointsFight())+'/';
    }
    else
    {
        texte = "-1/-1/-1/-1/";
    }
    return texte;
}


Eqips Outfit::chargeEquipements(QString const& donnees,Resource *resource)
{
    Eqips objs;
    objs.nbr = donnees.section('/', 0,0).toInt();
    objs.equipement = chargeEquipement(donnees.section('/', 1), resource);
    return objs;
}

Outfit *Outfit::chargeEquipement(const QString &donnees,Resource *resource)
{
    QStringList liste = donnees.split('/');
    if(liste[0].toInt() == -1)
        return 0;
    return new Outfit(resource, liste[1].toInt(), liste[2].toInt(), liste[3].toInt());
}

QString Outfit::longue_description()
{
    QString texte = getRessource()->longue_description();
    texte += "<p>Effets : </p>";
    texte += Outfit::descr_effet(this);
    return texte;
}

bool operator==(Outfit const& a, Outfit const& b)
{
    if(a.getRessource() != b.getRessource())
        return false;
    if(a.getBonusForce() != b.getBonusForce())
        return false;
    if(a.getBonusVie() != b.getBonusVie())
        return false;
    if(a.getBonusPointsFight() != b.getBonusPointsFight())
        return false;
    return true;
}
