#include "map.h"
#include "graphic/ecran.h"
#include "monde/monde.h"

Map::Map(Donnees_editeur *donnees_editeur, Monde *parent, Point const& pos,Ecran *ecran)
{
    m_donnees_editeur = donnees_editeur;
    m_ecran = ecran;
    m_pos = pos;
    m_dataMap = new DataMap(donnees_editeur,pos.x,pos.y,pos.z);
    m_parent = parent;
    m_dataMap->coupable(&m_objets_coupables);
    m_aide_timers = new QSignalMapper(this);
    for(int  i = 0; i < NBR_MONSTRES_MAP;i++)
    {
        addMonstre();
    }
    connect(m_aide_timers, SIGNAL(mapped(int)), this, SLOT(repousse(int)));
}

void Map::addMonstre()
{
    UnMonstre *monstre = m_dataMap->nouveauMonstre();
    if(monstre)
    {
        QString nom = nomMonstre(monstre->classe());
        QPoint p = m_dataMap->caseLibre();
        m_monstres[nom] = monstre->genereMonstre(m_dataMap->x(),m_dataMap->y(),m_dataMap->z(),p.x(),p.y(),m_donnees_editeur);
    }
}

QString Map::nomMonstre(QString const& nomClasse)
{
    for(int i = 0; i < NBR_MONSTRES_MAP*2+2;i++)//*2+2 pour être sûr qu'on trouvera un i
    {
        QString nom = nomClasse+"_"+QString::number(i);
        if(!m_monstres.contains(nom))
        {
            return nom;
        }
    }
    qDebug() << "Pas de nom pour monstre trouvé !!";
    exit(1);
    return "";
}

QString Map::ressources_coupees() const
{
    QString ressources;
    for(QMap<QPoint, bool>::const_iterator it = m_objets_coupables.begin(); it != m_objets_coupables.end(); it++)
    {
        if(!it.value())
        {
            ressources += QString::number(it.key().x()).rightJustified(2, '0');
            ressources += QString::number(it.key().y()).rightJustified(2, '0');
        }
    }
    return ressources;
}

void Map::coupe(QPoint p)
{
    int pos = p.x()*1000+p.y();
    m_objets_coupables[p] = false;

    int interval = TEMPS_MIN_REPOUSSE+qrand()%(TEMPS_MAX_REPOUSSE-TEMPS_MIN_REPOUSSE);

    if(!m_timers.contains(p))
    {
        m_timers[p] = new QTimer(this);
        m_timers[p]->setInterval(interval);
        m_timers[p]->setSingleShot(true);
        connect(m_timers[p], SIGNAL(timeout()), m_aide_timers, SLOT(map()));
    }
    else
        m_aide_timers->removeMappings(m_timers[p]);
    m_aide_timers->setMapping(m_timers[p], pos);
    m_timers[p]->start();
}

void Map::repousse(int pos)
{
    QPoint p(pos/1000, pos%1000);
    m_objets_coupables[p] = true;
    envoiGroupe(joueursPasEnCombat(), "rep/"+QString::number(p.x())+'*'+QString::number(p.y()));
}

void Map::addCombat(Personnage *leader1, Personnage *leader2)
{
    m_combats[leader1->getNom()] = new Combat(leader1,leader2,m_dataMap);
    connect(m_combats[leader1->getNom()],SIGNAL(envoie(QString,QString)), this,SLOT(sendToPlayer(QString,QString)));
    connect(m_combats[leader1->getNom()],SIGNAL(decoCombattants(QString)),this,SLOT(decoCombattants(QString)));
    connect(m_combats[leader1->getNom()],SIGNAL(s_finCombat(QString)),this,SLOT(finCombat(QString)));
}

void Map::sendToPlayer(QString const& name,QString const& message)
{
    m_joueurs[name]->envoi(message);
}

void Map::decoCombattants(QString nomCombat)
{
    QStringList noms = combat(nomCombat)->combattants();
    int longueur = noms.length();
    QList<Joueur*>joueurs = joueursPasEnCombat();
    for(int j = 0; j < joueurs.size(); j++)
    {
        for(int i = 0; i < longueur; i++)
        {
            joueurs.at(j)->envoi("dec/"+noms[i]);
            m_joueurs[noms[i]]->envoi("dec/"+joueurs.at(j)->getPersoActuel()->getNom());
        }
    }
}

