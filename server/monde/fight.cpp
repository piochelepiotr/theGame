#include "monde/fight.h"

Fight::Fight(Entity *leader1, Entity *leader2, Map *dataMap, int fightId) : QObject()
{
    m_fightId = fightId;
    m_dataMap = dataMap;
    m_entities[leader1->getNom()] = leader1;
    m_entities[leader2->getNom()] = leader2;
}

Fight::~Fight()
{
    finFight();
}

void Fight::addEntity(Character *perso)
{
    perso->setPret(false);
    m_entities[perso->getNom()] = perso;
}

void Fight::removeEntity(const QString &name)
{
    if(m_phase == EnDemande)
    {
        m_entities.remove(name);
        /*if(name == m_leader1)
        {
            emit envoie(m_leader2,"annuleDemandeDefi");
            emit s_finFight(m_leader1);
        }
        else
        {
            emit envoie(m_leader1,"refuseDemandeDefi");
            emit s_finFight(m_leader1);
        }*/
    }
    else if(m_phase == EnPlacement)
    {
        m_entities[name]->perdVie(m_entities[name]->getVie());
        m_entities.remove(name);
        envoieATous("dec/"+name);
        finFight();
        qDebug() << "fin du fight";
    }
    else if(m_phase == EnFight)
    {
        m_entities[name]->perdVie(m_entities[name]->getVie());
        m_entities.remove(name);
        envoieATous("dec/"+name);
        meurt(name,false);
    }   
}

