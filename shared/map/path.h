#ifndef UNCHEMIN_H
#define UNCHEMIN_H

#include <QQueue>
#include <QPoint>
#include "scenery/constants.h"

class Path
{
public:

    Path(Path parent, Dir const& dir, int xp, int yp);
    Path(QPoint const& p = QPoint(0,0));
    QPoint lacase() const { return m_case; }
    QQueue<Dir> chemin() const { return m_chemin; }


private:

    QQueue<Dir>m_chemin;
    QPoint m_case;
};

#endif // UNCHEMIN_H
