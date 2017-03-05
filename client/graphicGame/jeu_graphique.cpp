#include "jeu_graphique.h"


Jeu_graphique::Jeu_graphique(const QSize &size, const QString &nom, Jeu2d *parent, Donnees_editeur *donneesediteur)
{
    m_posCaseVisee = QPoint(-1,-1);
    m_ancienne = QPoint(-1,-1);
    m_parent = parent;
    m_nom = nom;
    m_lmap = size.width();
    m_hmap = size.height();
    redi_case();
    m_donneesediteur = donneesediteur;
    QPen pen(QColor(200,200,200, 128));
    QPolygon p;
    QPixmap caseDep = QPixmap("../data/interface/caseDep.png").scaled(m_lcase, m_hcase);
    QPixmap casePortee = QPixmap("../data/interface/casePortee.png").scaled(m_lcase, m_hcase);
    for(int i=0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casesDep[i] [j] = addPixmap(caseDep);
            m_casesDep[i] [j]->setZValue(4);
            m_casesDep[i] [j]->setVisible(false);
            m_casesDep[i] [j]->setOpacity(0.5);

            m_casesPortee[i] [j] = addPixmap(casePortee);
            m_casesPortee[i] [j]->setZValue(4);
            m_casesPortee[i] [j]->setVisible(false);
            m_casesPortee[i] [j]->setOpacity(0.5);


            for(int x = 0; x < 2; x++)
            {
                m_lesobjets[x] [i] [j] = new ObjSurScene(this, m_lmap);
                m_lesobjets[x] [i] [j]->setVisible(false);
            }
            m_lesobjets[2] [i] [j] = new ObjSurScene(this, m_lmap, QPoint(i,j));
            m_lesobjets[2] [i] [j]->setVisible(false);

            m_lesobjets[0] [i] [j]->setZValue(1);
            m_lesobjets[1] [i] [j]->setZValue(2);
            m_lesobjets[2] [i] [j]->setZValue(j+4);
            m_grille[i] [j] = addPolygon(p, pen);
            m_grille[i] [j]->setZValue(3);
        }
    }
    //case combat rouge et bleu
    QPixmap casecbt1("../data/interface/casecbt0.png");
    QPixmap casecbt2("../data/interface/casecbt1.png");
    m_imgCaseVisee = addPixmap(casecbt2);
    m_imgCaseVisee->setZValue(5);
    m_imgCaseVisee->setVisible(false);
    m_imgCaseVisee->setOpacity(0.5);
    for(int j = 0; j < MAX_PAR_EQUIP; j++)
    {
        m_imgcasescbt[0] [j] = addPixmap(casecbt1);
        m_imgcasescbt[0] [j]->setZValue(4);
        m_imgcasescbt[0] [j]->setVisible(false);
        m_imgcasescbt[0] [j]->setOpacity(0.5);

        m_imgcasescbt[1] [j] = addPixmap(casecbt2);
        m_imgcasescbt[1] [j]->setZValue(4);
        m_imgcasescbt[1] [j]->setVisible(false);
        m_imgcasescbt[1] [j]->setOpacity(0.5);
    }
    //fin case combat
    m_fond = addPixmap(QPixmap());
    m_fond->setPos(0,0);
    grille();

    m_fleche = addPixmap(QPixmap());
    m_fleche->setZValue(4+NBR_CASES_H);
    m_posFleche = QPoint(-1,-1);
}

Jeu_graphique::~Jeu_graphique()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        delete i.value();
    }
    delete m_parent;
}

