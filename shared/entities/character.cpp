#include "character.h"

Personnage::Personnage(const QString &nom, QString classe, Donnees_editeur *donnees_editeur) : Creature(nom,classe,donnees_editeur)///////////////////////////////////juste pour le client
{
    m_met_anneau_gauche = false;
    m_argent = 0;
    m_xp = 0;
    m_cape = 0;
    m_coiffe = 0;
    m_anod = 0;
    m_anog = 0;
    m_amulette = 0;
    m_ceinture = 0;
    m_bottes = 0;
    m_arme = 0;
}



Personnage::Personnage(QString const& donnees, Donnees_editeur *donnees_editeur) : Creature(donnees.section('/',1,1),donnees.section('/',2,2),donnees_editeur)
{
    m_donnees_editeur = donnees_editeur;
    m_met_anneau_gauche = false;
    m_nom = donnees.section('/', 1,1);
    m_classe = donnees.section('/',2,2);
    m_posX = donnees.section('/',3,3).toInt();
    m_posY = donnees.section('/',4,4).toInt();
    m_posZ = donnees.section('/',5,5).toInt();
    m_posmapx = donnees.section('/', 6,6).toInt();
    m_posmapy = donnees.section('/', 7,7).toInt();
    m_vie = donnees.section('/',8,8).toInt();
    m_base_vie = donnees.section('/',9,9).toInt();
    m_base_force = donnees.section('/',10,10).toInt();
    m_base_pc = donnees.section('/',11,11).toInt();
    m_argent = donnees.section('/',12,12).toInt();
    m_xp = donnees.section('/',13,13).toInt();
    metAJourNiveau();
    int i = 14;
    m_cape = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_coiffe = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_anod = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_anog = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_amulette = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_ceinture = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    m_bottes = Equipement::chargeEquipement(donnees.section('/', i, i+3), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)));
    i += 4;
    if(donnees.section('/', i, i) != "-1")
        m_arme = Arme::chargeArme(donnees.section('/', i, i+5), donnees_editeur->ressources->getRessource(donnees.section('/', i, i)), donnees_editeur->ressources->getSort(donnees.section('/', i+4,i+4))->sortNiveau(donnees.section('/', i+5, i+5).toInt()));
    else
        m_arme = 0;
    i += 6;
    //METIERS
    i++;
    while(donnees.section('/',i,i) != "RESSOURCES")
    {
        m_metiers[donnees.section('/', i, i)] = Metier::chargeMetier(donnees.section('/', i, i+1), donnees_editeur->metiers);
        i += 2;
    }
    //RESSOURCES
    i++;
    while(donnees.section('/',i,i) != "OBJETS")
    {
        m_ressources.push_back(Ressource::chargeRess(donnees.section('/', i, i).toInt(), donnees_editeur->ressources->getRessource(donnees.section('/', i+1, i+1))));
        i += 2;
    }
    //OBJETS
    i++;
    while(donnees.section('/',i,i) != "ARMES")
    {
        m_equipements.push_back(Equipement::chargeEquipements(donnees.section('/', i,i+4), donnees_editeur->ressources->getRessource(donnees.section('/', i+1, i+1))));
        i += 5;
    }
    //ARMES
    i++;
    while(donnees.section('/',i,i) != "SORTS")
    {
        m_armes.push_back(Arme::chargeArmes(donnees.section('/', i,i+6), donnees_editeur->ressources->getRessource(donnees.section('/', i+1, i+1)), donnees_editeur->ressources->getSort(donnees.section('/', i+5,i+5))->sortNiveau(donnees.section('/', i+6,i+6).toInt())));
        i += 7;
    }
    i++;
    //SORTS
    while(donnees.section('/',i,i) != "FIN")
    {
        qDebug() << "sort : " << donnees.section('/',i,i) << " niv : "<<donnees.section('/',i+1,i+1);
        m_sorts[donnees.section('/',i,i)] = m_donnees_editeur->ressources->getSort(donnees.section('/',i,i))->sortNiveau(donnees.section('/',i+1,i+1).toInt());
        i += 2;
    }
}

Personnage::~Personnage()
{
    for(int i = 0; i < m_equipements.size(); i++)
    {
        delete m_equipements[i].equipement;
    }
    for(int i = 0; i < m_armes.size(); i++)
    {
        delete m_armes[i].arme;
    }
    for(QMap<QString,Metier*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        delete it.value();
    }
    if(m_cape)
        delete m_cape;
    if(m_coiffe)
        delete m_coiffe;
    if(m_anod)
        delete m_anod;
    if(m_anog)
        delete m_anog;
    if(m_amulette)
        delete m_amulette;
    if(m_ceinture)
        delete m_ceinture;
    if(m_bottes)
        delete m_bottes;
    if(m_arme)
        delete m_arme;
}


