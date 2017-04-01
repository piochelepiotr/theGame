#include "actions_personnage.h"

#define LENGTH_RUN 2

Action::Action(const QString &name, Dir orientation, ImagesEntity *images)
{
    m_currentImg = 0;
    m_currentStep = 0;
    m_name = name;
    m_orientation = orientation;
    m_images = images->getImagesAction(name);
    m_nbrOfImg = m_images->nombre_images(m_orientation);
    qDebug() << name;
    if(name == "courir")
    {
        m_length = LENGTH_RUN;
    }
    else
    {
        m_length = m_nbrOfImg;
    }
}

void Action::nextImage()
{
    m_currentImg = (m_currentImg + 1) % m_nbrOfImg;
    m_currentStep = (m_currentStep + 1) % m_length;
}

Actions_personnage::Actions_personnage(EntityModel *uneCreature, const QSize &taille_case)
{
    m_images = new ImagesEntity(uneCreature, taille_case);
    m_actionActuelle = new Action("marcher", B, m_images);
    m_immobile = true;
    m_taille_case = taille_case;
    m_derniere_action = Aucune;
}

Actions_personnage::~Actions_personnage()
{
    delete m_images;
    delete m_actionActuelle;
    for(int i = 0; i < m_lesactions.size(); i++)
    {
        delete m_lesactions[i];
    }
}

void Actions_personnage::redi(int lcase, int hcase)
{
    m_taille_case.setWidth(lcase);
    m_taille_case.setHeight(hcase);
    m_images->redimentionne(QSize(lcase, hcase));
}

bool Actions_personnage::suivante(int *decalageX, int *decalageY, int *caseX, int *caseY, DerniereAction *action)
{
    if(m_immobile)
    {
        if(m_lesactions.isEmpty())
        {
            if(m_derniere_action != Aucune)
            {
                *action = m_derniere_action;
                m_derniere_action = Aucune;
            }
            return false;
        }
        delete m_actionActuelle;
        m_actionActuelle = m_lesactions.front();
        m_lesactions.pop_front();
        m_immobile = false;
        return true;
    }
    if(m_actionActuelle->moves())
    {
        if(!m_actionActuelle->isAtEnd())
        {
            m_actionActuelle->nextImage();
            decale(decalageX, decalageY);
        }
        else
        {
            *decalageX = 0;
            *decalageY = 0;
            QPoint nouvellePos = posALaFin(QPoint(*caseX, *caseY));
            *caseX = nouvellePos.x();
            *caseY = nouvellePos.y();
            Dir orientation = m_actionActuelle->orientation();
            int currentImage = m_actionActuelle->getCurrentImage();
            delete m_actionActuelle;
            if(m_lesactions.isEmpty())
            {
                m_immobile = true;
                m_actionActuelle = new Action("marcher", orientation, m_images);
            }
            else
            {
                m_actionActuelle = m_lesactions.front();
                m_lesactions.pop_front();
                m_actionActuelle->setCurrentImg(currentImage+1);
            }
        }
    }
    else
    {
        if(!m_actionActuelle->isAtEnd())
        {
            m_actionActuelle->nextImage();
        }
        else
        {
            Dir orientation = m_actionActuelle->orientation();
            delete m_actionActuelle;
            if(m_lesactions.isEmpty())
            {
                m_immobile = true;
                m_actionActuelle = new Action("marcher", orientation, m_images);
            }
            else
            {
                m_actionActuelle = m_lesactions.front();
                m_lesactions.pop_front();
            }
        }
    }
    return true;
}

void Actions_personnage::decale(int *x, int *y) // à activer après avoir changer la valeure de currentImage
{
    int currentStep = m_actionActuelle->getCurrentStep();
    *x = 0;
    *y = 0;
    switch(m_actionActuelle->orientation())
    {
        case O:
            *y -= m_taille_case.height()/m_actionActuelle->length()*currentStep;
            break;
        case B:
            *y += m_taille_case.height()/m_actionActuelle->length()*currentStep;
            break;
        case G:
            *x -= m_taille_case.width()/m_actionActuelle->length()*currentStep;
            break;
        case D:
            *x += m_taille_case.width()/m_actionActuelle->length()*currentStep;
            break;
        case OG:
            *y -= (m_taille_case.height()/2)/m_actionActuelle->length()*currentStep;
            *x -= (m_taille_case.width()/2)/m_actionActuelle->length()*currentStep;
            break;
        case OD:
            *y -= (m_taille_case.height()/2)/m_actionActuelle->length()*currentStep;
            *x += (m_taille_case.width()/2)/m_actionActuelle->length()*currentStep;
            break;
        case BG:
            *y += (m_taille_case.height()/2)/m_actionActuelle->length()*currentStep;
            *x -= (m_taille_case.width()/2)/m_actionActuelle->length()*currentStep;
            break;
        case BD:
            *y += (m_taille_case.height()/2)/m_actionActuelle->length()*currentStep;
            *x += (m_taille_case.width()/2)/m_actionActuelle->length()*currentStep;
            break;
        default:
            break;
    }
}

QPoint Actions_personnage::posALaFin(QPoint actuelle)
{
    bool paire;
    if(actuelle.y() %2 == 0)
        paire = true;
    else
        paire = false;
    switch(m_actionActuelle->orientation())
    {
        case O:
            actuelle.setY(actuelle.y()-2);
            break;
        case B:
            actuelle.setY(actuelle.y()+2);
            break;
        case G:
            actuelle.setX(actuelle.x()-1);
            break;
        case D:
            actuelle.setX(actuelle.x()+1);
            break;
        case OG:
            actuelle.setY(actuelle.y()-1);
            if(paire)
            {
                actuelle.setX(actuelle.x()-1);
            }
            break;
        case BG:
            actuelle.setY(actuelle.y()+1);
            if(paire)
            {
                actuelle.setX(actuelle.x()-1);
            }
            break;
        case OD:
            actuelle.setY(actuelle.y()-1);
            if(!paire)
            {
                actuelle.setX(actuelle.x()+1);
            }
            break;
        case BD:
            actuelle.setY(actuelle.y()+1);
            if(!paire)
            {
                actuelle.setX(actuelle.x()+1);
            }
            break;
        default:
            break;
    }

    return actuelle;
}

void Actions_personnage::effaceActions()
{
    for(int i = 0; i < m_lesactions.size(); i++)
    {
        delete m_lesactions[i];
    }
    m_lesactions.clear();
}

void Actions_personnage::ajouteAction(const QString &nom, Dir orientation)
{
    effaceActions();
    m_lesactions.push_back(new Action(nom, orientation, m_images));
}

void Actions_personnage::marche(QQueue<Dir>const&chemin, DerniereAction action)
{
    effaceActions();
    for(int i = 0; i < chemin.size(); i++)
    {
        m_lesactions.push_back(new Action("marcher", chemin[i], m_images));
    }
    m_derniere_action = action;
}

void Actions_personnage::court(QQueue<Dir>const&chemin, DerniereAction action)
{
    effaceActions();
    for(int i = 0; i < chemin.size(); i++)
    {
        m_lesactions.push_back(new Action("courir", chemin[i], m_images));
    }
    m_derniere_action = action;
}

void Actions_personnage::recolte(QString const& verbe, int nombre_coups, DerniereAction action, Dir direction)
{
    effaceActions();
    for(int i = 0; i < nombre_coups; i++)
    {
        m_lesactions.push_back(new Action(verbe, direction, m_images));
    }
    m_derniere_action = action;
}

