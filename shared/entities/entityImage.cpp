#include "entities/entityImage.h"

Images_action::Images_action(QString const& nom_classe,QString const& nom_action, QSize const& size)
{
    m_nbrUtilisateur = 1;
    m_nomClasse = nom_classe;
    m_nomAction = nom_action;
    definieEnMouvement();
    QString chemin = "../data/imagesdespersos/"+ m_nomClasse+"/"+ m_nomAction + "/", chemin2;
    int j;
    QPixmap p;
    for(int i = 0; i < 8; i++)
    {
        chemin2 = chemin + QString::number(i) + '/';
        j = 0;
        while(p.load(chemin2+QString::number(j)+".png"))
        {
            m_images[i].push_back(p.scaled(size.width(), size.height()));
            j++;
        }
    }
}

bool Images_action::redimentionne(QSize const& nouvelle)
{
    if(m_nbrUtilisateur < 1)
        return false;
    QString chemin = "../data/imagesdespersos/"+ m_nomClasse +"/"+ m_nomAction + "/", chemin2;
    for(int i = 0; i < 8; i++)
    {
        chemin2 = chemin + QString::number(i) + '/';
        for(int j = 0; j < m_images[i].size(); j++)
        {
            m_images[i][j] = QPixmap(chemin2+ QString::number(j)+".png" ).scaled(nouvelle.width(), nouvelle.height());
        }
    }
    return true;
}

QPixmap Images_action::getImage(int num, Dir orientation) const
{
    if(num < nombre_images(orientation))
        return m_images[(int)orientation][num];
    return m_images[0][0];
}

void Images_action::definieEnMouvement()
{
    if(m_nomAction == "marcher" || m_nomAction == "courir")
    {
        m_enMouvement = true;
    }
    else
    {
        m_enMouvement = false;
    }
}

Images_Classe::Images_Classe(UneCreature *uneCreature, QSize const& taille)
{
    m_uneCreature = uneCreature;
    m_taille.setWidth((int)((double)taille.width()*m_uneCreature->propX()));
    m_taille.setHeight((int)((double)taille.height()*m_uneCreature->propY()));
}

void Images_Classe::redimentionne(QSize const& nouvelle)
{
    m_taille.setWidth((int)((double)nouvelle.width()*m_uneCreature->propX()));
    m_taille.setHeight((int)((double)nouvelle.height()*m_uneCreature->propY()));
    if(m_images.isEmpty())
        return;
    for(QMap<QString, Images_action*>::iterator it = m_images.begin(); it != m_images.end(); it++)
    {
        if(!it.value()->redimentionne(m_taille))
        {
            delete it.value();
            m_images.erase(it);
        }
    }
}

Images_action *Images_Classe::getImagesAction(QString const& nomAction)
{
    if(!m_images.contains(nomAction))
        m_images[nomAction] = new Images_action(m_uneCreature->classe(), nomAction, m_taille);
    return m_images[nomAction];
}

Images_Classes::Images_Classes(QMap<QString, UneCreature*>creatures, QSize const& taille)
{
    for(QMap<QString, UneCreature*>::iterator it = creatures.begin(); it != creatures.end(); it++)
    {
        m_creatures[it.value()->classe()] = new Images_Classe(it.value(), taille);
    }
}

Images_Classe *Images_Classes::getImagesUneCreature(QString const& nom) const
{
    if(!m_creatures.contains(nom))
        return 0;
    return m_creatures[nom];
}

void Images_Classes::redimentionne(QSize const& taille)
{
    for(QMap<QString, Images_Classe*>::iterator it = m_creatures.begin(); it != m_creatures.end(); it++)
    {
        it.value()->redimentionne(taille);
    }
}

Images_Classes::~Images_Classes()
{
    for(QMap<QString, Images_Classe*>::iterator it = m_creatures.begin(); it != m_creatures.end(); it++)
    {
        delete it.value();
    }
}
