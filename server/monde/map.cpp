#include "map.h"
#include "graphic/ecran.h"
#include "monde/monde.h"

#define MAX_FIGHTS 50
#define NBR_MONSTRES_MAP 5

ServerMap::ServerMap(Data *donnees_editeur, Monde *parent, Point const& pos,Ecran *ecran)
{
    m_donnees_editeur = donnees_editeur;
    m_ecran = ecran;
    m_pos = pos;
    m_map = new Map(donnees_editeur,pos.x,pos.y,pos.z);
    m_parent = parent;
    m_map->coupable(&m_objets_coupables);
    m_aide_timers = new QSignalMapper(this);
    for(int  i = 0; i < NBR_MONSTRES_MAP;i++)
    {
        addMonstre();
    }
    connect(m_aide_timers, SIGNAL(mapped(int)), this, SLOT(repousse(int)));
}

void ServerMap::addMonstre()
{
    MonsterModel *monstre = m_map->nouveauMonstre();
    if(monstre)
    {
        QString name = nameMonstre(monstre->getClass());
        QPoint p = m_map->caseLibre();
        m_monstres[name] = monstre->generateMonster(m_map->x(),m_map->y(),m_map->z(),p.x(),p.y(),m_donnees_editeur,name);
    }
}

QString ServerMap::nameMonstre(QString const& nameClasse)
{
    for(int i = 0; i < NBR_MONSTRES_MAP*2+2;i++)//*2+2 pour être sûr qu'on trouvera un i
    {
        QString name = nameClasse+"_"+QString::number(i);
        if(!m_monstres.contains(name))
        {
            return name;
        }
    }
    qDebug() << "Pas de name pour monstre trouvé !!";
    exit(1);
    return "";
}

QString ServerMap::resources_coupees() const
{
    QString resources;
    for(QMap<QPoint, bool>::const_iterator it = m_objets_coupables.begin(); it != m_objets_coupables.end(); it++)
    {
        if(!it.value())
        {
            resources += QString::number(it.key().x()).rightJustified(2, '0');
            resources += QString::number(it.key().y()).rightJustified(2, '0');
        }
    }
    return resources;
}

void ServerMap::coupe(QPoint p)
{
    int pos = p.x()*1000+p.y();
    m_objets_coupables[p] = false;

    int interval = TEMPS_MIN_REPOUSSE+qrand()%(TEMPS_MAX_REPOUSSE-TEMPS_MIN_REPOUSSE);

    if(!m_timers.contains(p))
    {
        m_timers[p] = new QTimer(this);
        m_timers[p]->setInterval(interval);
        m_timers[p]->setSingleShot(true);
        connect(m_timers[p], SIGNAL(timeout()), m_aide_timers, SLOT(ServerMap()));
    }
    else
        m_aide_timers->removeMappings(m_timers[p]);
    m_aide_timers->setMapping(m_timers[p], pos);
    m_timers[p]->start();
}

void ServerMap::repousse(int pos)
{
    QPoint p(pos/1000, pos%1000);
    m_objets_coupables[p] = true;
    envoiGroupe(joueursPasEnFight(), "rep/"+QString::number(p.x())+'*'+QString::number(p.y()));
}

void ServerMap::addFight(Entity *leader1, Entity *leader2)
{
    int fightId = findFightId();
    m_fights[fightId] = new Fight(leader1,leader2,m_map,fightId);
    connect(m_fights[fightId],SIGNAL(envoie(QString,QString)), this,SLOT(sendToPlayer(QString,QString)));
    connect(m_fights[fightId],SIGNAL(decoFighttants(int)),this,SLOT(decoFighttants(int)));
    connect(m_fights[fightId],SIGNAL(s_finFight(int)),this,SLOT(finFight(int)));
    m_fights[fightId]->createTeams();
}

void ServerMap::sendToPlayer(QString const& name,QString const& message)
{
    m_joueurs[name]->envoi(message);
}

void ServerMap::decoFighttants(int fightId)
{
    QStringList names = fight(fightId)->fighttants();
    int longueur = names.length();
    QList<Joueur*>joueurs = joueursPasEnFight();
    for(int j = 0; j < joueurs.size(); j++)
    {
        for(int i = 0; i < longueur; i++)
        {
            joueurs.at(j)->envoi("dec/"+names[i]);
            m_joueurs[names[i]]->envoi("dec/"+joueurs.at(j)->getPersoActuel()->getNom());
        }
    }
}

