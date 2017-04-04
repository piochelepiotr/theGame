#include "monde/fight.h"

Fight::Fight(Character *leader1, Character *leader2, Map *dataMap) : QObject()
{
    m_dataMap = dataMap;
    leader1->setPret(false);
    leader2->setPret(false);
    m_leader1 = leader1->getNom();
    m_leader2 = leader2->getNom();
    m_fighttants[m_leader1] = leader1;
    m_fighttants[m_leader2] = leader2;
    m_phase = EnDemande;
}

Fight::~Fight()
{
    finFight();
}

void Fight::ajoutePerso(Character *perso)
{
    perso->setPret(false);
    m_fighttants[perso->getNom()] = perso;
}

void Fight::enlevePerso(QString name)
{
    if(m_phase == EnDemande)
    {
        m_fighttants.remove(name);
        if(name == m_leader1)
        {
            emit envoie(m_leader2,"annuleDemandeDefi");
            emit s_finFight(m_leader1);
        }
        else
        {
            emit envoie(m_leader1,"refuseDemandeDefi");
            emit s_finFight(m_leader1);
        }
    }
    else if(m_phase == EnPlacement)
    {
        m_fighttants[name]->perdVie(m_fighttants[name]->getVie());
        m_fighttants.remove(name);
        envoieATous("dec/"+name);
        finFight();
        qDebug() << "fin du fight";
    }
    else if(m_phase == EnFight)
    {
        m_fighttants[name]->perdVie(m_fighttants[name]->getVie());
        m_fighttants.remove(name);
        envoieATous("dec/"+name);
        meurt(name,false);
    }   
}

void Fight::deplace(QString name, int x, int y)
{
    m_fighttants[name]->setPosMap(x,y);
    if(m_phase == EnPlacement)
    {
        for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
        {
            emit envoie(it.key(), "dep/"+name+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
    else if(m_phase == EnFight)
    {
        for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
        {
            emit envoie(it.key(), "dep/"+name+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
}

Character *Fight::getCible(QPoint const& p)
{
    if(m_phase != EnFight)
        return 0;
    for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(it.value()->getPosMap() == p)
            return it.value();
    }
    return 0;
}

void Fight::attaque(QString nameAttaquant, QString nameSpell, int x, int y)
{
    if(m_phase != EnFight)
        return;
    Spell *spell = m_fighttants[nameAttaquant]->getSpell(nameSpell);
    Character *cible = getCible(QPoint(x,y));
    if(cible != 0)
    {
        int degats = spell->degats();
        cible->perdVie(degats);
        for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
        {
            emit envoie(it.key(),"fightVieDe/"+cible->getNom()+"/"+QString::number(cible->getVie()));
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
    return m_fighttants.keys().contains(name);
}

bool Fight::personneSur(int x,int y)
{
    QPoint p(x,y);
    for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(it.value()->getPosMap() == p)
        {
            return false;
        }
    }
    return true;
}

void Fight::enEquipe(int equipe1,int equipe2,QPoint const& pos1,QPoint const& pos2)
{
    m_phase = EnPlacement;
    getPersonnage(m_leader1)->setEquipe(equipe1);
    getPersonnage(m_leader2)->setEquipe(equipe2);
    emit envoie(m_leader1,"commenceDefi/"+QString::number(equipe1));
    emit envoie(m_leader2,"commenceDefi/"+QString::number(1-equipe1));
    deplace(m_leader1,pos1.x(),pos1.y());
    deplace(m_leader2,pos2.x(),pos2.y());
    getPersonnage(m_leader1)->setEnFight(true);
    getPersonnage(m_leader2)->setEnFight(true);
    emit decoFighttants(m_leader1);
}

void Fight::fightCommence()
{
    m_phase = EnFight;
    for(QMap<QString, Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        it.value()->setTour(false);
        emit envoie(it.value()->getNom(), "commenceFight");
    }
    for(QMap<QString,Character*>::const_iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        for(QMap<QString,Character*>::const_iterator it2 = m_fighttants.begin(); it2 != m_fighttants.end(); it2++)
        {
            qDebug() << it2.value()->getVie() << "est la vie";
            qDebug() << it2.value()->getTotalVie() << "est le total";
            emit envoie(it.key(),"fightVieDe/"+it2.key()+"/"+QString::number(it2.value()->getVie()));
        }
    }
    m_currentPlayer = -1;
    order();
    nextPlayer();
}

void Fight::toutLeMondeEstPret()
{
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(!it.value()->pret())
        {
            return;
        }
    }
    fightCommence();
}

void Fight::pret(QString name)
{
    m_fighttants[name]->setPret(true);
    toutLeMondeEstPret();
}

void Fight::pasPret(QString name)
{
    m_fighttants[name]->setPret(false);
}

void Fight::order()
{
    m_quantityFighttants = 0;
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        m_ordre.append(it.key());
        m_quantityFighttants++;
    }
}

void Fight::nextPlayer()
{
    if(m_phase != EnFight)
        return;
    if(m_currentPlayer != -1)
    {
        m_fighttants[m_ordre[m_currentPlayer]]->setTour(false);
        emit envoie(m_ordre[m_currentPlayer],"passeTour");
    }
    m_currentPlayer = (m_currentPlayer+1)%m_quantityFighttants;
    m_fighttants[m_ordre[m_currentPlayer]]->setTour(true);
    emit envoie(m_ordre[m_currentPlayer],"tonTour");
}

QStringList Fight::fighttants()
{
    QStringList fighttants;
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        fighttants.append(it.key());
    }
    return fighttants;
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
                    m_fighttants[m_ordre[m_currentPlayer]]->setTour(true);
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
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(it.value()->getVie() != 0)
        {
            l++;
            if(it.value()->equipe() == 0)
                tailleEquipe0++;
        }
    }
    qDebug() << "taille equipe : " <<tailleEquipe0 << "  et l = " << l;
    if(tailleEquipe0 == 0 || tailleEquipe0 == l)
    {
        emit s_finFight(m_leader1);
        return true;
    }
    return false;
}

void Fight::envoieATous(QString const& message)
{
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        emit envoie(it.key(),message);
    }
}

QString Fight::gainsFin()
{
    QString equipe0,equipe1;
    int niveauEquipe0 = 0,niveauEquipe1 = 0;
    int tailleEquipe0 = 0;
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(it.value()->equipe() == 0)
        {
            niveauEquipe0 += it.value()->getNiveau();
        }
        else
        {
            niveauEquipe1 += it.value()->getNiveau();
        }
        if(it.value()->getVie() != 0)
        {
            if(it.value()->equipe() == 0)
            {
                tailleEquipe0++;
            }
        }
    }
    for(QMap<QString,Character*>::iterator it = m_fighttants.begin(); it != m_fighttants.end(); it++)
    {
        if(it.value()->equipe() == 0)
        {
            equipe0 += it.value()->gagneFinFight(niveauEquipe1,niveauEquipe0 != 0);
            equipe0 += "//";
        }
        else
        {
            equipe1 += it.value()->gagneFinFight(niveauEquipe0,niveauEquipe0 == 0);
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

