#include "gamescene.h"
#include <QGraphicsPixmapItem>

GameScene::GameScene(const QSize &size, QLabel *texte, Donnees_editeur *donnees_editeur)
{
    m_displayGrid = true;
    m_posCaseVisee = QPoint(-1,-1);
    m_ancienne = QPoint(-1,-1);
    m_donnees_editeur = donnees_editeur;
    m_lmap = size.width();
    m_hmap = size.height();
    largethautcase();

    m_dataMap = new DataMap(m_donnees_editeur,0,0,0);
    m_zoom_active = true;
    m_tailleci = 1;
    m_enlevercaseim = false;
    m_calc = CALQUE_DEFAUT;
    m_equipe = 0;
    m_objetActuel = m_donnees_editeur->decor->objet(0);
    m_texte = texte;

    QPen pen(QColor(200,200,200, 128));
    QPolygon p;
    QPixmap caseim("../data/interface/caseim.png");
    QPixmap casePortee("../data/interface/casePO.png");
    QPixmap casecbt1("../data/interface/casecbt0.png");
    QPixmap casecbt2("../data/interface/casecbt1.png");
    QPixmap caseDep("../data/interface/caseDep.png");

    m_fond = addPixmap(QPixmap());
    m_fond->setPos(0,0);


    m_imgCaseVisee = addPixmap(casecbt2);
    m_imgCaseVisee->setZValue(5);
    m_imgCaseVisee->setVisible(false);
    m_imgCaseVisee->setOpacity(0.5);

    for(int j = 0; j < MAX_PAR_EQUIP; j++)
    {
        m_imgcasescbt[0] [j] = addPixmap(casecbt1);
        m_imgcasescbt[0] [j]->setZValue(5+NBR_CASES_H);
        m_imgcasescbt[0] [j]->setVisible(false);
        m_imgcasescbt[0] [j]->setOpacity(0.5);

        m_imgcasescbt[1] [j] = addPixmap(casecbt2);
        m_imgcasescbt[1] [j]->setZValue(5+NBR_CASES_H);
        m_imgcasescbt[1] [j]->setVisible(false);
        m_imgcasescbt[1] [j]->setOpacity(0.5);
    }

    for(int i=0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casesDep[i] [j] = addPixmap(caseDep);
            m_casesDep[i] [j]->setZValue(4);
            m_casesDep[i] [j]->setVisible(false);
            m_casesDep[i] [j]->setOpacity(0.5);

            m_caseImmarchables[i] [j] = addPixmap(caseim);
            m_caseImmarchables[i] [j]->setZValue(5+NBR_CASES_H);
            m_caseImmarchables[i] [j]->setVisible(false);
            m_caseImmarchables[i] [j]->setOpacity(0.5);

            m_casesPortee[i] [j] = addPixmap(casePortee);
            m_casesPortee[i] [j]->setZValue(5+NBR_CASES_H);
            m_casesPortee[i] [j]->setVisible(false);
            m_casesPortee[i] [j]->setOpacity(0.5);

            for(int x = 0; x < 2; x++)
            {
                m_imagesObjets[x] [i] [j] = new ObjSurScene(this,m_lmap);
                m_imagesObjets[x] [i] [j]->setVisible(false);
            }

            m_imagesObjets[2] [i] [j] = new ObjSurScene(this,m_lmap,QPoint(i,j));
            m_imagesObjets[2] [i] [j]->setVisible(false);

            m_imagesObjets[0] [i] [j]->setZValue(1);
            m_imagesObjets[1] [i] [j]->setZValue(2);
            m_imagesObjets[2] [i] [j]->setZValue(j+4);

            m_grille[i] [j] = addPolygon(p, pen);
            m_grille[i] [j]->setZValue(3);

        }
    }

    grille();

    m_caseSele.setX(-1);
    m_caseSele.setY(-1);

    changementSele(QPoint(-1,-1));
    m_objet = m_donnees_editeur->decor->objet(0);

    m_cadreg = addRect(0,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadreg->setZValue(5+NBR_CASES_H);
    m_cadreg->setBrush(QBrush(QColor(0,0,0)));
    m_cadreg->setOpacity(0.2);
    m_cadred = addRect(m_lmap-m_lcase*CASESCACHEESX,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadred->setZValue(5+NBR_CASES_H);
    m_cadred->setBrush(QBrush(QColor(0,0,0)));
    m_cadred->setOpacity(0.2);
    m_cadreb = addRect(m_lcase*CASESCACHEESX+1,m_mhcase*(NBR_CASES_H-CASESCACHEESY), m_lmap-2*m_lcase*CASESCACHEESX-2, m_lmap-m_mhcase*(NBR_CASES_H-CASESCACHEESY));
    m_cadreb->setZValue(5+NBR_CASES_H);
    m_cadreb->setBrush(QBrush(QColor(0,0,0)));
    m_cadreb->setOpacity(0.2);
    m_cadreh = addRect(m_lcase*CASESCACHEESX+1,0, m_lmap-2*m_lcase*CASESCACHEESX-2, m_mhcase*CASESCACHEESY);
    m_cadreh->setZValue(5+NBR_CASES_H);
    m_cadreh->setBrush(QBrush(QColor(0,0,0)));
    m_cadreh->setOpacity(0.2);
    zoomChanged();
}

GameScene::~GameScene()
{

}

void GameScene::zoomChanged()
{
    m_cadred->setVisible(!m_zoom_active);
    m_cadreg->setVisible(!m_zoom_active);
    m_cadreb->setVisible(!m_zoom_active);
    m_cadreh->setVisible(!m_zoom_active);
    actualise();
}

void GameScene::changeValeurZoom()
{   
    m_zoom_active = !m_zoom_active;
    zoomChanged();
}

void GameScene::actualise()
{
    redi(QSize(m_lmap, m_hmap));
}

void GameScene::redi(QSize const& nouvelle)
{
    bool enregistree = m_dataMap->estEnregistree();
    m_lmap = nouvelle.width();
    m_hmap = nouvelle.height();
    largethautcase();
    m_donnees_editeur->decor->resize(m_lcase, m_hcase,m_lmap,m_hmap);
    grille();
    QPixmap caseDep = QPixmap("../data/interface/caseDep.png").scaled(m_lcase, m_hcase);
    QPixmap caseim = QPixmap("../data/interface/caseim.png").scaled(m_lcase, m_hcase);
    QPixmap casePortee = QPixmap("../data/interface/casePO.png").scaled(m_lcase, m_hcase);
    QPixmap casecbt1 = QPixmap("../data/interface/casecbt0.png").scaled(m_lcase, m_hcase);
    QPixmap casecbt2 = QPixmap("../data/interface/casecbt1.png").scaled(m_lcase, m_hcase);

    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        m_imgcasescbt[0] [i]->setPixmap(casecbt1);
        m_imgcasescbt[1] [i]->setPixmap(casecbt2);
    }

    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                caseEgale(i, j, m_dataMap->objet(i,j,x), x);
            }
            m_casesDep[i] [j]->setPixmap(caseDep);
            m_casesDep[i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_mhcase);

            m_caseImmarchables[i] [j]->setPixmap(caseim);
            m_caseImmarchables[i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_mhcase);

            m_casesPortee[i] [j]->setPixmap(casePortee);
            m_casesPortee[i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_mhcase);
        }
    }

    for(QMap<QPoint, QGraphicsPixmapItem*>::iterator i = m_lesimagestransports.begin(); i != m_lesimagestransports.end(); i++)
    {
        i.value()->setPixmap(QPixmap("../data/interface/transporteur.png").scaled(m_lcase, m_hcase));
        i.value()->setPos(m_dataMap->cposx(i.key().x(), i.key().y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(i.key().y(),m_hcase,m_zoom_active)-m_mhcase);
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_imgcasescbt[i] [j]->setPos(m_dataMap->cposx(m_dataMap->caseCombat(i,j).x(),m_dataMap->caseCombat(i,j).y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(m_dataMap->caseCombat(i,j).y(),m_hcase,m_zoom_active)-m_mhcase);
        }
    }

    m_cadreg->setRect(0,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadred->setRect(m_lmap-m_lcase*CASESCACHEESX,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadreb->setRect(m_lcase*CASESCACHEESX+1,m_mhcase*(NBR_CASES_H-CASESCACHEESY), m_lmap-2*m_lcase*CASESCACHEESX-2, m_lmap-m_mhcase*(NBR_CASES_H-CASESCACHEESY));
    m_cadreh->setRect(m_lcase*CASESCACHEESX+1,0, m_lmap-2*m_lcase*CASESCACHEESX-2, m_mhcase*CASESCACHEESY);

    fondEgal(m_dataMap->fond());
    m_dataMap->setEnregistree(enregistree);
}

void GameScene::grille()
{
    if(m_displayGrid)
    {
    if(m_zoom_active)
    {
        for(int i=0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                m_grille[i] [j]->setVisible(false);
            }
        }
        int posx, posy;
        QPolygon p;

        for(int i = CASESCACHEESX, m = NBR_CASES_L-CASESCACHEESX+1; i < m; i++)
        {
            for(int j = CASESCACHEESY; j < NBR_CASES_H-CASESCACHEESY+2; j++)
            {
                if(!m_dataMap->casePleine(i,j))
                    m_grille[i] [j]->setVisible(true);
                else
                    m_grille[i] [j]->setVisible(false);
                posx = m_dataMap->cposx(i,j,m_lcase,m_zoom_active);
                posy = m_dataMap->cposy(j,m_hcase,m_zoom_active);

                p.clear();
                p<<QPoint(posx, posy-m_mhcase)<<QPoint(posx+m_mlcase,posy)<<QPoint(posx, posy+m_mhcase)<<QPoint(posx-m_mlcase, posy);
                m_grille[i] [j]->setPolygon(p);
            }
        }
    }
    else
    {
        int posx, posy;
        QPolygon p;

        for(int i=0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                if(!m_dataMap->casePleine(i,j))
                    m_grille[i] [j]->setVisible(true);
                else
                    m_grille[i] [j]->setVisible(false);
                posx = m_dataMap->cposx(i,j,m_lcase,m_zoom_active);
                posy = m_dataMap->cposy(j,m_hcase,m_zoom_active);

                p.clear();
                p<<QPoint(posx, posy-m_mhcase)<<QPoint(posx+m_mlcase,posy)<<QPoint(posx, posy+m_mhcase)<<QPoint(posx-m_mlcase, posy);
                m_grille[i] [j]->setPolygon(p);
            }
        }
    }
    }
    else
    {
        for(int i=0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                m_grille[i] [j]->setVisible(false);
            }
        }
    }
}