void ServerMap::recoFighttants(int fightId)
{
    QStringList names = fight(fightId)->fighttants();
    QList<Entity*>entities = getEntitiesNotFighting();
    int l = names.length();
    Entity *entity = 0;
    for(int i = 0; i < l;i++)
    {
        entity = fight(fightId)->getEntity(names[i]);
        entity->setFightId(-1);
        //envoieA(fight(fightId)->fighttants(),"changePos/"+entity->getNom()+"/"+QString::number(entity->getPosMap().x())+"/"+QString::number(entity->getPosMap().y()));
    }

    //2 things to do :
    //send all the players that have just get out of the fight to everyone not fighting
    //send all the players and monsters that were not in a fight to the players (not monsters) that have just get out of the fight
    for(auto const& name : names)
    {
        if(m_joueurs.contains(name))//if it is a player and not a monster
        {
            for(auto const& entity : entities)
            {
                m_joueurs[name]->envoi("con/"+entity->important());
            }
        }
        sendToNotFighting("con/"+fight(fightId)->getEntity(name)->important());
    }
}

void ServerMap::sendToNotFighting(QString const& message) const
{
    for(auto const& player : m_joueurs)
    {
        if(!player->getPersoActuel()->enFight())
        {
            player->envoi(message);
        }
    }
}

void ServerMap::finFight(int fightId)
{
    Fight *fight = m_fights[fightId];
    if(fight->phase() == EnDemande)
    {

    }
    else if(fight->phase() == EnPlacement)
    {
        QString texte = fight->gainsFin();
        envoieA(fight->characters(), "finFight/"+texte);
        recoFighttants(fightId);
    }
    else if(fight->phase() == EnFight)
    {
        QString texte = fight->gainsFin();
        envoieA(fight->characters(), "finFight/"+texte);
        recoFighttants(fightId);
    }
    disconnect(fight);
    fight->setPhase(FightFini);
    delete fight;
    m_fights.remove(fightId);
}

void ServerMap::finFightAvantDebut(int fightId)
{
    disconnect(m_fights[fightId]);
    delete m_fights[fightId];
    m_fights.remove(fightId);
}

Fight *ServerMap::fight(int fightId)
{
    return m_fights[fightId];
}

ServerMap::~ServerMap()
{
    delete m_map;
    for(auto fight : m_fights)
    {
        delete fight;
    }
}

void ServerMap::joueurChangePosDepart(QString name, int x, int y)
{
    int fightId = m_joueurs[name]->getPersoActuel()->getFightId();
    if(m_map->estCaseDeDepart(x,y,fight(fightId)->getEntity(name)->equipe()))
    {
        if(m_fights[fightId]->personneSur(x,y))
        {
            qDebug() << "on deplace";
            m_fights[fightId]->moveEntity(name,x,y);
        }
    }
}



void ServerMap::envoieA(QStringList names,QString message)
{
    for(int i = 0; i < names.length(); i++)
    {
        m_joueurs[names[i]]->envoi(message);
    }
}

void ServerMap::connectPlayer(Joueur *joueur,bool hasJustChangedServerMap)
{
    if(!hasJustChangedServerMap)
        joueur->joue();
    QList<Joueur*>pasEnFight = joueursPasEnFight();
    QList<Monster*>monstersNotFighting = monsterNotFighting();
    QString message = "ttt/"+resources_coupees()+'/';
    for(int i = 0; i < pasEnFight.size(); i++)
    {
        message += pasEnFight[i]->getPersoActuel()->important()+'/';
    }
    for(auto const& i : monstersNotFighting)
    {
        message += i->important() + '/';
    }
    joueur->envoi(message);
    m_joueurs[joueur->getPersoActuel()->getNom()] = joueur;
    envoiGroupe(pasEnFight, "con/"+joueur->getPersoActuel()->important());
}

void ServerMap::disconnectPlayer(QString const& name)
{
    qDebug() << "disconnect player";
    Character *pers = m_joueurs[name]->getPersoActuel();
    m_joueurs.remove(name);
    if(pers->enFight())
    {
        Fight *figth = fight(pers->getFightId());
        figth->removeEntity(name);
    }
    else
    {
        envoiGroupe(joueursPasEnFight(), "dec/"+name);
    }
}

QList<Joueur*> ServerMap::joueursPasEnFight()
{
    QList<Joueur*>joueursPasEnFight;
    for(QMap<QString,Joueur*>::iterator it = m_joueurs.begin(); it != m_joueurs.end(); it++)
    {
        if(!it.value()->getPersoActuel()->enFight())
            joueursPasEnFight.append(it.value());
    }
    return joueursPasEnFight;
}

