#ifndef COMBAT_H
#define COMBAT_H

#include <QString>
#include "entities/character.h"

//enum PhaseCombat { EnDemande, EnPlacement,EnCombat };

class Combat
{
public:
    Combat(QString nomCombat,Character *moi);
    QString leader() const { return m_nomCombat; }


private:
    QString m_nomCombat;
    Character *m_moi;
    bool m_iAmLeader;
};

#endif // COMBAT_H