QString Personnage::enString() const
{
    QString donnees;//=>>>>>>>>>>>>>>>>    nom/classe/posmondeX/posmondeY/posmondeZ/posmapx/posmapy/vie/base_vie/base_force/base_pc/argent/xp/lvl

    //puis    cape, coiffe, anod, anog, amu, ceinture, botte, arme

    donnees += m_nom + '/';
    donnees += m_classe + '/';
    donnees += QString::number(m_posX) + '/';
    donnees += QString::number(m_posY) + '/';
    donnees += QString::number(m_posZ) + '/';
    donnees += QString::number(m_posmapx) + '/';
    donnees += QString::number(m_posmapy) + '/';
    donnees += QString::number(m_vie) + '/';
    donnees += QString::number(m_base_vie) + '/';
    donnees += QString::number(m_base_force) + '/';
    donnees += QString::number(m_base_pc) + '/';
    donnees += QString::number(m_argent) + '/';
    donnees += QString::number(m_xp) + '/';

    donnees += Equipement::enString(m_cape);
    donnees += Equipement::enString(m_coiffe);
    donnees += Equipement::enString(m_anod);
    donnees += Equipement::enString(m_anog);
    donnees += Equipement::enString(m_amulette);
    donnees += Equipement::enString(m_ceinture);
    donnees += Equipement::enString(m_bottes);
    donnees += Arme::enString(m_arme);
    donnees += "METIERS/";
    for(QMap<QString,Metier*>::const_iterator i = m_metiers.begin(); i != m_metiers.end(); i++)
    {
        donnees += Metier::enString(i.value());
    }
    donnees += "RESSOURCES/";
    for(int i = 0; i < m_ressources.size(); i++)
    {
        donnees += Ressource::enString(m_ressources[i]);
    }
    donnees += "OBJETS/";
    for(int i = 0; i < m_equipements.size(); i++)
    {
        donnees += Equipement::enString(m_equipements[i]);
    }
    donnees += "ARMES/";
    for(int i = 0; i < m_armes.size(); i++)
    {
        donnees += Arme::enString(m_armes[i]);
    }
    donnees += "SORTS/";
    for(QMap<QString,Sort*>::const_iterator it = m_sorts.begin(); it != m_sorts.end(); it++)
    {
           donnees += it.value()->enString();
    }
    donnees += "FIN/";

    return donnees;
}

int Personnage::ajouterRessource(Resss const& resss)
{
    for(int i = 0; i < m_ressources.size(); i++)
    {
        if(m_ressources[i].ress == resss.ress)
        {
            m_ressources[i].nbr += resss.nbr;
            return i;
        }
    }
    m_ressources.push_back(resss);
    return m_ressources.size()-1;
}

void Personnage::enleverRessource(int num, int nbr)
{
    m_ressources[num].nbr -= nbr;
    if(m_ressources[num].nbr < 1)
    {
        m_ressources.remove(num);
    }
}

int Personnage::ajouterEquipement(Eqips const& equipement)
{
    for(int i = 0; i < m_equipements.size(); i++)
    {
        if(*(m_equipements[i].equipement) == *(equipement.equipement))
        {
            delete equipement.equipement;
            m_equipements[i].nbr += equipement.nbr;
            return i;
        }
    }
    m_equipements.push_back(equipement);
    return m_equipements.size()-1;
}

int Personnage::ajouterArme(Armes const& armes)
{
    for(int i = 0; i < m_armes.size(); i++)
    {
        if(*(m_armes[i].arme) == *(armes.arme))
        {
            delete armes.arme;
            m_armes[i].nbr += armes.nbr;
            return i;
        }
    }
    m_armes.push_back(armes);
    return m_armes.size()-1;
}

int Personnage::ajouterArme(Arme *arme)
{
    Armes armes;
    armes.arme = arme;
    armes.nbr = 1;
    return ajouterArme(armes);
}

int Personnage::ajouterEquipement(Equipement *equipement)
{
    Eqips eqips;
    eqips.equipement = equipement;
    eqips.nbr = 1;
    return ajouterEquipement(eqips);
}

int Personnage::ajouterRessource(Ressource *ressource)
{
    Resss ressources;
    ressources.ress = ressource;
    ressources.nbr = 1;
    return ajouterRessource(ressources);
}


