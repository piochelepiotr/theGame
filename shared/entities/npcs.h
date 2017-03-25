#ifndef TOUSLESPNJ_H
#define TOUSLESPNJ_H

#include "entities/npc.h"
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "scenery/constants.h"

class NPCs
{
public:
    NPCs();
    ~NPCs();
    NPC *getpnj(qint16 num) const { return m_pers[num]; }

private:
    QMap<qint16, NPC*>m_pers;
};

#endif // TOUSLESPNJ_H
