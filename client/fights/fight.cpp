#include "fight.h"

Fight::Fight(QString nomFight,Character *moi)
{
    m_nomFight = nomFight;
    m_moi = moi;
    m_iAmLeader = (moi->getNom() == nomFight);
}
