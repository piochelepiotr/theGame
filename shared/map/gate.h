#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H

#include "scenery/constants.h"

class Gate
{
public :

    Gate(QString const& name = "", QString const& namearr = "", int mapx = 0, int mapy = 0, int mapz = 0, Dir largage = B, int posx = 0, int posy = 0);
    QString getNom() const { return m_name; }
    QString getNomArr() const { return m_name_arr; }
    int getMapX() const { return m_maparrX; }
    int getMapY() const { return m_maparrY; }
    int getMapZ() const { return m_maparrZ; }
    Dir getLargage() const { return m_largage; }
    void setNom(QString const& name) { m_name = name; }
    void setNomArr(QString const& name_arr) { m_name_arr = name_arr; }
    void setMapX(int maparrX) { m_maparrX = maparrX; }
    void setMapY(int maparrY) { m_maparrY = maparrY; }
    void setMapZ(int maparrZ) { m_maparrZ = maparrZ; }
    void setLargage(Dir largage) { m_largage = largage; }
    int getLargageX() const { return m_largageX; }
    int getLargageY() const { return m_largageY; }

private :

    QString m_name;
    QString m_name_arr;
    int m_maparrX;
    int m_maparrY;
    int m_maparrZ;
    Dir m_largage;
    int m_largageX;
    int m_largageY;
};

#endif // TRANSPORTEUR_H
