#include "map/computePath.h"


bool caseExiste(int x, int y)
{
    return x >= 0 && y >= 0 && x < NBR_CASES_L && y < NBR_CASES_H;
}

QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<UnChemin>parents)
{
    QVector<UnChemin>enfants;
    int x,y;

    for(int i = 0; i < parents.size(); i++)
    {
        x = parents[i].lacase().x();
        y = parents[i].lacase().y();

        if(QPoint(x,y) == arr)
        {
            return parents[i].chemin();
        }

        if(y % 2 == 0)
        {
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 0, 1));
                }
            }
            if(x-1 >= 0 && y-1 >= 0)
            {
                if(!casemarchees[x-1] [y-1])
                {
                    casemarchees[x-1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG,-1, -1));
                }
            }
            if(x-1 >= 0 && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x-1] [y+1])
                {
                    casemarchees[x-1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, -1, 1));
                }
            }
        }
        else
        {
            if(x+1 < NBR_CASES_L && y-1 >= 0)
            {
                if(!casemarchees[x+1] [y-1])
                {
                    casemarchees[x+1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 1, -1));
                }
            }
            if(x+1 < NBR_CASES_L && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x+1] [y+1])
                {
                    casemarchees[x+1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 1, 1));
                }
            }
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, 0, 1));
                }
            }
        }
        if(y+2 < NBR_CASES_H)
        {
            if(!casemarchees[x] [y+2])
            {
                casemarchees[x] [y+2] = true;
                enfants.push_back(UnChemin(parents[i], B, 0, 2));
            }
        }
        if(y-2 >= 0)
        {
            if(!casemarchees[x] [y-2])
            {
                casemarchees[x] [y-2] = true;
                enfants.push_back(UnChemin(parents[i], O, 0, -2));
            }
        }
        if(x+1 < NBR_CASES_L)
        {
            if(!casemarchees[x+1] [y])
            {
                casemarchees[x+1] [y] = true;
                enfants.push_back(UnChemin(parents[i], D, 1, 0));
            }
        }
        if(x-1 >= 0)
        {
            if(!casemarchees[x-1] [y])
            {
                casemarchees[x-1] [y] = true;
                enfants.push_back(UnChemin(parents[i], G, -1, 0));
            }
        }
    }

    QQueue<Dir>vide;

    if(enfants.isEmpty())
        return vide;
    else
        return faitechem(casemarchees, arr, enfants);
}


QQueue<Dir> faitechemCombat(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<UnChemin>parents, int max_dep)
{
    QVector<UnChemin>enfants;
    int x,y;
    if(max_dep > 0)
    {
        for(int i = 0; i < parents.size(); i++)
        {
            x = parents[i].lacase().x();
            y = parents[i].lacase().y();

            if(QPoint(x,y) == arr)
            {
                return parents[i].chemin();
            }

            if(y % 2 == 0)
            {
                if(y-1 >= 0)
                {
                    if(!casemarchees[x] [y-1])
                    {
                        casemarchees[x] [y-1] = true;
                        enfants.push_back(UnChemin(parents[i], OD, 0, -1));
                    }
                }
                if(y+1 < NBR_CASES_H)
                {
                    if(!casemarchees[x] [y+1])
                    {
                        casemarchees[x] [y+1] = true;
                        enfants.push_back(UnChemin(parents[i], BD, 0, 1));
                    }
                }
                if(x-1 >= 0 && y-1 >= 0)
                {
                    if(!casemarchees[x-1] [y-1])
                    {
                        casemarchees[x-1] [y-1] = true;
                        enfants.push_back(UnChemin(parents[i], OG,-1, -1));
                    }
                }
                if(x-1 >= 0 && y+1 < NBR_CASES_H)
                {
                    if(!casemarchees[x-1] [y+1])
                    {
                        casemarchees[x-1] [y+1] = true;
                        enfants.push_back(UnChemin(parents[i], BG, -1, 1));
                    }
                }
            }
            else
            {
                if(x+1 < NBR_CASES_L && y-1 >= 0)
                {
                    if(!casemarchees[x+1] [y-1])
                    {
                        casemarchees[x+1] [y-1] = true;
                        enfants.push_back(UnChemin(parents[i], OD, 1, -1));
                    }
                }
                if(x+1 < NBR_CASES_L && y+1 < NBR_CASES_H)
                {
                    if(!casemarchees[x+1] [y+1])
                    {
                        casemarchees[x+1] [y+1] = true;
                        enfants.push_back(UnChemin(parents[i], BD, 1, 1));
                    }
                }
                if(y-1 >= 0)
                {
                    if(!casemarchees[x] [y-1])
                    {
                        casemarchees[x] [y-1] = true;
                        enfants.push_back(UnChemin(parents[i], OG, 0, -1));
                    }
                }
                if(y+1 < NBR_CASES_H)
                {
                    if(!casemarchees[x] [y+1])
                    {
                        casemarchees[x] [y+1] = true;
                        enfants.push_back(UnChemin(parents[i], BG, 0, 1));
                    }
                }
            }
        }
    }

    QQueue<Dir>vide;

    if(enfants.isEmpty())
        return vide;
    else
        return faitechemCombat(casemarchees, arr, enfants, max_dep-1);
}


QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<UnChemin>parents, QPoint *arrivee)//on doit arriver à une des cases
{
    QVector<UnChemin>enfants;
    int x,y;

    for(int i = 0; i < parents.size(); i++)
    {
        x = parents[i].lacase().x();
        y = parents[i].lacase().y();

        if(arrivees.contains(QPoint(x,y)))
        {
            arrivee->setX(x);
            arrivee->setY(y);
            return parents[i].chemin();
        }

        if(y % 2 == 0)
        {
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 0, 1));
                }
            }
            if(x-1 >= 0 && y-1 >= 0)
            {
                if(!casemarchees[x-1] [y-1])
                {
                    casemarchees[x-1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG,-1, -1));
                }
            }
            if(x-1 >= 0 && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x-1] [y+1])
                {
                    casemarchees[x-1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, -1, 1));
                }
            }
        }
        else
        {
            if(x+1 < NBR_CASES_L && y-1 >= 0)
            {
                if(!casemarchees[x+1] [y-1])
                {
                    casemarchees[x+1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 1, -1));
                }
            }
            if(x+1 < NBR_CASES_L && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x+1] [y+1])
                {
                    casemarchees[x+1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 1, 1));
                }
            }
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, 0, 1));
                }
            }
        }
        if(y+2 < NBR_CASES_H)
        {
            if(!casemarchees[x] [y+2])
            {
                casemarchees[x] [y+2] = true;
                enfants.push_back(UnChemin(parents[i], B, 0, 2));
            }
        }
        if(y-2 >= 0)
        {
            if(!casemarchees[x] [y-2])
            {
                casemarchees[x] [y-2] = true;
                enfants.push_back(UnChemin(parents[i], O, 0, -2));
            }
        }
        if(x+1 < NBR_CASES_L)
        {
            if(!casemarchees[x+1] [y])
            {
                casemarchees[x+1] [y] = true;
                enfants.push_back(UnChemin(parents[i], D, 1, 0));
            }
        }
        if(x-1 >= 0)
        {
            if(!casemarchees[x-1] [y])
            {
                casemarchees[x-1] [y] = true;
                enfants.push_back(UnChemin(parents[i], G, -1, 0));
            }
        }
    }

    QQueue<Dir>vide;

    if(enfants.isEmpty())
        return vide;
    else
        return faitechem(casemarchees, arrivees, enfants, arrivee);
}


