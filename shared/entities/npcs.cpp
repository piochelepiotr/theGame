#include "entities/npcs.h"

NPCs::NPCs()
{
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        QString pnj;
        while(!(pnj = stream.readLine()).isNull())
        {
            if(!pnj.isEmpty())
                m_pers[(qint16) pnj.section('/',0,0).toInt()] = new NPC(pnj);
        }
        fichier.close();
    }
}

NPCs::~NPCs()
{
    for(QMap<qint16, NPC*>::iterator it = m_pers.begin(); it != m_pers.end(); it++)
    {
        delete it.value();
    }
}
