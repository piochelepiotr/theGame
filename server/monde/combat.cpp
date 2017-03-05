#include "monde/combat.h"

Combat::Combat(Personnage *leader1, Personnage *leader2, DataMap *dataMap) : QObject()
{
    m_dataMap = dataMap;
    leader1->setPret(false);
    leader2->setPret(false);
    m_leader1 = leader1->getNom();
    m_leader2 = leader2->getNom();
    m_combattants[m_leader1] = leader1;
    m_combattants[m_leader2] = leader2;
    m_phase = EnDemande;
}

Combat::~Combat()
{
    finCombat();
}

void Combat::ajoutePerso(Personnage *perso)
{
    perso->setPret(false);
    m_combattants[perso->getNom()] = perso;
}

void Combat::enlevePerso(QString nom)
{
    if(m_phase == EnDemande)
    {
        m_combattants.remove(nom);
        if(nom == m_leader1)
        {
            emit envoie(m_leader2,"annuleDemandeDefi");
            emit s_finCombat(m_leader1);
        }
        else
        {
            emit envoie(m_leader1,"refuseDemandeDefi");
            emit s_finCombat(m_leader1);
        }
    }
    else if(m_phase == EnPlacement)
    {
        m_combattants[nom]->perdVie(m_combattants[nom]->getVie());
        m_combattants.remove(nom);
        envoieATous("dec/"+nom);
        finCombat();
        qDebug() << "fin du combat";
    }
    else if(m_phase == EnCombat)
    {
        m_combattants[nom]->perdVie(m_combattants[nom]->getVie());
        m_combattants.remove(nom);
        envoieATous("dec/"+nom);
        meurt(nom,false);
    }   
}

void Combat::deplace(QString nom, int x, int y)
{
    m_combattants[nom]->setPosMap(x,y);
    if(m_phase == EnPlacement)
    {
        for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
        {
            emit envoie(it.key(), "dep/"+nom+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
    else if(m_phase == EnCombat)
    {
        for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
        {
            emit envoie(it.key(), "dep/"+nom+"*"+QString::number(x)+"*"+QString::number(y));
        }
    }
}

Personnage *Combat::getCible(QPoint const& p)
{
    if(m_phase != EnCombat)
        return 0;
    for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        if(it.value()->getPosMap() == p)
            return it.value();
    }
    return 0;
}

void Combat::attaque(QString nomAttaquant, QString nomSort, int x, int y)
{
    if(m_phase != EnCombat)
        return;
    Sort *sort = m_combattants[nomAttaquant]->getSort(nomSort);
    Personnage *cible = getCible(QPoint(x,y));
    if(cible != 0)
    {
        int degats = sort->degats();
        cible->perdVie(degats);
        for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
        {
            emit envoie(it.key(),"combatVieDe/"+cible->getNom()+"/"+QString::number(cible->getVie()));
        }
        if(cible->getVie() == 0)
        {
            meurt(cible->getNom());
        }
    }
}

void Combat::passeTour(QString nom)
{
    if(m_phase != EnCombat)
        return;
    if(nom == m_ordre[m_currentPlayer])
    {
        nextPlayer();
    }
}

bool Combat::contains(QString nom)
{
    return m_combattants.keys().contains(nom);
}

bool Combat::personneSur(int x,int y)
{
    QPoint p(x,y);
    for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        if(it.value()->getPosMap() == p)
        {
            return false;
        }
    }
    return true;
}

void Combat::enEquipe(int equipe1,int equipe2,QPoint const& pos1,QPoint const& pos2)
{
    m_phase = EnPlacement;
    getPersonnage(m_leader1)->setEquipe(equipe1);
    getPersonnage(m_leader2)->setEquipe(equipe2);
    emit envoie(m_leader1,"commenceDefi/"+QString::number(equipe1));
    emit envoie(m_leader2,"commenceDefi/"+QString::number(1-equipe1));
    deplace(m_leader1,pos1.x(),pos1.y());
    deplace(m_leader2,pos2.x(),pos2.y());
    getPersonnage(m_leader1)->setEnCombat(true);
    getPersonnage(m_leader2)->setEnCombat(true);
    emit decoCombattants(m_leader1);
}

void Combat::combatCommence()
{
    m_phase = EnCombat;
    for(QMap<QString, Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        it.value()->setTour(false);
        emit envoie(it.value()->getNom(), "commenceCombat");
    }
    for(QMap<QString,Personnage*>::const_iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        for(QMap<QString,Personnage*>::const_iterator it2 = m_combattants.begin(); it2 != m_combattants.end(); it2++)
        {
            qDebug() << it2.value()->getVie() << "est la vie";
            qDebug() << it2.value()->getTotalVie() << "est le total";
            emit envoie(it.key(),"combatVieDe/"+it2.key()+"/"+QString::number(it2.value()->getVie()));
        }
    }
    m_currentPlayer = -1;
    order();
    nextPlayer();
}

void Combat::toutLeMondeEstPret()
{
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        if(!it.value()->pret())
        {
            return;
        }
    }
    combatCommence();
}

void Combat::pret(QString nom)
{
    m_combattants[nom]->setPret(true);
    toutLeMondeEstPret();
}

void Combat::pasPret(QString nom)
{
    m_combattants[nom]->setPret(false);
}

void Combat::order()
{
    m_nombreCombattants = 0;
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        m_ordre.append(it.key());
        m_nombreCombattants++;
    }
}

void Combat::nextPlayer()
{
    if(m_phase != EnCombat)
        return;
    if(m_currentPlayer != -1)
    {
        m_combattants[m_ordre[m_currentPlayer]]->setTour(false);
        emit envoie(m_ordre[m_currentPlayer],"passeTour");
    }
    m_currentPlayer = (m_currentPlayer+1)%m_nombreCombattants;
    m_combattants[m_ordre[m_currentPlayer]]->setTour(true);
    emit envoie(m_ordre[m_currentPlayer],"tonTour");
}

QStringList Combat::combattants()
{
    QStringList combattants;
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        combattants.append(it.key());
    }
    return combattants;
}

void Combat::meurt(QString const& nom,bool envoyer)
{
    if(m_phase != EnCombat)
        return;
    int l = m_ordre.length();
    for(int i = 0; i< l;i++)
    {
        if(m_ordre[i] == nom)
        {
            m_ordre.remove(i);
            if(envoyer)
                envoieATous("meurt/"+nom);
            if(!finCombat())
            {
                m_nombreCombattants--;
                if(i == m_currentPlayer)
                {
                    m_currentPlayer %= m_nombreCombattants;
                    m_combattants[m_ordre[m_currentPlayer]]->setTour(true);
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

bool Combat::finCombat()
{
    if(m_phase != EnCombat && m_phase != EnPlacement)
        return false;
    int l = 0;
    int tailleEquipe0 = 0;
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
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
        emit s_finCombat(m_leader1);
        return true;
    }
    return false;
}

void Combat::envoieATous(QString const& message)
{
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        emit envoie(it.key(),message);
    }
}

QString Combat::gainsFin()
{
    QString equipe0,equipe1;
    int niveauEquipe0 = 0,niveauEquipe1 = 0;
    int tailleEquipe0 = 0;
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
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
    for(QMap<QString,Personnage*>::iterator it = m_combattants.begin(); it != m_combattants.end(); it++)
    {
        if(it.value()->equipe() == 0)
        {
            equipe0 += it.value()->gagneFinCombat(niveauEquipe1,niveauEquipe0 != 0);
            equipe0 += "//";
        }
        else
        {
            equipe1 += it.value()->gagneFinCombat(niveauEquipe0,niveauEquipe0 == 0);
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