void Map::recoCombattants(QString nomCombat)
{
    QStringList noms = combat(nomCombat)->combattants();
    QList<Joueur*>joueurs = joueursPasEnCombat();
    int l = noms.length();
    Personnage *pers = 0;
    for(int i = 0; i < l;i++)
    {
        pers = combat(nomCombat)->getPersonnage(noms[i]);
        pers->setEnCombat(false);
        envoieA(combat(nomCombat)->combattants(),"changePos/"+pers->getNom()+"/"+QString::number(pers->getPosMap().x())+"/"+QString::number(pers->getPosMap().y()));
    }
    for(int j = 0; j < joueurs.size(); j++)
    {
        for(int i = 0; i < l; i++)
        {
            joueurs.at(j)->envoi("con/"+combat(nomCombat)->getPersonnage(noms[i])->important());
            m_joueurs[noms[i]]->envoi("con/"+joueurs.at(j)->getPersoActuel()->important());
        }
    }
}

void Map::finCombat(QString nom)
{
    if(m_combats[nom]->phase() == EnDemande)
    {

    }
    else if(m_combats[nom]->phase() == EnPlacement)
    {
        QString texte = m_combats[nom]->gainsFin();
        envoieA(combat(nom)->combattants(), "finCombat/"+texte);
        recoCombattants(nom);
    }
    else if(m_combats[nom]->phase() == EnCombat)
    {
        QString texte = m_combats[nom]->gainsFin();
        envoieA(combat(nom)->combattants(), "finCombat/"+texte);
        recoCombattants(nom);
    }
    disconnect(m_combats[nom]);
    m_combats[nom]->setPhase(CombatFini);
    delete m_combats[nom];
    m_combats.remove(nom);
}

void Map::finCombatAvantDebut(QString nom)
{
    disconnect(m_combats[nom]);
    delete m_combats[nom];
    m_combats.remove(nom);
}

Combat *Map::combat(QString nom)
{
    return m_combats[nom];
}

QString Map::leaderDe(QString nom)
{
    for(QMap<QString,Combat*>::iterator it = m_combats.begin(); it != m_combats.end(); it++)
    {
        if(it.value()->contains(nom))
        {
            return it.key();
        }
    }
    qDebug() << "AUCUN LEADER TROUVE";
    return "";
}

Map::~Map()
{
    delete m_dataMap;
    for(QMap<QString,Combat*>::iterator it = m_combats.begin(); it != m_combats.end(); it++)
    {
        delete it.value();
    }
}

void Map::joueurChangePosDepart(QString nom, int x, int y)
{
    QString leader = leaderDe(nom);
    if(m_dataMap->estCaseDeDepart(x,y,m_combats[leader]->getPersonnage(nom)->equipe()))
    {
        if(m_combats[leader]->personneSur(x,y))
        {
            qDebug() << "on deplace";
            m_combats[leader]->deplace(nom,x,y);
        }
    }
}

void Map::enEquipe(QString const& nom)
{
    int equipe1 = qrand()%2;
    qDebug() << equipe1;
    QPoint pos1 = m_dataMap->posDep(equipe1);
    QPoint pos2 = m_dataMap->posDep(1-equipe1);
    m_combats[nom]->enEquipe(equipe1,1-equipe1,pos1,pos2);
}

void Map::envoieA(QStringList noms,QString message)
{
    for(int i = 0; i < noms.length(); i++)
    {
        m_joueurs[noms[i]]->envoi(message);
    }
}

void Map::connectPlayer(Joueur *joueur,bool hasJustChangedMap)
{
    if(!hasJustChangedMap)
        joueur->joue();
    QList<Joueur*>pasEnCombat = joueursPasEnCombat();
    QString message = "ttt/"+ressources_coupees()+'/';
    for(int i = 0; i < pasEnCombat.size(); i++)
    {
        message += pasEnCombat[i]->getPersoActuel()->important()+'/';
    }
    joueur->envoi(message);
    m_joueurs[joueur->getPersoActuel()->getNom()] = joueur;
    envoiGroupe(pasEnCombat, "con/"+joueur->getPersoActuel()->important());
}

void Map::disconnectPlayer(QString const& nom)
{
    qDebug() << "disconnect player";
    Personnage *pers = m_joueurs[nom]->getPersoActuel();
    m_joueurs.remove(nom);
    if(pers->enCombat())
    {
        Combat *figth = combat(leaderDe(nom));
        figth->enlevePerso(nom);
    }
    else
    {
        envoiGroupe(joueursPasEnCombat(), "dec/"+nom);
    }
}

QList<Joueur*> Map::joueursPasEnCombat()
{
    QList<Joueur*>joueursPasEnCombat;
    for(QMap<QString,Joueur*>::iterator it = m_joueurs.begin(); it != m_joueurs.end(); it++)
    {
        if(!it.value()->getPersoActuel()->enCombat())
            joueursPasEnCombat.append(it.value());
    }
    return joueursPasEnCombat;
}

void envoiGroupe(QList<Joueur*> const& receveurs, QString const& message, const QString &nom)
{
    for(QList<Joueur*>::const_iterator it = receveurs.begin(); it != receveurs.end(); it++)
    {
        if((*it)->getPersoActuel()->getNom() != nom)
            (*it)->envoi(message);
    }
}

