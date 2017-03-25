#include "map/map.h"

Map::Map(Data *donnees_editeur,int cooX, int cooY, int cooZ)
{
    m_estEnregistree = true;
    m_undo = 0;
    m_donnees_editeur = donnees_editeur;
    m_cooX = cooX;
    m_cooY = cooY;
    m_cooZ = cooZ;
    charge("../data/maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");
    m_estEnregistree = true;
}

void Map::chargeMap(int x,int y,int z)
{
    m_undo = 0;
    m_cooX = x;
    m_cooY = y;
    m_cooZ = z;
    charge("../data/maps/["+QString::number(m_cooX)+";"+QString::number(m_cooY)+";"+QString::number(m_cooZ)+"].bin");
    m_estEnregistree = true;
}

void Map::charge(QString const& nomFichier)
{
    QFile fichier;
    fichier.setFileName(nomFichier);
    if(!fichier.exists())
    {
        nouvelleMap();
        return;
    }

    if(fichier.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&fichier);
        qint16 num;
        qint8 num2;
        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                for(int x = 0; x < 3; x++)
                {
                    stream >> num;
                    m_objets[x] [i] [j] = m_donnees_editeur->decor->objet(num);
                }
            }
        }

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream >> m_casepleines[i] [j];
                m_casepleinesCombat[i] [j] = m_casepleines[i] [j];
            }
        }
        QPoint p;

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < MAX_PAR_EQUIP; j++)
            {
                stream >> num2;
                p.setX((int)num2);
                stream >> num2;
                p.setY((int)num2);
                m_casescbt[i] [j] = p;
            }
        }
        QString texte;
        stream >> texte;

        fichier.close();

        QStringList liste = texte.split("/");

        m_fond = liste.front();
        liste.pop_front();

        while(liste[0] != "FINMUSIQUES")
        {
            m_musiques.push_back(liste[0]);
            liste.pop_front();
        }
        liste.pop_front();

        while(liste[0] != "FINMONSTRES")
        {
            m_monstres[liste[0]] = liste[1].toDouble();
            liste.pop_front();
            liste.pop_front();
        }

        if(liste.size() > 0)
            liste.pop_front();

        for(int i = 0; i < liste.size()-2; i+=8)
        {
             m_transpos[QPoint(liste[i+6].toInt(), liste[i+7].toInt())] = Gate(liste[i], liste[i+1], liste[i+2].toInt(), liste[i+3].toInt(), liste[i+4].toInt(), (Dir)liste[i+5].toInt(), liste[i+6].toInt(), liste[i+7].toInt());
        }
        charge_contours();
        if(m_undo != -1)
            QFile::remove("../data/maps/undo/"+QString::number(m_undo)+".bin");
    }
    else
    {
        qDebug() << "erreur d'ouverture de la map !";
        exit(1);
    }
}

bool Map::undo()
{
    if(m_undo > 1)
    {
        m_undo--;
        nouvelleMap();
        charge("../data/maps/undo/"+QString::number(m_undo)+".bin");
        //fichier.setFileName();
        return true;
    }
    return false;
}

void Map::nouvelleMap()
{
    m_estEnregistree = false;
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                m_objets[x] [i] [j] = m_donnees_editeur->decor->objet(0);
            }
        }
    }

    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casepleines[i] [j] = 0;
            m_casepleinesCombat[i] [j] = 0;
        }
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_casescbt[i] [j] = QPoint(-1,-1);
        }
    }
    m_fond = FOND_DEFAUT;
    m_musiques.clear();
    m_monstres.clear();
    m_transpos.clear();
}

bool Map::exist(int cooX,int cooY,int cooZ,int undo/*=-1*/)
{
    QFile fichier;
    if(undo != -1)
        fichier.setFileName("../data/maps/undo/"+QString::number(undo-1)+".bin");
    else
        fichier.setFileName("../data/maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");
    return fichier.exists();
}

void Map::casePleineDeMap(int cooX, int cooY, int cooZ, qint8 casesPleines[NBR_CASES_L] [NBR_CASES_H])
{
    QFile fichier;
    fichier.setFileName("../data/maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");
    if(!fichier.exists())
    {
        qDebug() << "erreur au chargement de la map d'à coté!";
        exit(1);
    }
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
                }
            }
        }

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream >> casesPleines[i] [j];
            }
        }

        fichier.close();
    }
    else
    {
        qDebug() << "erreur d'ouverture de la map !";
        exit(1);
    }
}