void GameScene::largethautcase()
{
    if(m_zoom_active)
    {
        m_lcase = m_lmap/((NBR_CASES_L-CASESCACHEESX*2)*2-1)*2;
        m_hcase = m_hmap/(NBR_CASES_H-CASESCACHEESY*2-1)*2;
        m_mlcase = m_lcase/2;
        m_mhcase = m_hcase/2;
    }
    else
    {
        m_lcase = m_lmap/(NBR_CASES_L*2-1)*2;
        m_hcase = m_hmap/(NBR_CASES_H-1)*2;
        m_mlcase = m_lcase/2;
        m_mhcase = m_hcase/2;
    }
}

void GameScene::case_prend_valeur(QPoint const& poscase)
{
    caseEgale(poscase.x(),poscase.y(),m_objetActuel, m_calc);
    m_objet = m_objetActuel;
}

void GameScene::souriBouge(QPoint const& poscase)
{
    m_texte->setText("pos : ["+QString::number(poscase.x())+";"+QString::number(poscase.y())+"] et map ["+QString::number(m_dataMap->x())+";"+QString::number(m_dataMap->y())+";"+QString::number(m_dataMap->z())+"]");
    if(poscase.x() != m_caseSele.x() || poscase.y() != m_caseSele.y())
        changementSele(poscase);
}