void Map::receiveMessage(Joueur *player, QString const& begin, QString const& message)
{
    if(begin == "dec")
    {
        m_ecran->enleveJeu(player);
        m_ecran->enleveChoixPerso(player);
    }
    else if(begin == "cdp")
    {
        m_ecran->enleveJeu(player);
    }
    else if(begin == "cha")
    {
        envoiGroupe(joueursPasEnCombat(),message);
    }
    else if(begin == "dep")
    {
        player->getPersoActuel()->setPosMap(message.section('*',1,1).toInt(), message.section('*',2,2).toInt());
        envoiGroupe(joueursPasEnCombat(), message, player->getPersoActuel()->getNom());
    }
    else if(begin == "cut")//recolte d'une ressource
    {
        envoiGroupe(joueursPasEnCombat(), message, player->getPersoActuel()->getNom());
    }
    else if(begin == "cop")//ressource coupee
    {
        coupe(QPoint(message.section('/', 0, 0).section('*', 0, 0).toInt(), message.section('/', 0, 0).section('*', 1, 1).toInt()));
        QStringList gains = message.section('/', 1).split('/');
        QString nomMetier = gains[0];
        gains.pop_front();
        player->getPersoActuel()->getMetier(nomMetier)->gagneXp(gains[0].toInt());
        gains.pop_front();
        if(gains.size())
        {
            if(gains[0] == "r")
            {

                gains.pop_front();
                player->getPersoActuel()->ajouterRessource(Ressource::chargeRess(gains[0].toInt(), m_donnees_editeur->ressources->getRessource(gains[1])));
            }
            else if(gains[0] == "e")
            {
                gains.pop_front();
                Eqips equipements;
                equipements.nbr = 1;
                while(gains.size() > 3)
                {
                    equipements.equipement = Equipement::chargeEquipement(gains[0]+'/'+gains[1]+'/'+gains[2]+'/'+gains[3], m_donnees_editeur->ressources->getRessource(gains[0]));
                    player->getPersoActuel()->ajouterEquipement(equipements);
                    for(int i = 0; i < 4; i++)
                    {
                        gains.pop_front();
                    }
                }
            }
            else
            {
                gains.pop_front();
                Armes armes;
                armes.nbr = 1;
                while(gains.size() > 5)
                {
                    armes.arme = Arme::chargeArme(gains[0]+gains[1]+gains[2]+gains[3]+gains[4]+gains[5], m_donnees_editeur->ressources->getRessource(gains[0]), m_donnees_editeur->ressources->getSort(gains[4])->sortNiveau(gains[5].toInt()));
                    player->getPersoActuel()->ajouterArme(armes);
                    for(int i = 0; i < 6; i++)
                        gains.pop_front();
                }
            }
        }
        envoiGroupe(joueursPasEnCombat(), message.section('/',0,1), player->getPersoActuel()->getNom());
    }
    else if(begin == "cdm")//change of map
    {
        disconnectPlayer(player->getPersoActuel()->getNom());
        player->getPersoActuel()->setPosX(message.section("/", 0,0).toInt());
        player->getPersoActuel()->setPosY(message.section("/", 1,1).toInt());
        player->getPersoActuel()->setPosZ(message.section("/", 2,2).toInt());
        player->getPersoActuel()->setPosMap(message.section("/", 3,3).toInt(), message.section("/", 4,4).toInt());
        m_parent->map(player->getPersoActuel()->getPos())->connectPlayer(player,true);
    }
    else if (begin == "combat")
    {
        analyseCombat(message.section('/',0,0),message.section('/',1),player);
    }
    else if(begin == "eqi")
    {
        player->getPersoActuel()->equipeEquipement(message.section('/', 0,0).toInt(), message.section('/', 1,1));
    }
    else if(begin == "eqa")
    {
        player->getPersoActuel()->equipeArme(message.toInt());
    }
    else if(begin == "eeq")//enlève un equipement
    {
        int num = message.toInt();
        player->getPersoActuel()->desequipe(num);
    }
    else if(begin == "ear")//enlève l'arme
    {
        player->getPersoActuel()->desequipeArme();
    }
    else if(begin == "pnj")//a fini un dialogue avec un pnj
    {
        analyseReponsePnj(message, player);
    }
    else if(begin == "rrr")
    {
        player->getPersoActuel()->getMetier(message.section('/',0,0))->gagneXp(message.section('/',1,1).toInt());
        QStringList liste_fin = message.section('/',2).split('/');
        if(liste_fin[0] == "r")
        {
            liste_fin.pop_front();
            player->getPersoActuel()->ajouterRessource(Ressource::chargeRess(1, m_donnees_editeur->ressources->getRessource(liste_fin[0])));
            liste_fin.pop_front();
        }
        else if(liste_fin[0] == "e")
        {
            liste_fin.pop_front();
            player->getPersoActuel()->ajouterEquipement(Equipement::chargeEquipements("1/"+liste_fin[0]+'/'+liste_fin[1]+'/'+liste_fin[2]+'/'+liste_fin[3], m_donnees_editeur->ressources->getRessource(liste_fin[0])));
            for(int i = 0; i < 4; i++)
                liste_fin.pop_front();
        }
        else
        {
            liste_fin.pop_front();
            player->getPersoActuel()->ajouterArme(Arme::chargeArmes("1/"+liste_fin[0]+'/'+liste_fin[1]+'/'+liste_fin[2]+'/'+liste_fin[3]+'/'+liste_fin[4]+'/'+liste_fin[5], m_donnees_editeur->ressources->getRessource(liste_fin[0]), m_donnees_editeur->ressources->getSort(liste_fin[4])->sortNiveau(liste_fin[5].toInt())));
            for(int i = 0; i < 6; i++)
                liste_fin.pop_front();
        }

        while(liste_fin.size() > 1)
        {
            if(liste_fin[0] == "r")
            {
                liste_fin.pop_front();
                player->getPersoActuel()->enleverRessource(liste_fin[0].toInt(), liste_fin[1].toInt());
                liste_fin.pop_front();
                liste_fin.pop_front();
            }
            else if(liste_fin[0] == "e")
            {
                liste_fin.pop_front();
                player->getPersoActuel()->enleverEquipement(liste_fin[0].toInt(), liste_fin[1].toInt());
                liste_fin.pop_front();
                liste_fin.pop_front();
            }
            else
            {
                liste_fin.pop_front();
                player->getPersoActuel()->enleverArme(liste_fin[0].toInt(), liste_fin[1].toInt());
                liste_fin.pop_front();
                liste_fin.pop_front();
            }
        }
    }
}

