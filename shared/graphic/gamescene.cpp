#include "gamescene.h"
#include <QGraphicsPixmapItem>

#include "scenery/data.h"
#include "map/computePath.h"

GameScene::GameScene(const QSize &size, QLabel *texte, Data *donnees_editeur)
{
    m_subWinOpened = false;
    m_displayGrid = true;
    m_posCaseVisee = QPoint(-1,-1);
    m_ancienne = QPoint(-1,-1);
    m_donnees_editeur = donnees_editeur;
    m_lmap = size.width();
    m_hmap = size.height();
    largethautcase();

    m_dataMap = new Map(m_donnees_editeur,0,0,0);
    m_zoom_active = true;
    m_tailleci = 1;
    m_enlevercaseim = false;
    m_calcObject = true;
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

    m_imageBackground = addPixmap(QPixmap());
    m_imageBackground->setZValue(3);
    m_imageBackground->setVisible(false);

    for(int j = 0; j < MAX_PAR_EQUIP; j++)
    {
        m_imgcasescbt[0] [j] = addPixmap(casecbt1);
        m_imgcasescbt[0] [j]->setZValue(5);
        m_imgcasescbt[0] [j]->setVisible(false);
        m_imgcasescbt[0] [j]->setOpacity(0.5);

        m_imgcasescbt[1] [j] = addPixmap(casecbt2);
        m_imgcasescbt[1] [j]->setZValue(5);
        m_imgcasescbt[1] [j]->setVisible(false);
        m_imgcasescbt[1] [j]->setOpacity(0.5);
    }

    for(int i=0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            m_casesDep[i] [j] = addPixmap(caseDep);
            m_casesDep[i] [j]->setZValue(4);
            m_casesDep[i] [j]->setVisible(false);
            m_casesDep[i] [j]->setOpacity(0.5);

            m_caseImmarchables[i] [j] = addPixmap(caseim);
            m_caseImmarchables[i] [j]->setZValue(5+Map::mapHeight);
            m_caseImmarchables[i] [j]->setVisible(false);
            m_caseImmarchables[i] [j]->setOpacity(0.5);

            m_casesPortee[i] [j] = addPixmap(casePortee);
            m_casesPortee[i] [j]->setZValue(5);
            m_casesPortee[i] [j]->setVisible(false);
            m_casesPortee[i] [j]->setOpacity(0.5);

            m_imagesObjets [i] [j] = new ObjectItem(this,m_lmap,QPoint(i,j));
            m_imagesObjets [i] [j]->setVisible(false);
            m_imagesObjets[i] [j]->setZValue(j+4);

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
    m_cadreg->setZValue(5+Map::mapHeight);
    m_cadreg->setBrush(QBrush(QColor(0,0,0)));
    m_cadreg->setOpacity(0.2);
    m_cadred = addRect(m_lmap-m_lcase*CASESCACHEESX,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadred->setZValue(5+Map::mapHeight);
    m_cadred->setBrush(QBrush(QColor(0,0,0)));
    m_cadred->setOpacity(0.2);
    m_cadreb = addRect(m_lcase*CASESCACHEESX+1,m_mhcase*(Map::mapHeight-CASESCACHEESY), m_lmap-2*m_lcase*CASESCACHEESX-2, m_lmap-m_mhcase*(Map::mapHeight-CASESCACHEESY));
    m_cadreb->setZValue(5+Map::mapHeight);
    m_cadreb->setBrush(QBrush(QColor(0,0,0)));
    m_cadreb->setOpacity(0.2);
    m_cadreh = addRect(m_lcase*CASESCACHEESX+1,0, m_lmap-2*m_lcase*CASESCACHEESX-2, m_mhcase*CASESCACHEESY);
    m_cadreh->setZValue(5+Map::mapHeight);
    m_cadreh->setBrush(QBrush(QColor(0,0,0)));
    m_cadreh->setOpacity(0.2);
    m_cadred->setVisible(!m_zoom_active);
    m_cadreg->setVisible(!m_zoom_active);
    m_cadreb->setVisible(!m_zoom_active);
    m_cadreh->setVisible(!m_zoom_active);
    m_subWindow = 0;
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
    resize(QSize(m_lmap, m_hmap));
}

void GameScene::resize(QSize const& nouvelle)
{
    qDebug() << "resize";
    bool saved = m_dataMap->estEnregistree();
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

    m_imgCaseVisee->setPixmap(QPixmap("../data/interface/casePO.png").scaled(m_lcase,m_hcase));



    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        m_imgcasescbt[0] [i]->setPixmap(casecbt1);
        m_imgcasescbt[1] [i]->setPixmap(casecbt2);
    }

    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            caseEgale(i, j, m_dataMap->objet(i,j));
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
            m_imgcasescbt[i] [j]->setPos(m_dataMap->cposx(m_dataMap->caseFight(i,j).x(),m_dataMap->caseFight(i,j).y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(m_dataMap->caseFight(i,j).y(),m_hcase,m_zoom_active)-m_mhcase);
        }
    }

    m_cadreg->setRect(0,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadred->setRect(m_lmap-m_lcase*CASESCACHEESX,0,m_lcase*CASESCACHEESX, m_hmap);
    m_cadreb->setRect(m_lcase*CASESCACHEESX+1,m_mhcase*(Map::mapHeight-CASESCACHEESY), m_lmap-2*m_lcase*CASESCACHEESX-2, m_lmap-m_mhcase*(Map::mapHeight-CASESCACHEESY));
    m_cadreh->setRect(m_lcase*CASESCACHEESX+1,0, m_lmap-2*m_lcase*CASESCACHEESX-2, m_mhcase*CASESCACHEESY);

    m_fond->setPixmap(m_dataMap->getBackground(m_lmap,m_hmap));
    m_dataMap->setEnregistree(saved);
    if(m_subWindow)
        m_subWindow->gameResized();
}

void GameScene::grille()
{
    if(m_displayGrid)
    {
    if(m_zoom_active)
    {
        for(int i=0; i < Map::mapWidth; i++)
        {
            for(int j = 0; j < Map::mapHeight; j++)
            {
                m_grille[i] [j]->setVisible(false);
            }
        }
        int posx, posy;
        QPolygon p;

        for(int i = CASESCACHEESX, m = Map::mapWidth-CASESCACHEESX+1; i < m; i++)
        {
            for(int j = CASESCACHEESY; j < Map::mapHeight-CASESCACHEESY+2; j++)
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

        for(int i=0; i < Map::mapWidth; i++)
        {
            for(int j = 0; j < Map::mapHeight; j++)
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
        for(int i=0; i < Map::mapWidth; i++)
        {
            for(int j = 0; j < Map::mapHeight; j++)
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
        m_lcase = m_lmap/((Map::mapWidth-CASESCACHEESX*2)*2-1)*2;
        m_hcase = m_hmap/(Map::mapHeight-CASESCACHEESY*2-1)*2;
        m_mlcase = m_lcase/2;
        m_mhcase = m_hcase/2;
    }
    else
    {
        m_lcase = m_lmap/(Map::mapWidth*2-1)*2;
        m_hcase = m_hmap/(Map::mapHeight-1)*2;
        m_mlcase = m_lcase/2;
        m_mhcase = m_hcase/2;
    }
}

void GameScene::case_prend_valeur(QPoint const& poscase, QPoint const& pos)
{
    if(m_calcObject)
    {
        caseEgale(poscase.x(),poscase.y(),m_objetActuel);
        m_objet = m_objetActuel;
    }
    else
    {
        m_dataMap->addToBackground(m_objetActuel, pos, m_lmap, m_hmap);
        m_fond->setPixmap(m_dataMap->getBackground(m_lmap,m_hmap));
    }
}

void GameScene::souriBouge(QPoint const& poscase, QPoint const& pos)
{
    m_texte->setText("pos : ["+QString::number(pos.x())+";"+QString::number(pos.y())+"] et map ["+QString::number(m_dataMap->x())+";"+QString::number(m_dataMap->y())+";"+QString::number(m_dataMap->z())+"]");
    if(m_calcObject)
    {
        if(poscase.x() != m_caseSele.x() || poscase.y() != m_caseSele.y())
            changementSele(poscase);
    }
    else
    {
        m_imageBackground->setPos(pos.x()-m_imageBackground->pixmap().width()/2, pos.y()-m_imageBackground->pixmap().height()/2);
    }
}

void GameScene::changementSele(QPoint const& nouvelle)
{
    if(!m_calcObject)
        return;
    if(m_caseSele.x() != -1)
    {
        caseEgale(m_caseSele.x(), m_caseSele.y(), m_objet);
    }
    if(nouvelle.x() != -1)
    {
        m_objet = m_dataMap->objet(nouvelle.x(),nouvelle.y());
        caseEgale(nouvelle.x(), nouvelle.y(), m_objetActuel);
    }
    m_caseSele = nouvelle;
}

void GameScene::setObjetActuel(Object *nouveau)
{
    changementSele(QPoint(-1,-1));
    m_objet = m_donnees_editeur->decor->objet(0);
    m_objetActuel = nouveau;
    if(m_objetActuel->numero() != 0)
    {
        m_imageBackground->setPixmap(m_objetActuel->image());
        m_imageBackground->setVisible(!m_calcObject);
    }
    else
    {
        m_imageBackground->setVisible(false);
    }
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


void GameScene::caseEgale(int i, int j, Object *objet)
{
    m_dataMap->setObjet(i,j,objet);
    if(objet == m_donnees_editeur->decor->objet(0))
    {
        m_imagesObjets[i] [j]->setVisible(false);
    }
    else
    {
        m_imagesObjets[i] [j]->setPixmap(objet->image());
        m_imagesObjets[i] [j]->setVisible(true);
        m_imagesObjets[i] [j]->setPos(m_dataMap->cposx(i,j,m_lcase,m_zoom_active)-m_imagesObjets[i] [j]->pixmap().width()/2, m_dataMap->cposy(j,m_hcase,m_zoom_active)-m_imagesObjets[i] [j]->pixmap().height()+m_hcase*ECART);
        if(objet->name().isEmpty())
            m_imagesObjets[i][j]->changeToolTip("");
        else
            m_imagesObjets[i][j]->changeToolTip(objet->name());
    }
}

void GameScene::remplire()
{
    changementSele(QPoint(-1,-1));
    for(int i=0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            caseEgale(i,j,m_objetActuel);
        }
    }
    ajouteEvent();
}

void GameScene::ajouteTranspo(QPoint const& pos, Gate *transpo)
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

void GameScene::calcObject()
{
    m_imageBackground->setVisible(false);
    changementSele(QPoint(-1,-1));
    m_calcObject = true;
    souriBouge(QPoint(-1,-1), QPoint(-200,-200));
}

void GameScene::calcBacground()
{
    m_imageBackground->setVisible(m_objetActuel->numero() != 0);
    changementSele(QPoint(-1,-1));
    m_calcObject = false;
    souriBouge(QPoint(-1,-1), QPoint(-200,-200));
}

void GameScene::rend_case_immarchable(int i, int j)
{
    if(i > -1 && j > -1 && i < Map::mapWidth && j < Map::mapHeight)
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
    if(i > -1 && j > -1 && i < Map::mapWidth && j < Map::mapHeight)
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
    if(i > -1 && j > -1 && i < Map::mapWidth && j < Map::mapHeight)
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

void GameScene::chargeContours()
{
    m_dataMap->charge_contours();
    resize(QSize(m_lmap,m_hmap));
}

//CASES COMBAT

void GameScene::ajouteCasecbt(int x, int y)
{
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_dataMap->caseFight(m_equipe,i).x() == -1)
        {
            m_dataMap->setCaseFight(m_equipe,i,QPoint(x,y));
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
        if(m_dataMap->caseFight(m_equipe,i).x() == x && m_dataMap->caseFight(m_equipe,i).y() == y)
        {
            m_dataMap->setCaseFight(m_equipe,i,QPoint(-1,-1));
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
        resize(QSize(m_lmap,m_hmap));
    }
}

//CHANGEMENT D'AFFICHAGE

void GameScene::affiche_casesMarchable()
{
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            if(m_dataMap->casePleine(i,j))
                m_caseImmarchables[i] [j]->setVisible(true);
        }
    }
}

void GameScene::masque_casesMarchable()
{
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            m_caseImmarchables[i] [j]->setVisible(false);
        }
    }
}

void GameScene::affiche_casesFight()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAX_PAR_EQUIP; j++)
        {
            if(m_dataMap->caseFight(i,j).x() != -1)
            {
                m_imgcasescbt[i] [j]->setPos(m_dataMap->cposx(m_dataMap->caseFight(i,j).x(),m_dataMap->caseFight(i,j).y(),m_lcase,m_zoom_active)-m_mlcase, m_dataMap->cposy(m_dataMap->caseFight(i,j).y(),m_hcase,m_zoom_active)-m_mhcase);
                m_imgcasescbt[i] [j]->setVisible(true);
            }
        }
    }
}

