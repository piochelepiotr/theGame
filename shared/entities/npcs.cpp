#include "entities/npcs.h"

TouslesPnj::TouslesPnj()
{
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        QString pnj;
        while(!(pnj = stream.readLine()).isNull())
        {
            if(!pnj.isEmpty())
                m_pers[(qint16) pnj.section('/',0,0).toInt()] = new PersNonJ(pnj);
        }
        fichier.close();
    }
}

TouslesPnj::~TouslesPnj()
{
    for(QMap<qint16, PersNonJ*>::iterator it = m_pers.begin(); it != m_pers.end(); it++)
    {
        delete it.value();
    }
}