void Personnage::enleverEquipement(int num, int nbr)
{
    m_equipements[num].nbr -= nbr;
    if(m_equipements[num].nbr < 1)
    {
        delete m_equipements[num].equipement;
        m_equipements.remove(num);
    }
}

void Personnage::enleverArme(int num, int nbr)
{
    m_armes[num].nbr -= nbr;
    if(m_armes[num].nbr < 1)
    {
        delete m_armes[num].arme;
        m_armes.remove(num);
    }
}

int Personnage::equipeEquipement(int num, const QString &categorie, bool *anneau_gauche)
{
    Eqips vieux_equip;
    vieux_equip.nbr = 1;

    if(categorie == "coiffe")
    {
        vieux_equip.equipement = m_coiffe;
        m_coiffe = new Equipement(*m_equipements[num].equipement);
    }
    else if(categorie == "cape")
    {
        vieux_equip.equipement = m_cape;
        m_cape = new Equipement(*m_equipements[num].equipement);
    }
    else if(categorie == "ceinture")
    {
        vieux_equip.equipement = m_ceinture;
        m_ceinture = new Equipement(*m_equipements[num].equipement);
    }
    else if(categorie == "amulette")
    {
        vieux_equip.equipement = m_amulette;
        m_amulette = new Equipement(*m_equipements[num].equipement);
    }
    else if(categorie == "bottes")
    {
        vieux_equip.equipement = m_bottes;
        m_bottes = new Equipement(*m_equipements[num].equipement);
    }
    else if(categorie == "anneau")
    {
        if(!m_anod)
        {
            m_met_anneau_gauche = false;
        }
        else if(!m_anog)
        {
            m_met_anneau_gauche = true;
        }
        if(m_met_anneau_gauche)
        {
            if(anneau_gauche)
                *anneau_gauche = true;
            vieux_equip.equipement = m_anog;
            m_anog = new Equipement(*m_equipements[num].equipement);
            m_met_anneau_gauche = false;
        }
        else
        {
            if(anneau_gauche)
                *anneau_gauche = false;
            vieux_equip.equipement = m_anod;
            m_anod = new Equipement(*m_equipements[num].equipement);
            m_met_anneau_gauche = true;
        }
    }

    enleverEquipement(num,1);

    if(vieux_equip.equipement)
        return ajouterEquipement(vieux_equip);
    else
        return -2;
}

int Personnage::equipeArme(int num)
{
    Armes vielle_arme;
    vielle_arme.arme = m_arme;
    vielle_arme.nbr = 1;
    m_arme = new Arme(*m_armes[num].arme);
    enleverArme(num,1);

    if(vielle_arme.arme)
        return ajouterArme(vielle_arme);
    else
        return -2;
}

int Personnage::desequipe(int num)
{
    Eqips equipement;
    equipement.nbr = 1;

    if(num == 0)
    {
        equipement.equipement = m_coiffe;
        m_coiffe = 0;
    }
    else if(num == 1)
    {
        equipement.equipement = m_cape;
        m_cape = 0;
    }
    else if(num == 2)
    {
        equipement.equipement = m_anog;
        m_anog = 0;
    }
    else if(num == 3)
    {
        equipement.equipement = m_bottes;
        m_bottes = 0;
    }
    else if(num == 5)
    {
        equipement.equipement = m_amulette;
        m_amulette = 0;
    }
    else if(num == 6)
    {
        equipement.equipement = m_anod;
        m_anod = 0;
    }
    else if(num == 7)
    {
        equipement.equipement = m_ceinture;
        m_ceinture = 0;
    }
    return ajouterEquipement(equipement);
}

int Personnage::desequipeArme()
{
    Armes arme;
    arme.nbr = 1;
    arme.arme = m_arme;
    m_arme = 0;
    return ajouterArme(arme);
}

int Personnage::getBonusVie() const
{
    int bon = 0;
    if(m_cape)
        bon += m_cape->getBonusVie();
    if(m_coiffe)
        bon += m_coiffe->getBonusVie();
    if(m_anod)
        bon += m_anod->getBonusVie();
    if(m_anog)
        bon += m_anog->getBonusVie();
    if(m_amulette)
        bon += m_amulette->getBonusVie();
    if(m_ceinture)
        bon += m_ceinture->getBonusVie();
    if(m_bottes)
        bon += m_bottes->getBonusVie();
    if(m_arme)
        bon += m_arme->getEquipement()->getBonusVie();
    return bon;
}

