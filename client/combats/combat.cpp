#include "combat.h"

Combat::Combat(QString nomCombat,Character *moi)
{
    m_nomCombat = nomCombat;
    m_moi = moi;
    m_iAmLeader = (moi->getNom() == nomCombat);
}