void Map::enregistre(bool undo/* = -1*/)
{
    QFile fichier;
    if(undo)
    {
        m_undo++;
        fichier.setFileName("../data/maps/undo/"+QString::number(undo)+".bin");
    }
    else
    {
        fichier.setFileName("../data/maps/["+QString::number(m_cooX)+";"+QString::number(m_cooY)+";"+QString::number(m_cooZ)+"].bin");
        m_estEnregistree = true;
    }

    if(fichier.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&fichier);
        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream << m_objets[0] [i] [j]->numero() << m_objets[1] [i] [j]->numero() << m_objets[2] [i] [j]->numero();
            }
        }

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream << m_casepleines[i] [j];
            }
        }

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < MAX_PAR_EQUIP; j++)
            {
                stream << (qint8) m_casescbt[i] [j].x() << (qint8) m_casescbt[i] [j].y();
            }
        }

        //et la chaine QString

        QString reste;

        reste += m_fond + '/';

        for(int i = 0; i < m_musiques.size(); i++)
        {
            reste += m_musiques[i] + '/';
        }

        reste += "FINMUSIQUES/";

        for(QMap<QString, double>::iterator it = m_monstres.begin(); it != m_monstres.end(); it++)
        {
            reste += it.key() + '/' + QString::number(it.value()) + '/';
        }

        reste += "FINMONSTRES/";

        for(QMap<QPoint, Gate>::const_iterator it = m_transpos.begin(); it != m_transpos.end(); it++)
        {
            reste += it.value().getNom();
            reste += '/';
            reste += it.value().getNomArr();
            reste += '/';
            reste += QString::number(it.value().getMapX());
            reste += '/';
            reste += QString::number(it.value().getMapY());
            reste += '/';
            reste += QString::number(it.value().getMapZ());
            reste += '/';
            reste += QString::number((int)it.value().getLargage());
            reste += '/';
            reste += QString::number(it.key().x());
            reste += '/';
            reste += QString::number(it.key().y());
            reste += '/';
        }
        stream << reste;
        fichier.close();
    }
}

void Map::coupable(QMap<QPoint, bool> *objetsCoupables)
{
    for(int i = CASESCACHEESX; i < NBR_CASES_L-CASESCACHEESX; i++)
    {
        for(int j = CASESCACHEESY; j < NBR_CASES_H-CASESCACHEESY; j++)
        {
            if(m_donnees_editeur->metiers->est_un_objet_coupable(m_objets[2][i][j]->numero()))
            {
                (*objetsCoupables)[QPoint(i,j)] = true;
            }
        }
    }
}

bool Map::estCaseDeDepart(int x,int y,int equipe)
{
    QPoint p(x,y);
    for(int i = 0; i < MAX_PAR_EQUIP;i++)
    {
        if(p == m_casescbt[equipe][i])
            return true;
    }
    return false;
}


QVector<QPoint> Map::cases_autour(QPoint const& p)
{
    QVector<QPoint>cases;

    if(!m_casepleines[p.x()-1] [p.y()])
        cases.push_back(QPoint(p.x()-1, p.y()));
    if(!m_casepleines[p.x()+1] [p.y()])
        cases.push_back(QPoint(p.x()+1, p.y()));
    if(!m_casepleines[p.x()] [p.y()-2])
        cases.push_back(QPoint(p.x(), p.y()-2));
    if(!m_casepleines[p.x()] [p.y()+2])
        cases.push_back(QPoint(p.x(), p.y()+2));
    if(p.y()%2==0)
    {
        if(!m_casepleines[p.x()-1] [p.y()+1])
            cases.push_back(QPoint(p.x()-1, p.y()+1));
        if(!m_casepleines[p.x()-1] [p.y()-1])
            cases.push_back(QPoint(p.x()-1, p.y()-1));
        if(!m_casepleines[p.x()] [p.y()+1])
            cases.push_back(QPoint(p.x(), p.y()+1));
        if(!m_casepleines[p.x()] [p.y()-1])
            cases.push_back(QPoint(p.x(), p.y()-1));
    }
    else
    {
        if(!m_casepleines[p.x()] [p.y()+1])
            cases.push_back(QPoint(p.x(), p.y()+1));
        if(!m_casepleines[p.x()] [p.y()-1])
            cases.push_back(QPoint(p.x(), p.y()-1));
        if(!m_casepleines[p.x()+1] [p.y()+1])
            cases.push_back(QPoint(p.x()+1, p.y()+1));
        if(!m_casepleines[p.x()+1] [p.y()-1])
            cases.push_back(QPoint(p.x()+1, p.y()-1));
    }

    return cases;
}

