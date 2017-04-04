#include "fight.h"

Fight::Fight(QString nameFight,Character *moi)
{
    m_nameFight = nameFight;
    m_moi = moi;
    m_iAmLeader = (moi->getNom() == nameFight);
}