void Fight::moveEntity(QString name, int x, int y)
{
    m_entities[name]->setPosMap(x,y);
    if(m_phase == EnPlacement)
    {
        for(auto const& entity : m_entities.keys())
        {
            emit envoie(entity, "dep/"+name+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
    else if(m_phase == EnFight)
    {
        for(auto const& entity : m_entities.keys())
        {
            emit envoie(entity, "dep/"+name+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
}

Entity *Fight::getCible(QPoint const& p)
{
    if(m_phase != EnFight)
        return 0;
    for(auto entity : m_entities)
    {
        if(entity->getPosMap() == p)
            return entity;
    }
    return 0;
}

void Fight::attack(QString nameAttaquant, QString nameSpell, int x, int y)
{
    if(m_phase != EnFight)
        return;
    Spell *spell = m_entities[nameAttaquant]->getSpell(nameSpell);
    Entity *cible = getCible(QPoint(x,y));
    if(cible != 0)
    {
        int degats = spell->degats();
        cible->perdVie(degats);
        for(auto const& entity : m_entities.keys())
        {
            emit envoie(entity,"fightVieDe/"+cible->getNom()+"/"+QString::number(cible->getVie()));
        }
        if(cible->getVie() == 0)
        {
            meurt(cible->getNom());
        }
    }
}

void Fight::passeTour(QString name)
{
    if(m_phase != EnFight)
        return;
    if(name == m_ordre[m_currentPlayer])
    {
        nextPlayer();
    }
}

bool Fight::contains(QString name)
{
    return m_entities.keys().contains(name);
}

bool Fight::personneSur(int x,int y)
{
    QPoint p(x,y);
    for(auto const& entity : m_entities)
    {
        if(entity->getPosMap() == p)
        {
            return false;
        }
    }
    return true;
}

void Fight::createTeams()
{
    int rand = qrand()%2;
    m_phase = EnPlacement;
    //they are only two entities here
    int i = 0;
    for(auto entity : m_entities)
    {
        int team = (rand+i)%2;
        i++;
        QPoint pos = m_dataMap->posDep(team);
        entity->setEquipe(team);
        sendIfNotMonster(entity->getNom(),"fight/"+QString::number(m_fightId)+"/"+QString::number(team));
        entity->setFightId(m_fightId);
        entity->setPosMap(pos.x(),pos.y());
        if(!entity->isMonster())
        {
            for(auto other : m_entities)
            {
                emit envoie(entity->getNom(), "newEntity/"+other->important());
            }
        }
    }
    emit decoFighttants(m_fightId);
}

void Fight::fightCommence()
{
    m_phase = EnFight;
    for(auto & entity : m_entities)
    {
        entity->setTour(false);
        emit envoie(entity->getNom(), "commenceFight");
    }
    for(auto const& name: m_entities.keys())
    {
        for(auto it2 = m_entities.begin(); it2 != m_entities.end(); it2++)
        {
            qDebug() << it2.value()->getVie() << "est la vie";
            qDebug() << it2.value()->getTotalVie() << "est le total";
            emit envoie(name,"fightVieDe/"+it2.key()+"/"+QString::number(it2.value()->getVie()));
        }
    }
    m_currentPlayer = -1;
    order();
    nextPlayer();
}

void Fight::toutLeMondeEstPret()
{
    for(auto const& entity : m_entities)
    {
        if(!entity->pret())
        {
            return;
        }
    }
    fightCommence();
}

void Fight::pret(QString name)
{
    m_entities[name]->setPret(true);
    toutLeMondeEstPret();
}

void Fight::pasPret(QString name)
{
    m_entities[name]->setPret(false);
}

void Fight::order()
{
    m_quantityFighttants = 0;
    for(auto const& name : m_entities.keys())
    {
        m_ordre.append(name);
        m_quantityFighttants++;
    }
}

void Fight::nextPlayer()
{
    if(m_phase != EnFight)
        return;
    if(m_currentPlayer != -1)
    {
        m_entities[m_ordre[m_currentPlayer]]->setTour(false);
        emit envoie(m_ordre[m_currentPlayer],"passeTour");
    }
    m_currentPlayer = (m_currentPlayer+1)%m_quantityFighttants;
    m_entities[m_ordre[m_currentPlayer]]->setTour(true);
    emit envoie(m_ordre[m_currentPlayer],"tonTour");
}

QStringList Fight::fighttants()
{
    /*QStringList fighttants;
    for(QMap<QString,Character*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        fighttants.append(name);
    }
    return fighttants;*/
    return m_entities.keys();
}

void Fight::meurt(QString const& name,bool envoyer)
{
    if(m_phase != EnFight)
        return;
    int l = m_ordre.length();
    for(int i = 0; i< l;i++)
    {
        if(m_ordre[i] == name)
        {
            m_ordre.remove(i);
            if(envoyer)
                envoieATous("meurt/"+name);
            if(!finFight())
            {
                m_quantityFighttants--;
                if(i == m_currentPlayer)
                {
                    m_currentPlayer %= m_quantityFighttants;
                    m_entities[m_ordre[m_currentPlayer]]->setTour(true);
                    emit envoie(m_ordre[m_currentPlayer],"tonTour");
                }
                else if(i > m_currentPlayer)
                {
                    m_currentPlayer--;
                }
            }
            return;
        }
    }
}

bool Fight::finFight()
{
    if(m_phase != EnFight && m_phase != EnPlacement)
        return false;
    int l = 0;
    int tailleEquipe0 = 0;
    for(auto const& entity : m_entities)
    {
        if(entity->getVie() != 0)
        {
            l++;
            if(entity->equipe() == 0)
                tailleEquipe0++;
        }
    }
    qDebug() << "taille equipe : " <<tailleEquipe0 << "  et l = " << l;
    if(tailleEquipe0 == 0 || tailleEquipe0 == l)
    {
        emit s_finFight(m_fightId);
        return true;
    }
    return false;
}

void Fight::envoieATous(QString const& message)
{
    for(auto const& name : m_entities.keys())
    {
        sendIfNotMonster(name,message);
    }
}

QString Fight::gainsFin()
{
    QString equipe0,equipe1;
    int niveauEquipe0 = 0,niveauEquipe1 = 0;
    int tailleEquipe0 = 0;
    for(auto const& entity : m_entities)
    {
        if(entity->equipe() == 0)
        {
            niveauEquipe0 += entity->getNiveau();
        }
        else
        {
            niveauEquipe1 += entity->getNiveau();
        }
        if(entity->getVie() != 0)
        {
            if(entity->equipe() == 0)
            {
                tailleEquipe0++;
            }
        }
    }
    for(auto const& entity : m_entities)
    {
        if(entity->equipe() == 0)
        {
            equipe0 += entity->gagneFinFight(niveauEquipe1,niveauEquipe0 != 0);
            equipe0 += "//";
        }
        else
        {
            equipe1 += entity->gagneFinFight(niveauEquipe0,niveauEquipe0 == 0);
            equipe1 += "//";
        }
    }
    if(tailleEquipe0 == 0)
    {
        qDebug() << "message :" << equipe1 +"*"+equipe0;
        return equipe1 +"*"+equipe0;
    }
    else
    {
        qDebug() << "message :" << equipe0 +"*"+equipe1;
        return equipe0 +"*"+equipe1;
    }
}

void Fight::sendIfNotMonster(QString const& name,QString const& message)
{
    Entity *entity = getEntity(name);
    if(!entity->isMonster())
    {
        emit envoie(name,message);
    }
}

