#include "affichejoueur.h"
#include "graphicGame/gamefield.h"

AfficheJoueur::AfficheJoueur(EntityModel *creature, QString const& nom, QSize const& size, int *poscasex, int*poscasey, GameField *parent, int mapWidth)
    : ObjectItem(parent,mapWidth,QPoint(*poscasex,*poscasey))
{
    m_game = parent;
    m_decalageX = 0;
    m_decalageY = 0;
    m_caseX = poscasex;
    m_caseY = poscasey;
    m_game = parent;
    m_perso = new Actions_personnage(creature, size);
    setPixmap(m_perso->getImage());
    setZValue(4+(*m_caseY));
    m_pasentier = false;
    affiche();
    changeToolTip(nom);
}

AfficheJoueur::AfficheJoueur(EntityModel *creature, QString const& nom, QSize const& size, QPoint const& poscase, GameField *parent, int mapWidth)
: ObjectItem(parent,mapWidth,poscase)
{
    m_decalageX = 0;
    m_decalageY = 0;
    m_caseX = new int(poscase.x());
    m_caseY = new int(poscase.y());
    m_game = parent;
    m_perso = new Actions_personnage(creature, size);
    setPixmap(m_perso->getImage());
    setZValue(4+(*m_caseY));
    m_pasentier = true;
    affiche();
    changeToolTip(nom);
}

AfficheJoueur::~AfficheJoueur()
{
    if(m_pasentier)
    {
        delete m_caseX;
        delete m_caseY;
    }
    m_game->removeItem(this);
    delete m_perso;
}

void AfficheJoueur::suivante()
{
    int ancienneY = *m_caseY;
    Actions_personnage::DerniereAction action = Actions_personnage::Aucune;
    if(m_perso->suivante(&m_decalageX, &m_decalageY, m_caseX, m_caseY, &action))
    {
        setPixmap(m_perso->getImage());
        if(*m_caseY != ancienneY)
            setZValue(4+(*m_caseY));
        setPos(m_game->dataMap()->cposx(*m_caseX, *m_caseY,m_game->getlcase(),true)-pixmap().width()/2+m_decalageX, m_game->dataMap()->cposy(*m_caseY,m_game->gethcase(),true)-pixmap().height()+m_game->gethcase()*ECART+m_decalageY);
    }
    else if(action != Actions_personnage::Aucune)
    {
        if(action == Actions_personnage::ChangeDeMap)
        {
            m_game->changeMap();
        }
        else if(action == Actions_personnage::Recettes)
        {
            m_game->faitRecettes();
        }
        else if(action == Actions_personnage::Recolter)
        {
            m_game->doit_recolter();
        }
        else if(action == Actions_personnage::ARecolter)
        {
            m_game->a_coupe();
        }
    }
}

QPoint AfficheJoueur::posALaFin()
{
    QPoint p(*m_caseX,*m_caseY);
    if(!m_perso->imobile())
        p = m_perso->posALaFin(p);
    return p;
}

void AfficheJoueur::nouveauchemin(QQueue<Dir>chem, Actions_personnage::DerniereAction action)
{
    if(chem.size() < 4)
        m_perso->marche(chem, action);
    else
        m_perso->court(chem, action);
}

void AfficheJoueur::recolte(QString const& verbe,int nombre_coups, Dir orientation, Actions_personnage::DerniereAction derniere_action)
{
    m_perso->recolte(verbe, nombre_coups, derniere_action, orientation);
}

void AfficheJoueur::resize(int lcase, int hcase)
{
    m_perso->redi(lcase, hcase);
    affiche();
}

void AfficheJoueur::affiche()
{
    setPixmap(m_perso->getImage());
    setPos(0,0);
    setPos(m_game->dataMap()->cposx(*m_caseX, *m_caseY,m_game->getlcase(),true)-pixmap().width()/2+m_decalageX, m_game->dataMap()->cposy(*m_caseY,m_game->gethcase(),true)-pixmap().height()+m_game->gethcase()*ECART+m_decalageY);
}

void AfficheJoueur::changePos(int casex, int casey)
{
    *m_caseX = casex;
    *m_caseY = casey;
    setZValue(4+(*m_caseY));
    setPos(m_game->dataMap()->cposx(*m_caseX, *m_caseY,m_game->getlcase(),true)-pixmap().width()/2+m_decalageX, m_game->dataMap()->cposy(*m_caseY,m_game->gethcase(),true)-pixmap().height()+m_game->gethcase()*ECART+m_decalageY);
}

/*void AfficheJoueur::mousePressEvent ( QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {

    }
}*/
