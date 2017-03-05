#include "additionalActions/rechercheChemin.h"


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


void portee_aux(int cases_intraversables[NBR_CASES_L] [NBR_CASES_H],bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int x, int y, bool adroite, bool agauche, Dir dir,int max_portee)
{
    int xc = x;
    int yc = y;
    int xd = x;
    int yd = y;
    int xg = x;
    int yg = y;
    case_suivante(&xc,&yc,dir);
    case_suivante(&xd,&yd,vaAdroite(dir));
    case_suivante(&xg,&yg,vaAgauche(dir));
    if(caseExiste(xc,yc))
    {
        bool droite = false;
        bool gauche = false;
        if(cases_intraversables[xc][yc] < 2)
        {
            if(caseExiste(xd,yd) && adroite)
            {
                if(cases_intraversables[xd][yd]  < 2)
                {
                    droite = true;
                }
            }
            if(caseExiste(xg,yg) && agauche)
            {
                if(cases_intraversables[xg][yg] < 2)
                {
                    gauche = true;
                }
            }
            if(dir == O)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, true, droite, false, false, false, false, false, gauche, max_portee-2);
            }
            else if(dir == OD)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, gauche, true, droite, false, false, false, false, false, max_portee-1);
            }
            else if(dir == D)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, false, gauche, true, droite, false, false, false, false, max_portee-2);
            }
            else if(dir == BD)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, false, false, gauche, true, droite, false, false, false, max_portee-1);
            }
            else if(dir == B)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, false, false, false, gauche, true, droite, false, false, max_portee-2);
            }
            else if(dir == BG)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, false, false, false, false, gauche, true, droite, false, max_portee-1);
            }
            else if(dir == G)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, false, false, false, false, false, gauche, true, droite, max_portee-2);
            }
            else if(dir == OG)
            {
                portee(cases_intraversables, cases_ateignables, xc,yc, droite, false, false, false, false, false, gauche, true, max_portee-1);
            }
        }
    }
}


void portee(int cases_intraversables[NBR_CASES_L] [NBR_CASES_H],bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, bool o, bool od, bool d, bool bd, bool b, bool bg, bool g, bool og, int max_portee)
{
    if(max_portee < 0)
        return;
    cases_ateignables[xdep][ydep] = true;
    if(max_portee <= 0)
        return;
    if(o)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,od,og,O, max_portee);
    }
    if(od)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,d,o,OD, max_portee+1);
    }
    if(d)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,bd,od,D, max_portee);
    }
    if(bd)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,b,d,BD, max_portee);
    }
    if(b)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,bg,bd,B, max_portee);
    }
    if(bg)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,g,b,BG, max_portee);
    }
    if(g)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,og,bg,G, max_portee);
    }
    if(og)
    {
        portee_aux(cases_intraversables, cases_ateignables, xdep,ydep,o,g,OG, max_portee);
    }
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


void portee2_aux(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee, Dir dir)
{
    int x;
    int y;
    int x2;
    int y2;
    int x3;
    int y3;
    int portee_restante;
    int j;
    bool cont;
    bool ok;
    //bool ok3;
    for(int i = NBR_CASES_H+NBR_CASES_L; i > 0; i--)
    {
        x = xdep;
        y = ydep;
        cont = true;
        portee_restante = max_portee;
        ok = true;
        //ok3 = true;
        while(cont)
        {
            j = 0;
            while(cont && j < i)
            {
                case_suivante(&x,&y,dir);
                portee_restante -= valeur(dir);
                if(!caseExiste(x,y) || portee_restante < 0)
                {
                    cont = false;
                }
                else if(cases_pleines[x][y] == 2)
                {
                    cont = false;
                }
                else
                {
                    cases_ateignables[x][y] = true;
                    j++;
                }
            }
            if(cont)
            {
                x2 = x;
                y2 = y;
                //x3 = x;
                //y3 = y;
                case_suivante(&x2,&y2,vaAdroite(vaAdroite(dir)));
                //case_suivante(&x3,&y3,vaAdroite(vaAdroite(vaAdroite(dir))));
                /*if(!caseExiste(x3,y3))
                {
                    ok3 = false;
                }
                else if(cases_pleines[x3][y3] == 2)
                {
                    ok3 = false;
                }
                if(ok3)
                {
                    cases_ateignables[x3][y3] = true;
                }*/
                if(!caseExiste(x2,y2))
                {
                    ok = false;
                }
                else if(cases_pleines[x2][y2] == 2)
                {
                    ok = false;
                }
                case_suivante(&x,&y,vaAdroite(dir));
                portee_restante -= valeur(vaAdroite(dir));
                if(!caseExiste(x,y) || portee_restante < 0)
                {
                    cont = false;
                }
                else if(cases_pleines[x][y] == 2)
                {
                    cont = false;
                }
                else if(true)
                {
                    cases_ateignables[x][y] = true;
                }
            }
        }
    }


    for(int i = NBR_CASES_H+NBR_CASES_L; i > 0; i--)
    {
        x = xdep;
        y = ydep;
        cont = true;
        portee_restante = max_portee;
        ok = true;
        //ok3 = true;
        while(cont)
        {
            j = 0;
            while(cont && j < i)
            {
                case_suivante(&x,&y,dir);
                portee_restante -= valeur(dir);
                if(!caseExiste(x,y) || portee_restante < 0)
                {
                    cont = false;
                }
                else if(cases_pleines[x][y] == 2)
                {
                    cont = false;
                }
                else
                {
                    cases_ateignables[x][y] = true;
                    j++;
                }
            }
            if(cont)
            {
                x2 = x;
                y2 = y;
                //x3 = x;
                //y3 = y;
                case_suivante(&x2,&y2,vaAgauche(vaAgauche(dir)));
                //case_suivante(&x3,&y3,vaAgauche(vaAgauche(vaAgauche(dir))));
                /*if(!caseExiste(x3,y3))
                {
                    ok3 = false;
                }
                else if(cases_pleines[x3][y3] == 2)
                {
                    ok3 = false;
                }
                if(ok3)
                {
                    cases_ateignables[x3][y3] = true;
                }*/
                if(!caseExiste(x2,y2))
                {
                    ok = false;
                }
                else if(cases_pleines[x2][y2] == 2)
                {
                    ok = false;
                }
                case_suivante(&x,&y,vaAgauche(dir));
                portee_restante -= valeur(vaAgauche(dir));
                if(!caseExiste(x,y) || portee_restante < 0)
                {
                    cont = false;
                }
                else if(cases_pleines[x][y] == 2)
                {
                    cont = false;
                }
                else if(true)
                {
                    cases_ateignables[x][y] = true;
                }
            }
        }
    }
}

void portee2(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee)
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            cases_ateignables[i][j] = false;
        }
    }
    cases_ateignables[xdep][ydep] = true;
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, O);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, OD);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, D);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, BD);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, B);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, BG);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, G);
    portee2_aux(cases_pleines, cases_ateignables, xdep, ydep, max_portee, OG);
}

void portee3(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee)
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            cases_ateignables[i][j] = true;
        }
    }
}


void porteeNew(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee)
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            cases_ateignables[i][j] = true;
        }
    }
}