int Personnage::getBonusForce() const
{
    int bon = 0;
    if(m_cape)
        bon += m_cape->getBonusForce();
    if(m_coiffe)
        bon += m_coiffe->getBonusForce();
    if(m_anod)
        bon += m_anod->getBonusForce();
    if(m_anog)
        bon += m_anog->getBonusForce();
    if(m_amulette)
        bon += m_amulette->getBonusForce();
    if(m_ceinture)
        bon += m_ceinture->getBonusForce();
    if(m_bottes)
        bon += m_bottes->getBonusForce();
    if(m_arme)
        bon += m_arme->getEquipement()->getBonusForce();
    return bon;
}

int Personnage::getBonusPC() const
{
    int bon = 0;
    if(m_cape)
        bon += m_cape->getBonusPointsCombat();
    if(m_coiffe)
        bon += m_coiffe->getBonusPointsCombat();
    if(m_anod)
        bon += m_anod->getBonusPointsCombat();
    if(m_anog)
        bon += m_anog->getBonusPointsCombat();
    if(m_amulette)
        bon += m_amulette->getBonusPointsCombat();
    if(m_ceinture)
        bon += m_ceinture->getBonusPointsCombat();
    if(m_bottes)
        bon += m_bottes->getBonusPointsCombat();
    if(m_arme)
        bon += m_arme->getEquipement()->getBonusPointsCombat();
    return bon;
}

int Personnage::getPods() const
{
    int pods = 0;

    for(int i = 0; i < m_ressources.size(); i++)
    {
        pods += m_ressources[i].ress->pods()*m_ressources[i].nbr;
    }
    for(int i = 0; i < m_equipements.size(); i++)
    {
        pods += m_equipements[i].equipement->getRessource()->pods()*m_equipements[i].nbr;
    }
    for(int i = 0; i < m_armes.size(); i++)
    {
        pods += m_armes[i].arme->getEquipement()->getRessource()->pods()*m_armes[i].nbr;
    }
    if(m_coiffe)
        pods += m_coiffe->getRessource()->pods();
    if(m_cape)
        pods += m_cape->getRessource()->pods();
    if(m_anod)
        pods += m_anod->getRessource()->pods();
    if(m_anog)
        pods += m_anog->getRessource()->pods();
    if(m_amulette)
        pods += m_amulette->getRessource()->pods();
    if(m_ceinture)
        pods += m_ceinture->getRessource()->pods();
    if(m_bottes)
        pods += m_bottes->getRessource()->pods();
    if(m_arme)
        pods += m_arme->getEquipement()->getRessource()->pods();
    return pods;
}

QString Personnage::gagneRessources(Ressource *ressource, int nombre, int *indexDernier)
{
    int place = 0;
    QString texte;
    if(nombre <= 0)
        return texte;
    if(m_donnees_editeur->ressources->estUnEquipement(ressource->nom()))
    {
        if(m_donnees_editeur->ressources->estUneArme(ressource->nom()))
        {
            texte += "a/";
            ArmeBase *arme = m_donnees_editeur->ressources->getArme(ressource->nom());
            Armes armes;
            armes.nbr = 1;
            for(int i = 0; i < nombre; i++)
            {
                armes.arme = arme->genere();
                place = ajouterArme(armes);
                texte += Arme::enString(armenum(place));
            }
        }
        else
        {
            texte += "e/";
            EquipementBase *equipement = m_donnees_editeur->ressources->getEquipement(ressource->nom());
            Eqips equipements;
            equipements.nbr = 1;
            for(int i = 0; i < nombre; i++)
            {
                equipements.equipement = equipement->genere();
                place = ajouterEquipement(equipements);
                texte += Equipement::enString(equipement_num(place));
            }
        }
    }
    else
    {
        texte += "r/";
        Resss ressources;
        ressources.ress = ressource;
        ressources.nbr = nombre;
        ajouterRessource(ressources);
        texte += Ressource::enString(ressources);
    }
    if(indexDernier)
        *indexDernier = place;
    return texte;
}

int Personnage::indexRessource(Ressource *ressource, int *quantite)
{
    int index = 0;
    while(index < m_ressources.size() && m_ressources[index].ress != ressource)
    {
        index++;
    }
    if(m_ressources[index].ress != ressource)
    {
        if(quantite)
            *quantite =0;
        qDebug() << "ERREUR : indexRessource demande pour ressource inexistante";
    }
    else if(quantite)
        *quantite = m_ressources[index].nbr;
    return index;
}