void GameScene::changementSele(QPoint const& nouvelle)
{
    if(m_caseSele.x() != -1)
    {
        caseEgale(m_caseSele.x(), m_caseSele.y(), m_objet, m_calc);
    }
    if(nouvelle.x() != -1)
    {
        m_objet = m_dataMap->objet(nouvelle.x(),nouvelle.y(),m_calc);
        caseEgale(nouvelle.x(), nouvelle.y(), m_objetActuel, m_calc);
    }
    m_caseSele = nouvelle;
}


void GameScene::setObjetActuel(Objet *nouveau)
{
    changementSele(QPoint(-1,-1));
    m_objet = m_donnees_editeur->decor->objet(0);
    m_objetActuel = nouveau;
}

void GameScene::charge(int cooX, int cooY, int cooZ)
{
    if(cooX == -1)
        cooX = m_dataMap->x();
    if(cooY == -1)
        cooY = m_dataMap->y();
    if(cooZ == -1)
        cooZ = m_dataMap->z();

    m_dataMap->chargeMap(cooX,cooY,cooZ);
    actualise();
}



void GameScene::nouvelle()
{
    changementSele(QPoint(-1,-1));
    m_dataMap->nouvelleMap();
}


void GameScene::caseEgale(int i, int j, Objet *objet, int fond)
{
    m_dataMap->setObjet(i,j,fond,objet);
    if(objet == m_donnees_editeur->decor->objet(0))
    {
        m_imagesObjets[fond] [i] [j]->setVisible(false);
    }
    else
    {
        m_imagesObjets[fond] [i] [j]->setPixmap(objet->image());
        m_imagesObjets[fond] [i] [j]->setVisible(true);
        if(fond == 2)
        {
            m_imagesObjets[fond] [i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_imagesObjets[fond] [i] [j]->pixmap().width()/2, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_imagesObjets[fond] [i] [j]->pixmap().height()+m_hcase*ECART);
            if(objet->nom().isEmpty())
                m_imagesObjets[fond][i][j]->inutile();
            else
                m_imagesObjets[fond][i][j]->utile(objet->nom());
        }
        else
            m_imagesObjets[fond] [i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_imagesObjets[fond] [i] [j]->pixmap().width()/2, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_imagesObjets[fond] [i] [j]->pixmap().height()/2);
    }
}

