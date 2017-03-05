#include "actions_personnage.h"

Action::Action(const QString &nom, Dir orientation, Images_Classe *images)
{
    m_nom = nom;
    m_orientation = orientation;
    m_images = images->getImagesAction(nom);
    m_nbrImages = m_images->nombre_images(m_orientation);
}

Actions_personnage::Actions_personnage(UneCreature *uneCreature, const QSize &taille_case)
{
    m_images = new Images_Classe(uneCreature, taille_case);
    m_actionActuelle = new Action("marcher", O, m_images);
    m_immobile = true;
    m_taille_case = taille_case;
    m_imageActuelle = 0;
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
    if(m_actionActuelle->enMouvement())
    {
        if(m_imageActuelle < m_actionActuelle->nombre_images()-1)
        {
            m_imageActuelle++;
            decale(decalageX, decalageY);
        }
        else
        {
            m_imageActuelle = 0;
            *decalageX = 0;
            *decalageY = 0;
            QPoint nouvellePos = posALaFin(QPoint(*caseX, *caseY));
            *caseX = nouvellePos.x();
            *caseY = nouvellePos.y();
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
    else
    {
        if(m_imageActuelle < m_actionActuelle->nombre_images()-1)
        {
            m_imageActuelle++;
        }
        else
        {
            m_imageActuelle = 0;
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

void Actions_personnage::decale(int *x, int *y) // à activer après avoir changer la valeure de m_imageActuelle
{
    *x = 0;
    *y = 0;
    switch(m_actionActuelle->orientation())
    {
        case O:
            *y -= m_taille_case.height()/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case B:
            *y += m_taille_case.height()/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case G:
            *x -= m_taille_case.width()/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case D:
            *x += m_taille_case.width()/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case OG:
            *y -= (m_taille_case.height()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            *x -= (m_taille_case.width()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case OD:
            *y -= (m_taille_case.height()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            *x += (m_taille_case.width()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case BG:
            *y += (m_taille_case.height()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            *x -= (m_taille_case.width()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            break;
        case BD:
            *y += (m_taille_case.height()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
            *x += (m_taille_case.width()/2)/m_actionActuelle->nombre_images()*m_imageActuelle;
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

