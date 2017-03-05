#include "additionalActions/actionObjets.h"

bool operator<(QPoint const &a, QPoint const& b)
{
    if(a.y() < b.y())
        return true;
    else if(a.y() > b.y())
        return false;
    if(a.x() < b.x())
        return true;
    else
        return false;
}

bool chargeMap(Decors *decors, int cooX, int cooY,int cooZ, Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H])
{
    QFile fichier("maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");
    if(!fichier.exists())
        return false;

    if(fichier.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&fichier);
        qint16 num;

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                for(int x = 0; x < 3; x++)
                {
                    stream >> num;
                    objets[x] [i] [j] = decors->objet(num);
                }
            }
        }
        return true;
    }
    else
        return false;
}

bool mapexiste(int x, int y, int z)
{
    if(x < 0 || y < 0 || z < 0 || x > NBR_DE_MAPS_X-1 || y > NBR_DE_MAPS_Y-1 || z > NBR_DE_MAPS_Z-1)
        return false;
    QFile fichier("maps/["+QString::number(x)+";"+QString::number(y)+";"+QString::number(z)+"].bin");
    return fichier.exists();
}