void GameScene::masque_casesFight()
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
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            if(m_dataMap->casePleine(i,j) == 2)
                m_casesPortee[i] [j]->setVisible(true);
        }
    }
}

void GameScene::masque_casesPO()
{
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            m_caseImmarchables[i] [j]->setVisible(false);
            m_casesPortee[i] [j]->setVisible(false);
        }
    }
}

void GameScene::updateObjet(int i,int j, Object *objet)
{
    delete m_imagesObjets[i] [j];
    m_imagesObjets[i] [j] = new ObjectItem(this, m_lmap, QPoint(i,j));
    m_imagesObjets[i] [j]->setZValue(j+4);
    caseEgale(i,j,objet);
}

void GameScene::updateObjet(QPoint pos)
{
    updateObjet(pos.x(),pos.y(),m_dataMap->objet(pos.x(),pos.y()));
}

void GameScene::effaceChemin()
{
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
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

void GameScene::stopUtiliseSpell()
{
    m_imgCaseVisee->setVisible(false);
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            m_cases_ateignables[i] [j] = false;
            m_casesPortee[i][j]->setVisible(false);
        }
    }
}

void GameScene::affichePortee()
{
    for(int i = 0; i < Map::mapWidth; i++)
    {
        for(int j = 0; j < Map::mapHeight; j++)
        {
            m_casesPortee[i][j]->setVisible(m_cases_ateignables[i][j]);
        }
    }
}

void GameScene::utileClique(QPoint const& pos)
{
    Q_UNUSED(pos);
}

Scenery *GameScene::decors()
{
    return m_donnees_editeur->decor;
}