int Personnage::indexEquipement(Equipement *equipement, int *quantite)
{
    int index = 0;
    while(index < m_equipements.size() && m_equipements[index].equipement != equipement)
    {
        index++;
    }
    if(m_equipements[index].equipement != equipement)
    {
        if(quantite)
            *quantite =0;
        qDebug() << "ERREUR : indexEquipement demande pour equipement inexistant";
    }
    else if(quantite)
        *quantite = m_equipements[index].nbr;
    return index;
}

int Personnage::indexArme(Arme *arme, int *quantite)
{
    int index = 0;
    while(index < m_armes.size() && m_armes[index].arme != arme)
    {
        index++;
    }
    if(m_armes[index].arme != arme)
    {
        if(quantite)
            *quantite =0;
        qDebug() << "ERREUR : indexArme demande pour arme inexistante";
    }
    else if(quantite)
        *quantite = m_armes[index].nbr;
    return index;
}

bool Personnage::peutequipe(Equipement *equip)
{
    if(equip->getRessource()->niveau() > m_niveau)
        return false;
    return true;
}

/*QString Personnage::caracteristiques() const
{
    QString caracteristiques;
    caracteristiques += QObject::trUtf8("vie : ")+QString::number(getTotalVie())+ " ("+QString::number(getBaseVie()) + "+" + QString::number(getBonusVie())+ "), ";
    caracteristiques += QObject::trUtf8("force : ") + QString::number(getTotalForce())+ " ("+QString::number(getBaseForce()) + "+" + QString::number(getBonusForce())+"), ";
    caracteristiques += QObject::trUtf8("PC : ") + QString::number(getTotalPC())+ " ("+QString::number(getBasePC()) + "+" + QString::number(getBonusPC())+")";
    return caracteristiques;
}

QString Personnage::important()
{
    QString texte;
    texte += m_nom+'*';
    texte += m_classe+'*';
    texte += QString::number(m_posmapx)+'*';
    texte += QString::number(m_posmapy)+'*';
    return texte;
}*/

void Personnage::apprendMetier(QString nom)
{
    if(!m_metiers.contains(nom))
    {
        m_metiers[nom] = new Metier(m_donnees_editeur->metiers->metier(nom), 0);
    }
}

QStringList Personnage::getMetiers()
{
    QStringList list;
    for(QMap<QString,Metier*>::iterator it = m_metiers.begin(); it != m_metiers.end(); it++)
    {
        list.append(it.key());
    }
    return list;
}

/*void Personnage::setEnCombat(bool enCombat)
{
    if(enCombat)
    {
        m_vie = getTotalVie();
        m_posHorsCombat = QPoint(m_posmapx,m_posmapy);
    }
    else
    {
        m_posmapx = m_posHorsCombat.x();
        m_posmapy = m_posHorsCombat.y();
    }
    m_enCombat = enCombat;
}

void Personnage::perdVie(int degats)
{
    m_vie -= degats;
    if(m_vie < 0)
        m_vie = 0;
}

bool Personnage::peutUtiliserSort(QString const& nom)
{
    return m_pc_combat >= getSort(nom)->points_combat();
}*/

Sort *Personnage::getSort(QString const& nom)
{
    if(nom == "cac")
    {
        if(m_arme)
            return m_arme->getSort();
        else
            return m_donnees_editeur->ressources->getSort("Coup de poing")->sortNiveau(1);
    }
    else if(m_sorts.contains(nom))
    {
        return m_sorts[nom];
    }
    else
    {
        qDebug("SORT DEMANDER N'EXISTE PAS");
        return m_donnees_editeur->ressources->getSort("Coup de poing")->sortNiveau(1);
    }
}

void Personnage::metAJourNiveau()
{
    m_niveau = int(pow((double) m_xp,0.25))+1;
}

void Personnage::gagneXp(int xp)
{
    m_xp += xp;
    metAJourNiveau();
}

QString Personnage::gagneFinCombat(int niveauAutreEquipe,bool victoire)
{
    if(victoire)
    {
        int xpGagne = niveauAutreEquipe*m_niveau;
        gagneXp(xpGagne);
        return m_nom+"/"+QString::number(xpGagne);//le gain est bien ?
    }
    else
    {
        return m_nom+"/"+"0";
    }
}

int Personnage::xpDeNiveau(int niveau)
{
    return pow(niveau-1,4);
}

int Personnage::getPodsMax() const
{
    return NBR_PODS_LVL*m_niveau+BASE_POD;
}
