#include "entities/entityImage.h"

ImagesAction::ImagesAction(QString const& name_classe, QString const& name_action, QSize const& size)
{
    m_nbrUtilisateur = 1;
    m_nameClasse = name_classe;
    m_nameAction = name_action;
    definieEnMouvement();
    QString chemin = "../data/imagesdespersos/"+ m_nameClasse+"/"+ m_nameAction + "/", chemin2;
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
        if(j == 0)
        {
            qDebug() << "impossible de charger les images de la classe "<<m_nameClasse<<" du chemin "<< chemin2;
        }
    }
}

bool ImagesAction::redimentionne(QSize const& nouvelle)
{
    if(m_nbrUtilisateur < 1)
        return false;
    QString chemin = "../data/imagesdespersos/"+ m_nameClasse +"/"+ m_nameAction + "/", chemin2;
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

QPixmap ImagesAction::getImage(int num, Dir orientation) const
{
    if(num < quantity_images(orientation))
        return m_images[(int)orientation][num];
    return m_images[0][0];
}

void ImagesAction::definieEnMouvement()
{
    if(m_nameAction == "marcher" || m_nameAction == "courir")
    {
        m_enMouvement = true;
    }
    else
    {
        m_enMouvement = false;
    }
}

ImagesEntity::ImagesEntity(EntityModel *uneCreature, QSize const& taille)
{
    m_uneCreature = uneCreature;
    m_taille.setWidth((int)((double)taille.width()*m_uneCreature->propX()));
    m_taille.setHeight((int)((double)taille.height()*m_uneCreature->propY()));
}

void ImagesEntity::redimentionne(QSize const& nouvelle)
{
    m_taille.setWidth((int)((double)nouvelle.width()*m_uneCreature->propX()));
    m_taille.setHeight((int)((double)nouvelle.height()*m_uneCreature->propY()));
    if(m_images.isEmpty())
        return;
    for(QMap<QString, ImagesAction*>::iterator it = m_images.begin(); it != m_images.end(); it++)
    {
        if(!it.value()->redimentionne(m_taille))
        {
            delete it.value();
            m_images.erase(it);
        }
    }
}

ImagesAction *ImagesEntity::getImagesAction(QString const& nameAction)
{
    if(!m_images.contains(nameAction))
        m_images[nameAction] = new ImagesAction(m_uneCreature->getClass(), nameAction, m_taille);
    return m_images[nameAction];
}

ImagesEntities::ImagesEntities(QMap<QString, EntityModel*>creatures, QSize const& taille)
{
    for(QMap<QString, EntityModel*>::iterator it = creatures.begin(); it != creatures.end(); it++)
    {
        m_creatures[it.value()->getClass()] = new ImagesEntity(it.value(), taille);
    }
}

ImagesEntity *ImagesEntities::getImagesUneCreature(QString const& name) const
{
    if(!m_creatures.contains(name))
        return 0;
    return m_creatures[name];
}

void ImagesEntities::redimentionne(QSize const& taille)
{
    for(QMap<QString, ImagesEntity*>::iterator it = m_creatures.begin(); it != m_creatures.end(); it++)
    {
        it.value()->redimentionne(taille);
    }
}

ImagesEntities::~ImagesEntities()
{
    for(QMap<QString, ImagesEntity*>::iterator it = m_creatures.begin(); it != m_creatures.end(); it++)
    {
        delete it.value();
    }
}