void Jeu_graphique::redi(QSize const& nouvelle, DataMap *dataMap)
{
    m_posCaseVisee = QPoint(-1,-1);
    m_lmap = nouvelle.width();
    m_hmap = nouvelle.height();
    redi_case();
    m_donneesediteur->redidecors(m_lcase,m_hcase);
    grille();
    QPixmap caseDep = QPixmap("../data/interface/caseDep.png").scaled(m_lcase, m_hcase);
    QPixmap casePortee = QPixmap("../data/interface/casePortee.png").scaled(m_lcase, m_hcase);
    QPixmap casecbt1 = QPixmap("../data/interface/casecbt0.png").scaled(m_lcase, m_hcase);
    QPixmap casecbt2 = QPixmap("../data/interface/casecbt1.png").scaled(m_lcase, m_hcase);

    for(QMap<QString,AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        i.value()->redi(m_lcase, m_hcase);
    }

    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        m_imgcasescbt[0] [i]->setPixmap(casecbt1);
        m_imgcasescbt[1] [i]->setPixmap(casecbt2);
    }

    m_imgCaseVisee->setPixmap(casecbt2);

    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casesDep[i] [j]->setPixmap(caseDep);
            m_casesDep[i] [j]->setPos(m_parent->dataMap()->cposx(i,j,m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(j,m_hcase,true)-m_mhcase);
            m_casesPortee[i] [j]->setPixmap(casePortee);
            m_casesPortee[i] [j]->setPos(m_parent->dataMap()->cposx(i,j,m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(j,m_hcase,true)-m_mhcase);

            for(int x = 0; x < 3; x++)
            {
                caseEgale(i, j, dataMap->objet(i,j,x), x);
                m_lesobjets[x] [i] [j]->redi(m_lmap);
            }
        }
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_imgcasescbt[i] [j]->setPos(m_parent->dataMap()->cposx(dataMap->caseCombat(i,j).x(),dataMap->caseCombat(i,j).y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(dataMap->caseCombat(i,j).y(),m_hcase,true)-m_mhcase);
        }
    }

    for(QMap<QPoint, QGraphicsPixmapItem*>::iterator i = m_lesimagestransports.begin(); i != m_lesimagestransports.end(); i++)
    {
        i.value()->setPixmap(QPixmap("../data/interface/transporteur.png").scaled(m_lcase, m_hcase));
        i.value()->setPos(m_parent->dataMap()->cposx(i.key().x(), i.key().y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(i.key().y(),m_hcase,true)-m_mhcase);
    }
    fondEgal(m_nomfond);
}

void Jeu_graphique::redi_case()
{
    m_lcase = m_lmap/((NBR_CASES_L-CASESCACHEESX*2)*2-1)*2;
    m_hcase = m_hmap/(NBR_CASES_H-CASESCACHEESY*2-1)*2;
    m_mlcase = m_lcase/2;
    m_mhcase = m_hcase/2;
}

void Jeu_graphique::grille()
{
    /*int posx, posy;
    QPolygon p;

    for(int i = CASESCACHEESX, m = NBR_CASES_L-CASESCACHEESX+1; i < m; i++)
    {
        for(int j = CASESCACHEESY; j < NBR_CASES_H-CASESCACHEESY+2; j++)
        {
            posx = m_parent->dataMap()->cposx(i, j,m_lcase);
            posy = m_parent->dataMap()->cposy(j,m_hcase);

            p.clear();
            p<<QPoint(posx, posy-m_mhcase)<<QPoint(posx+m_mlcase,posy)<<QPoint(posx, posy+m_mhcase)<<QPoint(posx-m_mlcase, posy);
            m_grille[i] [j]->setPolygon(p);
        }
    }*/
}

void Jeu_graphique::setCasepleine(int i, int j, int value)
{
    if(value == 0)
        m_grille[i] [j]->setVisible(true);
    else
        m_grille[i] [j]->setVisible(false);
}

void Jeu_graphique::chargeObjets(DataMap *dataMap)
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                caseEgale(i,j,dataMap->objet(i,j,x),x);
            }
        }
    }
}

void Jeu_graphique::charge(DataMap *dataMap)
{
    chargeObjets(dataMap);
    fondEgal(dataMap->fond());
    //ajouter transpos,etc
}

