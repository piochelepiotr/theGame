#include "affichejoueur.h"
#include "jeu_graphique.h"

AfficheJoueur::AfficheJoueur(UneCreature *creature, QString const& nom, QSize const& size,int *poscasex, int*poscasey, Jeu_graphique *parent) : QGraphicsPixmapItem()
{
    m_color = QColor(255,255,255,0);
    m_decalageX = 0;
    m_decalageY = 0;
    m_caseX = poscasex;
    m_caseY = poscasey;
    m_parent = parent;
    m_perso = new Actions_personnage(creature, size);
    setPixmap(m_perso->getImage());
    setZValue(4+(*m_caseY));
    m_pasentier = false;
    affiche();
    creationBulleAide(nom);
}

AfficheJoueur::AfficheJoueur(UneCreature *creature, QString const& nom, QSize const& size,QPoint const& poscase, Jeu_graphique *parent) : QGraphicsPixmapItem()
{
    m_color = QColor(255,255,255,0);
    m_decalageX = 0;
    m_decalageY = 0;
    m_caseX = new int(poscase.x());
    m_caseY = new int(poscase.y());
    m_parent = parent;
    m_perso = new Actions_personnage(creature, size);
    setPixmap(m_perso->getImage());
    setZValue(4+(*m_caseY));
    m_pasentier = true;
    affiche();
    creationBulleAide(nom);
}

AfficheJoueur::~AfficheJoueur()
{
    if(m_pasentier)
    {
        delete m_caseX;
        delete m_caseY;
    }
    m_parent->removeItem(this);
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
        setPos(m_parent->getJeu()->dataMap()->cposx(*m_caseX, *m_caseY,m_parent->getlcase())-pixmap().width()/2+m_decalageX, m_parent->getJeu()->dataMap()->cposy(*m_caseY,m_parent->gethcase())-pixmap().height()+m_parent->gethcase()*ECART+m_decalageY);
        if(m_perso->imobile() && m_parent->contientTranspo(QPoint(*m_caseX, *m_caseY)))
        {
            emit estSurTranspo(QPoint(*m_caseX, *m_caseY));
        }
    }
    else if(action != Actions_personnage::Aucune)
    {
        if(action == Actions_personnage::ChangeDeMap)
        {
            m_parent->changeMap();
        }
        else if(action == Actions_personnage::Recettes)
        {
            m_parent->faitRecettes();
        }
        else if(action == Actions_personnage::Recolter)
        {
            m_parent->doit_recolter();
        }
        else if(action == Actions_personnage::ARecolter)
        {
            m_parent->a_recolte();
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

void AfficheJoueur::redi(int lcase, int hcase)
{
    m_perso->redi(lcase, hcase);
    affiche();
}

void AfficheJoueur::affiche()
{
    setPixmap(m_perso->getImage());
    setPos(0,0);
    setPos(m_parent->getJeu()->dataMap()->cposx(*m_caseX, *m_caseY,m_parent->getlcase())-pixmap().width()/2+m_decalageX, m_parent->getJeu()->dataMap()->cposy(*m_caseY,m_parent->gethcase())-pixmap().height()+m_parent->gethcase()*ECART+m_decalageY);
}

void AfficheJoueur::changePos(int casex, int casey)
{
    *m_caseX = casex;
    *m_caseY = casey;
    setZValue(4+(*m_caseY));
    setPos(m_parent->getJeu()->dataMap()->cposx(*m_caseX, *m_caseY,m_parent->getlcase())-pixmap().width()/2+m_decalageX, m_parent->getJeu()->dataMap()->cposy(*m_caseY,m_parent->gethcase())-pixmap().height()+m_parent->gethcase()*ECART+m_decalageY);
}

void AfficheJoueur::mousePressEvent ( QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        emit clique();
}

void AfficheJoueur::creationBulleAide(QString const& texte)
{
    m_toolTip = new ToolTip(texte);
    m_parent->addItem(m_toolTip);
    m_toolTip->setVisible(false);
}

void AfficheJoueur::deplaceAide()
{
    int posx = this->x();
    int posy = this->y() - (m_toolTip->boundingRect().height()+3);
    if(posy < 0)
    {
        posy = this->y() + pixmap().height() + 3;
    }
    posx = this->x()+pixmap().width()/2 - m_toolTip->boundingRect().width()/2;
    m_toolTip->setPos(posx,posy);
}

void AfficheJoueur::aide()
{
    QGraphicsColorizeEffect* colEffect = new QGraphicsColorizeEffect();
    colEffect->setColor(m_color);
    setGraphicsEffect(colEffect);
    deplaceAide();
    m_toolTip->setVisible(true);
}

void AfficheJoueur::desaide()
{
    setGraphicsEffect(0);
    m_toolTip->setVisible(false);
}

void AfficheJoueur::setTexteAide(QString const& texte)
{
    m_toolTip->setPlainText(texte);
}
