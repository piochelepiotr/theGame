#ifndef FIGHT_H
#define FIGHT_H

#include <QString>
#include "entities/character.h"

//enum PhaseFight { EnDemande, EnPlacement,EnFight };

class Fight
{
public:
    Fight(QString nomFight,Character *moi);
    QString leader() const { return m_nomFight; }


private:
    QString m_nomFight;
    Character *m_moi;
    bool m_iAmLeader;
};

#endif // FIGHT_H