QList<Monster*> ServerMap::monsterNotFighting()
{
    QList<Monster*>monsterNotFighting;
    for(auto const& i : m_monstres)
    {
        if(!i->enFight())
            monsterNotFighting.append(i);
    }
    return monsterNotFighting;
}

QList<Entity *> ServerMap::getEntitiesNotFighting()
{
    QList<Entity *>entitiesNotFighting;

    for(auto const& monster : monsterNotFighting())
    {
        entitiesNotFighting.append(monster);
    }
    for(auto const& player : joueursPasEnFight())
    {
        entitiesNotFighting.append(player->getPersoActuel());
    }
    return entitiesNotFighting;
}

void envoiGroupe(QList<Joueur*> const& receveurs, QString const& message, const QString &name)
{
    for(QList<Joueur*>::const_iterator it = receveurs.begin(); it != receveurs.end(); it++)
    {
        if((*it)->getPersoActuel()->getNom() != name)
            (*it)->envoi(message);
    }
}

void ServerMap::receiveMessage(Joueur *player, QString const& begin, QString const& message)
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
        envoiGroupe(joueursPasEnFight(),message);
    }
    else if(begin == "dep")
    {
        player->getPersoActuel()->setPosMap(message.section('*',1,1).toInt(), message.section('*',2,2).toInt());
        envoiGroupe(joueursPasEnFight(), message, player->getPersoActuel()->getNom());
    }
    else if(begin == "cut")//recolte d'une resource
    {
        envoiGroupe(joueursPasEnFight(), message, player->getPersoActuel()->getNom());
    }
    else if(begin == "cop")//resource coupee
    {
        coupe(QPoint(message.section('/', 0, 0).section('*', 0, 0).toInt(), message.section('/', 0, 0).section('*', 1, 1).toInt()));
        QStringList gains = message.section('/', 1).split('/');
        QString nameMetier = gains[0];
        gains.pop_front();
        player->getPersoActuel()->getMetier(nameMetier)->gagneXp(gains[0].toInt());
        gains.pop_front();
        if(gains.size())
        {
            if(gains[0] == "r")
            {

                gains.pop_front();
                player->getPersoActuel()->ajouterRessource(Resource::chargeRess(gains[0].toInt(), m_donnees_editeur->resources->getRessource(gains[1])));
            }
            else if(gains[0] == "e")
            {
                gains.pop_front();
                Eqips equipements;
                equipements.nbr = 1;
                while(gains.size() > 3)
                {
                    equipements.equipement = Outfit::chargeEquipement(gains[0]+'/'+gains[1]+'/'+gains[2]+'/'+gains[3], m_donnees_editeur->resources->getRessource(gains[0]));
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
                    armes.arme = Weapon::chargeArme(gains[0]+gains[1]+gains[2]+gains[3]+gains[4]+gains[5], m_donnees_editeur->resources->getRessource(gains[0]), m_donnees_editeur->resources->getSpell(gains[4])->spellNiveau(gains[5].toInt()));
                    player->getPersoActuel()->ajouterArme(armes);
                    for(int i = 0; i < 6; i++)
                        gains.pop_front();
                }
            }
        }
        envoiGroupe(joueursPasEnFight(), message.section('/',0,1), player->getPersoActuel()->getNom());
    }
    else if(begin == "cdm")//change of ServerMap
    {
        disconnectPlayer(player->getPersoActuel()->getNom());
        player->getPersoActuel()->setPosX(message.section("/", 0,0).toInt());
        player->getPersoActuel()->setPosY(message.section("/", 1,1).toInt());
        player->getPersoActuel()->setPosZ(message.section("/", 2,2).toInt());
        player->getPersoActuel()->setPosMap(message.section("/", 3,3).toInt(), message.section("/", 4,4).toInt());
        m_parent->map(player->getPersoActuel()->getPos())->connectPlayer(player,true);
    }
    else if (begin == "fight")
    {
        analyseFight(message.section('/',0,0),message.section('/',1),player);
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
            player->getPersoActuel()->ajouterRessource(Resource::chargeRess(1, m_donnees_editeur->resources->getRessource(liste_fin[0])));
            liste_fin.pop_front();
        }
        else if(liste_fin[0] == "e")
        {
            liste_fin.pop_front();
            player->getPersoActuel()->ajouterEquipement(Outfit::chargeEquipements("1/"+liste_fin[0]+'/'+liste_fin[1]+'/'+liste_fin[2]+'/'+liste_fin[3], m_donnees_editeur->resources->getRessource(liste_fin[0])));
            for(int i = 0; i < 4; i++)
                liste_fin.pop_front();
        }
        else
        {
            liste_fin.pop_front();
            player->getPersoActuel()->ajouterArme(Weapon::chargeArmes("1/"+liste_fin[0]+'/'+liste_fin[1]+'/'+liste_fin[2]+'/'+liste_fin[3]+'/'+liste_fin[4]+'/'+liste_fin[5], m_donnees_editeur->resources->getRessource(liste_fin[0]), m_donnees_editeur->resources->getSpell(liste_fin[4])->spellNiveau(liste_fin[5].toInt())));
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

void ServerMap::analyseFight(QString debut,QString fin,Joueur *joueur)
{
    /*if(debut == "jeDemandeDefi")
    {
        m_joueurs[fin]->envoi("demandeDefi/"+joueur->getPersoActuel()->getNom());
        addFight(joueur->getPersoActuel(),m_joueurs[fin]->getPersoActuel());
    }
    else if(debut == "annuleDemandeDefi")
    {
        QString name = fight(joueur->getPersoActuel()->getFightId())->getNomLeader2();
        finFight(joueur->getPersoActuel()->getFightId());
        m_joueurs[name]->envoi("annuleDemandeDefi");
    }
    else if(debut == "accepteDemandeDefi")
    {
        enEquipe(joueur->getPersoActuel()->getFightId());
    }
    else if(debut == "refuseDemandeDefi")
    {
        QString name = leaderDe(joueur->getPersoActuel()->getNom());
        m_joueurs[name]->envoi("refuseDemandeDefi");
    }*/
    if(debut == "changePosDep")
    {
        joueurChangePosDepart(joueur->getPersoActuel()->getNom(),fin.section('*',0,0).toInt(),fin.section('*',1,1).toInt());
    }
    else if(debut == "pret")
    {
        fight(joueur->getPersoActuel()->getFightId())->pret(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "pasPret")
    {
        fight(joueur->getPersoActuel()->getFightId())->pasPret(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "dep")
    {
        fight(joueur->getPersoActuel()->getFightId())->moveEntity(joueur->getPersoActuel()->getNom(),fin.section('*',0,0).toInt(),fin.section('*',1,1).toInt());
    }
    else if(debut == "passeTour")
    {
        fight(joueur->getPersoActuel()->getFightId())->passeTour(joueur->getPersoActuel()->getNom());
    }
    else if(debut == "attaque")
    {
        fight(joueur->getPersoActuel()->getFightId())->attack(joueur->getPersoActuel()->getNom(),fin.section('/',0,0),fin.section('/',1,1).toInt(),fin.section('/',2,2).toInt());
    }
    else if(debut == "attackMonster")
    {
        //check if the monster can be attacked
        if(m_monstres.contains(fin))
        {
            Entity *monster = m_monstres[fin];
            if(monster->getFightId() == -1)
            {
                //ok
                qDebug() << "fight with "<< monster->getNom();
                addFight(joueur->getPersoActuel(),monster);
            }
        }
    }
    else
    {
        qDebug() << "ATTENTION ERREUR DANS MESSAGES COMBAT";
    }
}

void ServerMap::analyseReponsePnj(QString const& reponse, Joueur *player)
{
    if(reponse.section('_', 0, 0) == "metier")
    {
        player->getPersoActuel()->learnJob(reponse.section('_', 1));
    }
    else if(reponse.section('_', 0, 0) == "donneEquipement")
    {
        Outfit *equip = m_donnees_editeur->resources->getEquipement(reponse.section('_',1))->genere();
        player->getPersoActuel()->ajouterEquipement(equip);
        player->envoi("gagneEquipement/"+Outfit::enString(equip));
    }
    else if(reponse.section('_', 0, 0) == "donneArme")
    {
        Weapon *arme = m_donnees_editeur->resources->getArme(reponse.section('_',1))->genere();
        player->getPersoActuel()->ajouterArme(arme);
        player->envoi("gagneArme/"+Weapon::enString(arme));
    }
    else if(reponse.section('_',0,0) == "donneRessource")
    {
        player->getPersoActuel()->ajouterRessource(m_donnees_editeur->resources->getRessource(reponse.section('_',1)));
        player->envoi("gagneRessource/"+reponse.section('_',1));
    }
}

int ServerMap::findFightId() const
{
    for(int i = 0; i < MAX_FIGHTS; i++)
    {
        if(!m_fights.contains(i))
            return i;
    }
    qDebug() << "Max fight number on map reached";
    return -1;
}