void Map::vide()
{
    videObjets();
    videCasesCombat();
    videCasesPleines();
    m_fond = "";
    m_musiques.clear();
    m_monstres.clear();
    m_transpos.clear();
}

void Map::videObjets()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                m_objets[x] [i] [j] = m_donnees_editeur->decor->objet(0);
            }
        }
    }
}

void Map::videCasesCombat()
{
    QPoint p(-1,-1);

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_casescbt[i] [j] = p;
        }
    }
}

void Map::videCasesPleines()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casepleines[i] [j] = 0;
            m_casepleinesCombat[i] [j] = 0;
        }
    }
}

QQueue<Dir> Map::calculchemin(QPoint const& dep, QPoint const& arr)
{
    bool casesmarchees[NBR_CASES_L] [NBR_CASES_H];
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(!m_casepleines[i] [j])
                casesmarchees[i] [j] = false;
            else
                casesmarchees[i] [j] = true;
        }
    }

    QVector <Path>leschem;
    leschem.push_back(Path(dep));

    return faitechem(casesmarchees, arr, leschem);

}

QQueue<Dir> Map::calculcheminJusquaLObjet(QPoint const& dep, QPoint const& position_objet, QPoint *arrivee)
{
    bool casesmarchees[NBR_CASES_L] [NBR_CASES_H];
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(!m_casepleines[i] [j])
                casesmarchees[i] [j] = false;
            else
                casesmarchees[i] [j] = true;
        }
    }
    QVector <Path>leschem;
    leschem.push_back(Path(dep));
    QVector<QPoint>arrivees = cases_autour(position_objet);



    return faitechem(casesmarchees, arrivees, leschem, arrivee);
}


QQueue<Dir> Map::calculcheminCombat(QPoint const& dep, QPoint const& arr, int max_dep)
{
    bool casesmarchees[NBR_CASES_L] [NBR_CASES_H];
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(!m_casepleinesCombat[i] [j])
                casesmarchees[i] [j] = false;
            else
                casesmarchees[i] [j] = true;
        }
    }

    QVector <Path>leschem;
    leschem.push_back(Path(dep));

    return faitechemCombat(casesmarchees, arr, leschem, max_dep);

}

QQueue<Dir> Map::calculcheminJusquaLObjetCombat(QPoint const& dep, QPoint const& position_objet, QPoint *arrivee)
{
    bool casesmarchees[NBR_CASES_L] [NBR_CASES_H];
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(!m_casepleinesCombat[i] [j])
                casesmarchees[i] [j] = false;
            else
                casesmarchees[i] [j] = true;
        }
    }
    QVector <Path>leschem;
    leschem.push_back(Path(dep));
    QVector<QPoint>arrivees = cases_autour(position_objet);



    return faitechemCombat(casesmarchees, arrivees, leschem, arrivee);
}

void Map::setCasePleine(int i,int j,int value)
{
    m_estEnregistree = false;
    m_casepleines[i][j] = value;
    m_casepleinesCombat[i][j] = value;
}

void Map::setCasePleineCombat(int i,int j,int value)
{
    m_casepleinesCombat[i][j] = value;
}