void Jeu_graphique::caseEgale(int i, int j, Objet *objet, int fond)
{
    if(objet == m_donneesediteur->decor->objet(0))
    {
        m_lesobjets[fond] [i] [j]->setVisible(false);
        m_lesobjets[fond] [i] [j]->inutile();
    }
    else
    {
        m_lesobjets[fond] [i] [j]->setPixmap(objet->image());
        m_lesobjets[fond] [i] [j]->setVisible(true);
        if(fond == 2)
        {
            m_lesobjets[fond] [i] [j]->setPos(m_parent->dataMap()->cposx(i,j,m_lcase,true)-m_lesobjets[fond] [i] [j]->pixmap().width()/2, m_parent->dataMap()->cposy(j,m_hcase,true)-m_lesobjets[fond] [i] [j]->pixmap().height()+m_hcase*ECART);
            if(objet->nom().isEmpty())
                m_lesobjets[fond] [i] [j]->inutile();
            else
                m_lesobjets[fond] [i] [j]->utile(objet->nom());
        }
        else
            m_lesobjets[fond] [i] [j]->setPos(m_parent->dataMap()->cposx(i,j,m_lcase,true)-m_lesobjets[fond] [i] [j]->pixmap().width()/2, m_parent->dataMap()->cposy(j,m_hcase,true)-m_lesobjets[fond] [i] [j]->pixmap().height()/2);
    }
}


void Jeu_graphique::updateObjet(int i,int j, Objet *objet)
{
    delete m_lesobjets[2] [i] [j];
    m_lesobjets[2] [i] [j] = new ObjSurScene(this, m_lmap, QPoint(i,j));
    m_lesobjets[2] [i] [j]->setZValue(j+4);
    caseEgale(i,j,objet,2);
}


void Jeu_graphique::ajouteChemin(QString const& nom, QQueue<Dir> const& chemin)
{
    m_persos[nom]->nouveauchemin(chemin);
}

void Jeu_graphique::nouvelle()
{
    for(int i=0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                caseEgale(i,j,m_donneesediteur->decor->objet(0), x);
            }
            m_grille[i] [j]->setVisible(true);
        }
    }

    for(QMap<QPoint, QGraphicsPixmapItem*>::iterator i = m_lesimagestransports.begin(); i != m_lesimagestransports.end(); i++)
    {
        removeItem(i.value());
        delete i.value();
    }
    m_lesimagestransports.clear();
}

void Jeu_graphique::ajouteTranspo(QPoint const& pos)
{
    m_lesimagestransports[pos] = addPixmap(QPixmap("../data/interface/transporteur.png").scaled(m_lcase, m_hcase));
    m_lesimagestransports[pos]->setPos(m_parent->dataMap()->cposx(pos.x(), pos.y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(pos.y(),m_hcase,true)-m_mhcase);
    m_lesimagestransports[pos]->setZValue(4);
}

QString Jeu_graphique::contientJoueur()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        if(i.value()->isUnderMouse())
        {
            return i.key();
        }
    }
    return "";
}

bool estdansScene(int x, int y)
{
    if(x < 0 || y < 0 || x > NBR_CASES_L-1 || y > NBR_CASES_H-1)
        return false;
    return true;
}

void Jeu_graphique::ajouteUnPerso(InfoPerVis perso)
{
    m_persos[perso.nom] = new AfficheJoueur(m_donneesediteur->ressources->getClasse(perso.classe) ,perso.nom, QSize(m_lcase, m_hcase), perso.posmap, this);
    this->addItem(m_persos[perso.nom]);
    if(perso.nom == m_nom)
        connect(m_persos[perso.nom], SIGNAL(estSurTranspo(QPoint)), m_parent, SLOT(VaChangerDeMap(QPoint)));
}

void Jeu_graphique::supprimeUnPerso(QString const& nom)
{
    delete m_persos[nom];
    m_persos.remove(nom);
}

void Jeu_graphique::changeDeMap(int largX, int largY)
{
    m_persos[m_nom]->changePos(largX, largY);
    QStringList asuprr;
    for(QMap<QString,AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        if(i.key() != m_nom)
        {
            asuprr.append(i.key());
        }
    }
    while(!asuprr.isEmpty())
    {
        supprimeUnPerso(asuprr.first());
        asuprr.pop_front();
    }
}

