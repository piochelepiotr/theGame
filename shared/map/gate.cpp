#include "map/gate.h"

Gate::Gate(QString const& name, QString const& namearr, int mapx, int mapy,int mapz, Dir largage, int posx, int posy)
{
    m_name = name;
    m_name_arr = namearr;
    m_maparrX = mapx;
    m_maparrY = mapy;
    m_maparrZ = mapz;
    m_largage = largage;
    m_largageX = posx;
    m_largageY = posy;
    if(largage == O)
        m_largageY-=2;
    else if(largage == B)
        m_largageY+=2;
    else if(largage == D)
        m_largageX++;
    else if(largage == G)
        m_largageX--;
    else if(m_largageY % 2 == 0)
    {
        if(largage == OD)
        {
            m_largageY--;
        }
        if(largage == BD)
        {
            m_largageY++;
        }
        if(largage == OG)
        {
            m_largageX--;
            m_largageY--;
        }
        if(largage == BG)
        {
            m_largageX--;
            m_largageY++;
        }
    }
    else
    {
        if(largage == OD)
        {
            m_largageX++;
            m_largageY--;
        }
        if(largage == BD)
        {
            m_largageX++;
            m_largageY++;
        }
        if(largage == OG)
        {
            m_largageY--;
        }
        if(largage == BG)
        {
            m_largageY++;
        }
    }
}
