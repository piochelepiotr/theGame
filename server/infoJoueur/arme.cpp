#include "infoJoueur/arme.h"
#include "infoMonde/lesressources.h"

Arme::Arme(const QString &donnees, LesRessources *ressources)
{
    m_equipement = new Equipement(donnees.section('/',0,3),ressources);
    m_sort = ressources->getSort(donnees.section('/',4,4))->sortNiveau(donnees.section('/',5,5).toInt());
}

Arme::Arme(Equipement *equipement, Sort *sort)
{
    m_equipement = equipement;
    m_sort = sort;
}

Arme::Arme(Arme const& autre)
{
    m_equipement = new Equipement(*autre.getEquipement());
    m_sort = autre.getSort();
}

Arme::~Arme()
{
    delete m_equipement;
}

QString Arme::enString(Armes const& armes)
{
    return QString::number(armes.nbr)+ '/' + enString(armes.arme);
}

QString Arme::enString(Arme *arme)
{
    if(arme)
        return Equipement::enString(arme->getEquipement()) + arme->getSort()->nom() + '/' + QString::number(arme->getSort()->niveau()) + '/';
    return "-1/-1/-1/-1/-1/-1/";
}

Armes Arme::chargeArmes(QString const& donnees,Ressource *ressource, Sort *sort)
{
    Armes armes;
    armes.nbr = donnees.section('/', 0,0).toInt();
    armes.arme = chargeArme(donnees.section('/', 1), ressource, sort);
    return armes;
}

Arme *Arme::chargeArme(QString const& donnees,Ressource *ressource, Sort *sort)
{
    if(donnees.section('/', 0, 0).toInt() == -1)
        return 0;
    return new Arme(Equipement::chargeEquipement(donnees.section('/', 0, 3), ressource), sort);
}

QString Arme::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += getSort()->longue_description();
    return texte;
}

bool operator==(Arme const& a, Arme const& b)
{
    if(a.getSort() != b.getSort())
        return false;
    return *a.getEquipement() == *b.getEquipement();
}