void Map::charge_contours()
{
    m_estEnregistree = false;
    for(int i = 0; i < (NBR_CASES_L-CASESCACHEESX)*2; i++)
    {
        m_haut[i] = false;
        m_bas[i] = false;
    }

    for(int i = 0; i <= NBR_CASES_H-CASESCACHEESY*2; i++)
    {
        m_gauche[i] = false;
        m_droite[i] = false;
    }

    qint8 casesPleines[NBR_CASES_L] [NBR_CASES_H];
    if(Map::exist(m_cooX, m_cooY-1, m_cooZ))
    {
        casePleineDeMap(m_cooX,m_cooY-1,m_cooZ,casesPleines);
        for(int i = 0; i < NBR_CASES_L-CASESCACHEESX*2; i++)
        {
            if(!m_casepleines[i+CASESCACHEESX][CASESCACHEESY] && !casesPleines[i+CASESCACHEESX][NBR_CASES_H-CASESCACHEESY-1])
            {
                m_haut[2*i] = true;
            }
            if(!m_casepleines[i+CASESCACHEESX][CASESCACHEESY+1] && !casesPleines[i+CASESCACHEESX][NBR_CASES_H-CASESCACHEESY])
            {
                m_haut[2*i+1] = true;
            }
        }
    }
    if(Map::exist(m_cooX, m_cooY+1, m_cooZ))
    {
        casePleineDeMap(m_cooX,m_cooY+1,m_cooZ,casesPleines);
        for(int i = 0; i < NBR_CASES_L-CASESCACHEESX*2; i++)
        {
            if(!casesPleines[i+CASESCACHEESX][CASESCACHEESY] && !m_casepleines[i+CASESCACHEESX] [NBR_CASES_H-CASESCACHEESY-1])
            {
                m_bas[2*i] = true;
            }
            if(!casesPleines[i+CASESCACHEESX][CASESCACHEESY+1] && !m_casepleines[i+CASESCACHEESX] [NBR_CASES_H-CASESCACHEESY])
            {
                m_bas[2*i+1] = true;
            }
        }
    }
    if(Map::exist(m_cooX-1, m_cooY, m_cooZ))
    {
        casePleineDeMap(m_cooX-1,m_cooY,m_cooZ,casesPleines);
        for(int j = 0; j < NBR_CASES_H-CASESCACHEESY*2+1; j++)
        {
            if(!m_casepleines[CASESCACHEESX][CASESCACHEESY+j] && !casesPleines[NBR_CASES_L-CASESCACHEESX-1][CASESCACHEESY+j])
            {
                m_gauche[j] = true;
            }
        }
    }
    if(Map::exist(m_cooX+1, m_cooY, m_cooZ))
    {
        casePleineDeMap(m_cooX+1,m_cooY,m_cooZ,casesPleines);
        for(int j = 0; j < NBR_CASES_H-CASESCACHEESY*2+1; j++)
        {
            if(!casesPleines[CASESCACHEESX][CASESCACHEESY+j] && !m_casepleines[NBR_CASES_L-CASESCACHEESX-1] [CASESCACHEESY+j])
            {
                m_droite[j] = true;
            }
        }
    }
}

QPoint Map::case_haut(QPoint lacase)
{
    int actuelle = (lacase.x()-CASESCACHEESX)*2;
    if(lacase.y() == CASESCACHEESY+1)
    {
        actuelle++;
    }
    if(actuelle < 0)
        actuelle = 0;
    else if(actuelle > (NBR_CASES_L-CASESCACHEESX)*2-1)
        actuelle = (NBR_CASES_L-CASESCACHEESX)*2-1;
    int adroite = actuelle, agauche = actuelle, trouve = -1;
    while(trouve == -1 && (agauche >= 0 || adroite < (NBR_CASES_L-CASESCACHEESX)*2))
    {
        if(adroite < (NBR_CASES_L-CASESCACHEESX)*2 && m_haut[adroite])
            trouve = adroite;
        else if(agauche >= 0 && m_haut[agauche])
            trouve = agauche;
        else
        {
            agauche--;
            adroite++;
        }
    }
    QPoint p(-1,-1);
    if(trouve != -1)
    {
        p.setX(CASESCACHEESX+trouve/2);
        p.setY(CASESCACHEESY+trouve%2);
    }
    return p;
}

QPoint Map::case_bas(QPoint lacase)
{
    int actuelle = (lacase.x()-CASESCACHEESX)*2;
    if(lacase.y() == NBR_CASES_H-CASESCACHEESY)
    {
        actuelle++;
    }
    if(actuelle < 0)
        actuelle = 0;
    else if(actuelle > (NBR_CASES_L-CASESCACHEESX)*2-1)
        actuelle = (NBR_CASES_L-CASESCACHEESX)*2-1;
    int adroite = actuelle, agauche = actuelle, trouve = -1;
    while(trouve == -1 && (agauche >= 0 || adroite < (NBR_CASES_L-CASESCACHEESX)*2))
    {
        if(adroite < (NBR_CASES_L-CASESCACHEESX)*2 && m_bas[adroite])
            trouve = adroite;
        else if(agauche >= 0 && m_bas[agauche])
            trouve = agauche;
        else
        {
            agauche--;
            adroite++;
        }
    }
    QPoint p(-1,-1);
    if(trouve != -1)
    {
        p.setX(CASESCACHEESX+trouve/2);
        p.setY(NBR_CASES_H-CASESCACHEESY-1+trouve%2);
    }
    return p;
}

