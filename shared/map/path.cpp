#include "map/path.h"

UnChemin::UnChemin(UnChemin parent, Dir const& dir, int xp, int yp)
{

    while(!parent.m_chemin.isEmpty())
    {
        m_chemin.enqueue(parent.m_chemin.dequeue());
    }
    m_chemin.enqueue(dir);
    m_case = parent.m_case;
    m_case.setX(m_case.x()+xp);
    m_case.setY(m_case.y()+yp);
}

UnChemin::UnChemin(QPoint const& p)
{
    m_case = p;
}