bool Jeu_graphique::contientTranspo(QPoint const& pos)
{
    return m_parent->dataMap()->contientTranspo(pos);
}

void Jeu_graphique::imagesuivante()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        i.value()->suivante();
    }
}

void Jeu_graphique::deplace(QString const& nom, const QQueue<Dir> &chem, Actions_personnage::DerniereAction action)
{
    if(m_parent->phase() == EnCombat && m_parent->monTour())
        effaceChemin();
    m_persos[nom]->nouveauchemin(chem, action);
}

void Jeu_graphique::fondEgal(const QString &nom)
{
    m_nomfond = nom;
    m_fond->setPixmap(QPixmap("../data/lesfonds/"+nom).scaled(m_lmap, m_hmap));
}

void Jeu_graphique::utileClique(QPoint const& pos)
{
    if(m_persos[m_nom]->isImobile())
    {
        m_parent->utileClique(pos);
    }
}

void Jeu_graphique::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    int x = mouseEvent->scenePos().x(), y = mouseEvent->scenePos().y();
    if(m_parent->phase() == HorsCombat)
    {
        for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->aide();
            else
                it.value()->desaide();
        }
        m_fleche->setVisible(false);
        m_posFleche.setX(-1);
        m_posFleche.setY(-1);
        if(x < m_mlcase)
        {
            m_posFleche = m_parent->dataMap()->case_gauche(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = G;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheg.png").scaled(QSize(50,75)));
                m_fleche->setPos(0, m_parent->dataMap()->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(x > m_lmap-m_mlcase)
        {
            m_posFleche = m_parent->dataMap()->case_droite(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = D;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/fleched.png").scaled(QSize(50,75)));
                m_fleche->setPos(m_lmap-m_fleche->pixmap().width(), m_parent->dataMap()->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(y < m_mhcase)
        {
            m_posFleche = m_parent->dataMap()->case_haut(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = O;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheo.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_parent->dataMap()->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, 0);
            }
        }
        else if(y > (int) ((double) m_hcase * (double) (NBR_CASES_H-CASESCACHEESY*2)/2))
        {
            m_posFleche = m_parent->dataMap()->case_bas(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = B;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheb.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_parent->dataMap()->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, m_hmap-m_fleche->pixmap().height());
            }
        }
    }
    else if(m_parent->phase() == EnPlacement)
    {
        for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->aide();
            else
                it.value()->desaide();
        }
    }
    else if(m_parent->phase() == EnCombat)
    {
        if(m_parent->sort())
        {
            m_posCaseVisee = QPoint(-1,-1);
            for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
            {
                if(it.value()->isUnderMouse())
                {
                    it.value()->aide();
                    m_posCaseVisee = it.value()->posALaFin();
                }
                else
                    it.value()->desaide();
            }
            if(m_posCaseVisee.x() == -1)
            {
                m_posCaseVisee = m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
            }
            if(caseExiste(m_posCaseVisee.x(),m_posCaseVisee.y()) && m_cases_ateignables[m_posCaseVisee.x()][m_posCaseVisee.y()])
            {
                m_imgCaseVisee->setVisible(true);
                m_imgCaseVisee->setPos(m_parent->dataMap()->cposx(m_posCaseVisee.x(),m_posCaseVisee.y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(m_posCaseVisee.y(),m_hcase,true)-m_mhcase);
            }
            else
            {
                m_posCaseVisee = QPoint(-1,-1);
                m_imgCaseVisee->setVisible(false);
            }
        }
        else
        {
            for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
            {
                if(it.value()->isUnderMouse())
                    it.value()->aide();
                else
                    it.value()->desaide();
            }
            if(m_parent->monTour() && m_persos[m_nom]->isImobile())
            {
                QPoint arrivee = m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
                if(arrivee.x() != -1)
                {
                    if(arrivee != m_ancienne)
                    {
                        effaceChemin();
                        m_ancienne = arrivee;
                        QQueue<Dir> chem = m_parent->dataMap()->calculcheminCombat(getJoueur(m_nom)->posALaFin(), arrivee, m_parent->getPerso()->getPCCombat());
                        if(!chem.isEmpty())
                        {
                            afficheChemin(getJoueur(m_nom)->posALaFin(), chem);
                        }
                    }
                }
                else if(m_ancienne.x() != -1)
                {
                    m_ancienne = arrivee;
                    effaceChemin();
                }
            }
        }
    }
}

void Jeu_graphique::effaceChemin()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {

            m_casesDep[i] [j]->setVisible(false);
        }
    }
}