void GameScene::remplire()
{
    changementSele(QPoint(-1,-1));
    for(int i=0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            caseEgale(i,j,m_objetActuel, m_calc);
        }
    }
    ajouteEvent();
}

void GameScene::ajouteTranspo(QPoint const& pos, Transporteur const& transpo)
{
    m_dataMap->ajouterTranspo(pos,transpo);
    m_lesimagestransports[pos] = addPixmap(QPixmap("../data/interface/transporteur.png").scaled(m_lcase, m_hcase));
    m_lesimagestransports[pos]->setPos(m_dataMap->cposx(pos.x(), pos.y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(pos.y(),m_hcase,m_zoom_active)-m_mhcase);
    m_lesimagestransports[pos]->setZValue(4);
}

void GameScene::supprimeTranspo(QPoint const& pos)
{
    m_dataMap->supprimeTranspo(pos);
    removeItem(m_lesimagestransports[pos]);
    delete m_lesimagestransports[pos];
    m_lesimagestransports.remove(pos);
}

void GameScene::calc1()
{
    changementSele(QPoint(-1,-1));
    m_calc = 0;
}

void GameScene::calc2()
{
    changementSele(QPoint(-1,-1));
    m_calc = 1;
}


void GameScene::calc3()
{
    changementSele(QPoint(-1,-1));
    m_calc = 2;
}

void GameScene::rend_case_immarchable(int i, int j)
{
    if(i > -1 && j > -1 && i < NBR_CASES_L && j < NBR_CASES_H)
    {
        if(m_enlevercaseim)
        {
            m_dataMap->setCasePleine(i,j,0);
            m_caseImmarchables[i] [j]->setVisible(false);
            m_grille[i] [j]->setVisible(true);
        }
        else if(!m_dataMap->casePleine(i,j))
        {
            m_dataMap->setCasePleine(i,j,1);
            m_caseImmarchables[i] [j]->setVisible(true);
            m_grille[i] [j]->setVisible(false);
        }
    }
}

void GameScene::change_portee_case(QPoint const& lacase)
{
    if(m_enlevercaseim)
    {
        if(case_avec_portee(lacase.x(), lacase.y()))
            ajouteEvent();
    }
    else
    {
        if(case_sans_portee(lacase.x(),lacase.y()))
            ajouteEvent();
    }
}

bool GameScene::case_sans_portee(int i, int j)
{
    if(i > -1 && j > -1 && i < NBR_CASES_L && j < NBR_CASES_H)
    {
        if(m_dataMap->casePleine(i,j) != 2)
        {
            if(m_dataMap->casePleine(i,j) == 0)
            {
                m_caseImmarchables[i] [j]->setVisible(true);
                m_grille[i] [j]->setVisible(false);
            }
            m_casesPortee[i] [j]->setVisible(true);
            m_dataMap->setCasePleine(i,j,2);
            return true;
        }
    }
    return false;
}

bool GameScene::case_avec_portee(int i, int j)
{
    if(i > -1 && j > -1 && i < NBR_CASES_L && j < NBR_CASES_H)
    {
        if(m_dataMap->casePleine(i,j) == 2)
        {
            m_dataMap->setCasePleine(i,j,1);
            m_casesPortee[i] [j]->setVisible(false);
            return true;
        }
    }
    return false;
}

void GameScene::remplitCaseIm(int i, int j)
{
    if(m_tailleci == 1)
    {
        rend_case_immarchable(i,j);
    }
    else if(m_tailleci == 3)
    {
        for(int x = i-1; x < i+2; x++)
        {
            for(int y = j-2; y < j+4; y++)
            {
                rend_case_immarchable(x,y);
            }
        }
    }
    else
    {
        for(int x = i-2; x < i+4; x++)
        {
            for(int y = j-3; y < j+6; y++)
            {
                rend_case_immarchable(x,y);
            }
        }
    }
}

void GameScene::fondEgal(QString const& nom)
{
    m_dataMap->setFond(nom);
    m_fond->setPixmap(QPixmap("../data/lesfonds/"+nom).scaled(m_lmap, m_hmap));
}

void GameScene::chargeContours()
{
    m_dataMap->charge_contours();
    redi(QSize(m_lmap,m_hmap));
}

//CASES COMBAT

void GameScene::ajouteCasecbt(int x, int y)
{
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_dataMap->caseCombat(m_equipe,i).x() == -1)
        {
            m_dataMap->setCaseCombat(m_equipe,i,QPoint(x,y));
            m_imgcasescbt[m_equipe] [i]->setPos(m_dataMap->cposx(x,y,m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(y,m_hcase,m_zoom_active)-m_mhcase);
            m_imgcasescbt[m_equipe] [i]->setVisible(true);
            return;
        }
    }
}

