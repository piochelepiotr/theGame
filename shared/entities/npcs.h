#ifndef TOUSLESPNJ_H
#define TOUSLESPNJ_H

#include "infoMonde/persnonj.h"
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "scenery/constants.h"

class TouslesPnj
{
public:
    TouslesPnj();
    ~TouslesPnj();
    PersNonJ *getpnj(qint16 num) const { return m_pers[num]; }

private:
    QMap<qint16, PersNonJ*>m_pers;
};

#endif // TOUSLESPNJ_H