void Jeu_graphique::afficheChemin(QPoint dep, QQueue<Dir>chem)
{
    int x = dep.x();
    int y = dep.y();
    for(int i = 0; i < chem.size(); i++)
    {
        case_suivante(&x,&y,chem.at(i));
        m_casesDep[x] [y]->setVisible(true);
    }
}

void Jeu_graphique::dragLeaveEvent(QGraphicsSceneDragDropEvent *)
{
    m_fleche->setVisible(false);
    m_posFleche.setX(-1);
    m_posFleche.setY(-1);
}

void Jeu_graphique::changeMap()
{
    m_parent->changeMap();
}

void Jeu_graphique::faitRecettes()
{
    m_parent->fait_recettes();
}

void Jeu_graphique::doit_recolter()
{
    m_parent->doit_recolter();
}

void Jeu_graphique::recolte(const QString &nom, QString const& verbe, Dir orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action)
{
    m_persos[nom]->recolte(verbe, nombre_coups, orientation, derniere_action);
}

void Jeu_graphique::recolte(const QString &nom, QString const& verbe, int orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action)
{
    recolte(nom, verbe, (Dir)orientation, nombre_coups, derniere_action);
}

void Jeu_graphique::a_recolte()
{
    m_parent->a_coupe();
}

void Jeu_graphique::marche_pas(DataMap *dataMap)
{
    for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin(); it != m_persos.end(); it++)
    {
        QPoint p = it.value()->posALaFin();
        dataMap->setCasePleineCombat(p.x(),p.y(),2);
    }
}

void Jeu_graphique::affichePortee()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casesPortee[i][j]->setVisible(m_cases_ateignables[i][j]);
        }
    }
}

void Jeu_graphique::stopUtiliseSort()
{
    m_imgCaseVisee->setVisible(false);
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_cases_ateignables[i] [j] = false;
            m_casesPortee[i][j]->setVisible(false);
        }
    }
}

void Jeu_graphique::utiliseSort(Sort *sort)
{
    m_parent->portee(m_cases_ateignables, m_persos[m_nom]->posALaFin().x(), m_persos[m_nom]->posALaFin().y(),sort->portee_min(), sort->portee_max());
    affichePortee();
}

void Jeu_graphique::afficheCasesCombat(DataMap *dataMap)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            QPoint p = dataMap->caseCombat(i,j);
            if(p.x() != -1)
            {
                m_imgcasescbt[i] [j]->setPos(m_parent->dataMap()->cposx(p.x(),p.y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(p.y(),m_hcase,true)-m_mhcase);
                m_imgcasescbt[i] [j]->setVisible(true);
            }
        }
    }
}

void Jeu_graphique::masqueCaseCombat()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_imgcasescbt[i] [j]->setVisible(false);
        }
    }
}

bool Jeu_graphique::contientJoueur(QPoint const& pos)
{
    for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin(); it != m_persos.end();it++)
    {
        if(it.value()->posALaFin() == pos)
            return true;
    }
    return false;
}

void Jeu_graphique::changePos(QString const& qui, int x, int y)
{
    m_persos[qui]->changePos(x,y);
}

void Jeu_graphique::setVie(QString const& nom, int vie)
{
    m_persos[nom]->setTexteAide(nom+" ("+QString::number(vie)+")");
}

void Jeu_graphique::meurt(QString const& nom)
{
    m_persos[nom]->setPos(-100,-100);
}