void Map::analyseCombat(QString debut,QString fin,Joueur *joueur)
{
    if(debut == "jeDemandeDefi")
    {
        m_joueurs[fin]->envoi("demandeDefi/"+joueur->getPersoActuel()->getNom());
        addCombat(joueur->getPersoActuel(),m_joueurs[fin]->getPersoActuel());
    }
    else if(debut == "annuleDemandeDefi")
    {
        QString nom = combat(joueur->getPersoActuel()->getNom())->getNomLeader2();
        finCombat(joueur->getPersoActuel()->getNom());
        m_joueurs[nom]->envoi("annuleDemandeDefi");
    }
    else if(debut == "accepteDemandeDefi")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        enEquipe(nom);
    }
    else if(debut == "refuseDemandeDefi")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        m_joueurs[nom]->envoi("refuseDemandeDefi");
    }
    else if(debut == "changePosDep")
    {
        joueurChangePosDepart(joueur->getPersoActuel()->getNom(),fin.section('*',0,0).toInt(),fin.section('*',1,1).toInt());
    }
    else if(debut == "pret")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        combat(nom)->pret(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "pasPret")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        combat(nom)->pasPret(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "dep")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        combat(nom)->deplace(joueur->getPersoActuel()->getNom(),fin.section('*',0,0).toInt(),fin.section('*',1,1).toInt());
    }
    else if(debut == "passeTour")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        combat(nom)->passeTour(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "attaque")
    {
        QString nom = leaderDe(joueur->getPersoActuel()->getNom());
        combat(nom)->attaque(joueur->getPersoActuel()->getNom(),fin.section('/',0,0),fin.section('/',1,1).toInt(),fin.section('/',2,2).toInt());
    }
    else
    {
        qDebug() << "ATTENTION ERREUR DANS MESSAGES COMBAT";
    }
}

void Map::analyseReponsePnj(QString const& reponse, Joueur *player)
{
    if(reponse.section('_', 0, 0) == "metier")
    {
        player->getPersoActuel()->apprendMetier(reponse.section('_', 1));
    }
    else if(reponse.section('_', 0, 0) == "donneEquipement")
    {
        Equipement *equip = m_donnees_editeur->ressources->getEquipement(reponse.section('_',1))->genere();
        player->getPersoActuel()->ajouterEquipement(equip);
        player->envoi("gagneEquipement/"+Equipement::enString(equip));
    }
    else if(reponse.section('_', 0, 0) == "donneArme")
    {
        Arme *arme = m_donnees_editeur->ressources->getArme(reponse.section('_',1))->genere();
        player->getPersoActuel()->ajouterArme(arme);
        player->envoi("gagneArme/"+Arme::enString(arme));
    }
    else if(reponse.section('_',0,0) == "donneRessource")
    {
        player->getPersoActuel()->ajouterRessource(m_donnees_editeur->ressources->getRessource(reponse.section('_',1)));
        player->envoi("gagneRessource/"+reponse.section('_',1));
    }
}