QPoint Map::case_gauche(QPoint lacase)
{
    int actuelle = lacase.y()-CASESCACHEESY;
    if(actuelle < 0)
        actuelle = 0;
    else if(actuelle > NBR_CASES_H-CASESCACHEESY*2)
        actuelle = NBR_CASES_H-CASESCACHEESY*2;
    int enhaut = actuelle, enbas = actuelle, trouve = -1;
    while(trouve == -1 && (enhaut > -1 || enbas <= NBR_CASES_H-CASESCACHEESY*2))
    {
        if(enhaut > -1 && m_gauche[enhaut] && enhaut > -1)
            trouve = enhaut;
        else if(enbas <= NBR_CASES_H-CASESCACHEESY*2 && m_gauche[enbas] && enbas <= NBR_CASES_H-CASESCACHEESY*2)
                trouve = enbas;
        enhaut--;
        enbas++;
    }
    QPoint p(-1,-1);
    if(trouve != -1)
    {
        p.setX(CASESCACHEESX);
        p.setY(CASESCACHEESY+trouve);
    }
    return p;
}

QPoint Map::case_droite(QPoint lacase)
{
    int actuelle = lacase.y()-CASESCACHEESY;
    if(actuelle < 0)
        actuelle = 0;
    else if(actuelle > NBR_CASES_H-CASESCACHEESY*2)
        actuelle = NBR_CASES_H-CASESCACHEESY*2;
    int enhaut = actuelle, enbas = actuelle, trouve = -1;
    while(trouve == -1 && (enhaut >= 0 || enbas <= NBR_CASES_H-CASESCACHEESY*2))
    {
        if(enhaut >= 0 && m_droite[enhaut] && enhaut >= 0)
            trouve = enhaut;
        else if(enbas <= NBR_CASES_H-CASESCACHEESY*2 && m_droite[enbas] && enbas <= NBR_CASES_H-CASESCACHEESY*2)
            trouve = enbas;
        else
        {
            enhaut--;
            enbas++;
        }
    }
    QPoint p(-1,-1);
    if(trouve != -1)
    {
        p.setX(NBR_CASES_L-CASESCACHEESX-1);
        p.setY(CASESCACHEESY+trouve);
    }
    return p;
}

QPoint Map::posDep(int equipe)
{
    QPoint p(-1,-1);
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_casescbt[equipe][i] != p)
            return m_casescbt[equipe][i];
    }
    return p;
}

void Map::initialisePortee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int min_portee, int max_portee)
{
    int cases_ateignables2[NBR_CASES_L][NBR_CASES_H];
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            cases_ateignables2[i][j] = 0;
        }
    }
    QList<Point>cases;
    cases.append(Point(xdep,ydep,0));
    int x,y,portee,x2,y2;
    while(!cases.isEmpty())
    {
        x = cases.front().x;
        y = cases.front().y;
        portee = cases.front().z;
        cases.pop_front();

        if(portee > max_portee)
            break;
        else if(portee >= min_portee)
            cases_ateignables2[x][y] = 1;//on peut tirer dessus
        else
            cases_ateignables2[x][y] = 2;// on ne peut pas tirer dessus mais on n'y revient pas dans la suite de l'algo

        x2=x;
        y2=y;
        case_suivante_simple(&x2,&y2,OD);
        if(caseExiste(x2,y2) && !cases_ateignables2[x2][y2])
            cases.push_back(Point(x2,y2,portee+1));
        x2=x;
        y2=y;
        case_suivante_simple(&x2,&y2,BG);
        if(caseExiste(x2,y2) && !cases_ateignables2[x2][y2])
            cases.push_back(Point(x2,y2,portee+1));
        x2=x;
        y2=y;
        case_suivante_simple(&x2,&y2,BD);
        if(caseExiste(x2,y2) && !cases_ateignables2[x2][y2])
            cases.push_back(Point(x2,y2,portee+1));
        x2=x;
        y2=y;
        case_suivante_simple(&x2,&y2,OG);
        if(caseExiste(x2,y2) && !cases_ateignables2[x2][y2])
            cases.push_back(Point(x2,y2,portee+1));

    }

    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            cases_ateignables[i][j] = (cases_ateignables2[i][j] == 1) && (m_casepleines[i][j] == 0);
        }
    }
}

