#ifndef UNCHEMIN_H
#define UNCHEMIN_H

#include <QQueue>
#include <QPoint>
#include "additionalActions/constantes.h"

class UnChemin
{
public:

    UnChemin(UnChemin parent, Dir const& dir, int xp, int yp);
    UnChemin(QPoint const& p = QPoint(0,0));
    QPoint lacase() const { return m_case; }
    QQueue<Dir> chemin() const { return m_chemin; }


private:

    QQueue<Dir>m_chemin;
    QPoint m_case;
};

#endif // UNCHEMIN_H