QQueue<Dir> faitechemCombat(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<UnChemin>parents, QPoint *arrivee)//on doit arriver à une des cases
{
    QVector<UnChemin>enfants;
    int x,y;

    for(int i = 0; i < parents.size(); i++)
    {
        x = parents[i].lacase().x();
        y = parents[i].lacase().y();

        if(arrivees.contains(QPoint(x,y)))
        {
            arrivee->setX(x);
            arrivee->setY(y);
            return parents[i].chemin();
        }

        if(y % 2 == 0)
        {
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 0, 1));
                }
            }
            if(x-1 >= 0 && y-1 >= 0)
            {
                if(!casemarchees[x-1] [y-1])
                {
                    casemarchees[x-1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG,-1, -1));
                }
            }
            if(x-1 >= 0 && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x-1] [y+1])
                {
                    casemarchees[x-1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, -1, 1));
                }
            }
        }
        else
        {
            if(x+1 < NBR_CASES_L && y-1 >= 0)
            {
                if(!casemarchees[x+1] [y-1])
                {
                    casemarchees[x+1] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OD, 1, -1));
                }
            }
            if(x+1 < NBR_CASES_L && y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x+1] [y+1])
                {
                    casemarchees[x+1] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BD, 1, 1));
                }
            }
            if(y-1 >= 0)
            {
                if(!casemarchees[x] [y-1])
                {
                    casemarchees[x] [y-1] = true;
                    enfants.push_back(UnChemin(parents[i], OG, 0, -1));
                }
            }
            if(y+1 < NBR_CASES_H)
            {
                if(!casemarchees[x] [y+1])
                {
                    casemarchees[x] [y+1] = true;
                    enfants.push_back(UnChemin(parents[i], BG, 0, 1));
                }
            }
        }
    }

    QQueue<Dir>vide;

    if(enfants.isEmpty())
        return vide;
    else
        return faitechemCombat(casemarchees, arrivees, enfants, arrivee);
}

Dir vaAdroite(Dir centre)
{
    Dir droite = O;
    switch(centre)
    {
    case O:
        droite = OD;
        break;
    case OD:
        droite = D;
        break;
    case D:
        droite = BD;
        break;
    case BD:
        droite = B;
        break;
    case B:
        droite = BG;
        break;
    case BG:
        droite = G;
        break;
    case G:
        droite = OG;
        break;
    case OG:
        droite = O;
        break;
    default:
        break;
    }
    return droite;
}

Dir vaAgauche(Dir centre)
{
    Dir gauche = O;
    switch(centre)
    {
    case O:
        gauche = OG;
        break;
    case OG:
        gauche = G;
        break;
    case G:
        gauche = BG;
        break;
    case BG:
        gauche = B;
        break;
    case B:
        gauche = BD;
        break;
    case BD:
        gauche = D;
        break;
    case D:
        gauche = OD;
        break;
    case OD:
        gauche = O;
        break;
    default:
        break;
    }
    return gauche;
}

void case_suivante(int *x, int *y, Dir dir)
{
    switch(dir)
    {
    case O:
        (*y)-=2;
        break;
    case B:
        (*y)+=2;
        break;
    case D:
        (*x)++;
        break;
    case G:
        (*x)--;
        break;
    default:
        case_suivante_simple(x, y, dir);
    }
}

void case_suivante_simple(int *x, int *y, Dir dir)
{
    if((*y) % 2 == 0)
    {
        if(dir == BG)
        {
            (*x)--;
            (*y)++;
        }
        else if(dir == BD)
        {
            (*y)++;
        }
        else if(dir == OG)
        {
            (*x)--;
            (*y)--;
        }
        else if(dir == OD)
        {
            (*y)--;
        }
    }
    else
    {
        if(dir == BG)
        {
            (*y)++;
        }
        else if(dir == BD)
        {
            (*x)++;
            (*y)++;
        }
        else if(dir == OG)
        {
            (*y)--;
        }
        else if(dir == OD)
        {
            (*x)++;
            (*y)--;
        }
    }
}

int valeur(Dir dir)
{
    if(dir == O || dir == B || dir == D || dir == G)
        return 2;
    else
        return 1;
}