void GameScene::supprimeCasecbt(int x, int y)
{
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_dataMap->caseCombat(m_equipe,i).x() == x && m_dataMap->caseCombat(m_equipe,i).y() == y)
        {
            m_dataMap->setCaseCombat(m_equipe,i,QPoint(-1,-1));
            m_imgcasescbt[m_equipe] [i]->setVisible(false);
            return;
        }
    }
}

//EDITION ANNULER

void GameScene::ajouteEvent()
{
    m_dataMap->enregistre(true);
    //enregistre(m_mapx, m_mapy, m_mapz, true);
}

void GameScene::undo()
{
    if(m_dataMap->undo())
    {
        redi(QSize(m_lmap,m_hmap));
    }
}

//CHANGEMENT D'AFFICHAGE

void GameScene::affiche_casesMarchable()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(m_dataMap->casePleine(i,j))
                m_caseImmarchables[i] [j]->setVisible(true);
        }
    }
}

void GameScene::masque_casesMarchable()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_caseImmarchables[i] [j]->setVisible(false);
        }
    }
}

void GameScene::affiche_casesCombat()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            if(m_dataMap->caseCombat(i,j).x() != -1)
            {
                m_imgcasescbt[i] [j]->setPos(m_dataMap->cposx(m_dataMap->caseCombat(i,j).x(),m_dataMap->caseCombat(i,j).y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(m_dataMap->caseCombat(i,j).y(),m_hcase,m_zoom_active)-m_mhcase);
                m_imgcasescbt[i] [j]->setVisible(true);
            }
        }
    }
}

void GameScene::masque_casesCombat()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            m_imgcasescbt[i] [j]->setVisible(false);
        }
    }
}

void GameScene::affiche_casesPO()
{
    affiche_casesMarchable();
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            if(m_dataMap->casePleine(i,j) == 2)
                m_casesPortee[i] [j]->setVisible(true);
        }
    }
}

void GameScene::masque_casesPO()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_caseImmarchables[i] [j]->setVisible(false);
            m_casesPortee[i] [j]->setVisible(false);
        }
    }
}

void GameScene::updateObjet(int i,int j, Objet *objet)
{
    delete m_imagesObjets[2] [i] [j];
    m_imagesObjets[2] [i] [j] = new ObjSurScene(this, m_lmap, QPoint(i,j));
    m_imagesObjets[2] [i] [j]->setZValue(j+4);
    caseEgale(i,j,objet,2);
}

void GameScene::updateObjet(QPoint pos)
{
    updateObjet(pos.x(),pos.y(),m_dataMap->objet(pos.x(),pos.y(),2));
}

void GameScene::effaceChemin()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {

            m_casesDep[i] [j]->setVisible(false);
        }
    }
}

void GameScene::afficheChemin(QPoint dep, QQueue<Dir>chem)
{
    int x = dep.x();
    int y = dep.y();
    for(int i = 0; i < chem.size(); i++)
    {
        case_suivante(&x,&y,chem.at(i));
        m_casesDep[x] [y]->setVisible(true);
    }
}

void GameScene::stopUtiliseSort()
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

void GameScene::affichePortee()
{
    for(int i = 0; i < NBR_CASES_L; i++)
    {
        for(int j = 0; j < NBR_CASES_H; j++)
        {
            m_casesPortee[i][j]->setVisible(m_cases_ateignables[i][j]);
        }
    }
}

void GameScene::utileClique(QPoint const& pos)
{

}