void Map::calculPortee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int min_portee, int max_portee)
{
    // on créer une map avec des dimentions différentes
    int lcase = 40,hcase = 40;
    int mlcase = lcase/2;
    int mhcase = hcase/2;
    int x = cposx(xdep,ydep,lcase,true);
    int y = cposy(ydep,hcase,true);

    initialisePortee(cases_ateignables,xdep,ydep,min_portee,max_portee);
    for(int i = 0; i < NBR_CASES_L;i++)
    {
        for(int j = 0;j < NBR_CASES_H; j++)
        {
            if(m_casepleines[i][j] == 2 && (i != xdep || j != ydep))
            {
                int x2 = cposx(i,j,lcase,true)-x;
                int y2 = cposy(j,hcase,true)-y;
                int d = x2*x2+y2*y2;
                double max = 0,min = 0;
                calculContoursCase(x2,y2,mlcase,mhcase,max,min);
                for(int i2 = 0; i2 < NBR_CASES_L;i2++)
                {
                    for(int j2 = 0;j2 < NBR_CASES_H; j2++)
                    {
                        if(cases_ateignables[i2][j2])
                        {
                            int x3 = cposx(i2,j2,lcase,true)-x,y3 = cposy(j2,hcase,true)-y;
                            if(d < x3*x3+y3*y3)// l'obstacle ne peut cacher que ce qu'il y a derrière lui
                            {
                                double angle = calculAngle(x3,y3);
                                if(auMilieu(min,max,angle,d))
                                {
                                    cases_ateignables[i2][j2] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int Map::cposx(int casex, int casey,int lcase,bool zoom)
{
    int mlcase = lcase/2;
    if(zoom)
        casex -= CASESCACHEESX;
    if(casey % 2 == 0)
    {
        return lcase*(casex);
    }
    else
    {
        return lcase*(casex)+mlcase;
    }
}

int Map::cposy(int casey, int hcase, bool zoom)
{
    int mhcase = hcase/2;
    if(zoom)
        casey -= CASESCACHEESY;
    return mhcase*(casey);
}

QPoint Map::ccase(int posx, int posy,int lmap,int hmap,int lcase,int hcase,bool zoom)
{
    int mhcase = hcase/2;
    int mlcase = lcase/2;
    QPoint lacase(-1,-1);
    if(mhcase == 0 || mlcase == 0)
        return lacase;

    if(zoom)
    {
        posx += CASESCACHEESX*lcase;
        posy += CASESCACHEESY*mhcase;
    }

    if((zoom && (posx > -CASESCACHEESX*lcase-1 && posx < lmap + CASESCACHEESX*lcase && posy > -CASESCACHEESY*mhcase-1 && posy < hmap + CASESCACHEESY*mhcase))
            || (!zoom && posx > 0 && posx < lmap && posy > 0 && posy < hmap))
    {
        double a = (double) mhcase/ (double) mlcase, bdroitem, bdroited;
        int i = 0, j = qCeil(NBR_CASES_H/2)-1;

        while(-mhcase + i*hcase - (int) ((double)(posx)*a) < posy)
        {
            i++;
        }

        bdroitem = (double)  i*hcase;

        while(j*hcase+mhcase+a*(double)posx > posy)
        {
            j--;
        }

        j++;

        bdroited = (double) j*hcase;

        lacase.setX((bdroitem-bdroited)/(2*a));
        lacase.setY( a*(double) lacase.x()+bdroited);

        if(lacase.x() == 0)
        {
            lacase.setX(-1);
            lacase.setY(-1);
        }
        else
        {
            lacase.setY( qRound((double) (lacase.y())/(double)  (mhcase))-1);

            if(lacase.y() % 2 == 0)
                lacase.setX( qRound((double) (lacase.x()-mhcase)/ (double)(lcase)));
            else
                lacase.setX((lacase.x()- hcase)/(lcase));
        }

    }
    else
    {
        lacase.setX(-1);
        lacase.setY(-1);
        return lacase;
    }
    if(lacase.x() < 0)
    {
        lacase.setX(-1);
        lacase.setY(-1);
    }
    else if(lacase.x() > NBR_CASES_L-1)
    {
        lacase.setX(-1);
        lacase.setY(-1);
    }
    if(lacase.y() < 0)
    {
        lacase.setX(-1);
        lacase.setY(-1);
    }
    else if(lacase.y() > NBR_CASES_H-1)
    {
        lacase.setX(-1);
        lacase.setY(-1);
    }
    return lacase;
}

QPoint Map::caseLibre()
{
    int x = 0;
    int y = 0;
    do
    {
        x = qrand()%NBR_CASES_L;
        y = qrand()%NBR_CASES_H;
    }while(m_casepleines[x][y] != 0);
    return QPoint(x,y);
}

MonsterModel *Map::nouveauMonstre()
{
    double total = 0;
    for(QMap<QString,double>::iterator it = m_monstres.begin(); it != m_monstres.end(); it++)
    {
        total += it.value();
    }
    if(total == 0)
        return 0;
    double rand = ((double)(qrand() % ((int)(total*1000))))/1000.0;
    for(QMap<QString,double>::iterator it = m_monstres.begin(); it != m_monstres.end(); it++)
    {
        total += it.value();
        if(total > rand)
            return m_donnees_editeur->ressources->getMonstre(it.key());
    }
    return m_donnees_editeur->ressources->getMonstre(m_monstres.lastKey());
}

double calculAngle(int x,int y)
{
   double pi = 3.1415926;
   double angle = 0;
   if(x == 0)
   {
       if(y > 0)
           angle = pi/2;
       else
           angle = -pi/2;
   }
   else
   {
       angle = atan(((double)y)/((double)x));
       if(x < 0)
           angle += pi;
   }
   return angle;
}

bool auMilieu(double petitAngle, double grandAngle, double milieu, int d)
{
    int dec = 5;
    double decalage = atan(((double)dec)/((double)d));
    double pi = 3.1415926;

    if((petitAngle -decalage < milieu && milieu < grandAngle+decalage) || (petitAngle -decalage  < milieu + 2*pi && milieu + 2*pi < grandAngle+decalage))
        return false;
    return true;
}

void calculContoursCase(int x,int y,int mlcase,int mhcase,double &max,double &min)
{
    QList<double>angles;
    angles.append(calculAngle(x+mlcase,y));
    angles.append(calculAngle(x-mlcase,y));
    angles.append(calculAngle(x,y+mhcase));
    angles.append(calculAngle(x,y-mhcase));
    droiteExtremes(angles,max,min);
}

void droiteExtremes(QList<double>droites,double &max,double &min)
{
    double pi = 3.1415926;
    qSort(droites.begin(),droites.end());
    int l = droites.length();
    for(int i = l-1; i > 0;i--)
    {
        if(droites.at(i)-droites.at(i-1) > pi)
        {
            max = droites.at(i);
            min = droites.at(i-1);
            return;
        }
    }
    min = droites.at(l-1);
    max = droites.at(0)+2*pi;
}

QMap<QPoint, Object *> Map::posCollectedResources()
{
    QMap<QPoint,Object*>collectedObjetcs;
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(m_donnees_editeur->metiers->est_un_objet_coupe(m_objets[i][j][2]->numero()))
            {
                collectedObjetcs[QPoint(i,j)] = m_objets[i][j][2];
            }
        }
    }
    return collectedObjetcs;
}

Dir orientation_vers_objet(QPoint const& pos, QPoint const& pos_obj)
{
    if(pos.y() == pos_obj.y()+2)
        return O;
    else if(pos.y() == pos_obj.y()-2)
        return B;
    else if(pos.y() == pos_obj.y() && pos.x() == pos_obj.x()+1)
        return G;
    else if(pos.y() == pos_obj.y() && pos.x() == pos_obj.x()-1)
        return D;
    else if(pos.y()%2==0)
    {
        if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()+1)
            return OD;
        else if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()-1)
            return BD;
        else if(pos.x() == pos_obj.x()+1 && pos.y() == pos_obj.y()+1)
            return OG;
        else
            return BG;
    }
    else
    {
        if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()+1)
            return OG;
        else if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()-1)
            return BG;
        else if(pos.x() == pos_obj.x()-1 && pos.y() == pos_obj.y()+1)
            return OD;
        else
            return BD;
    }
}
