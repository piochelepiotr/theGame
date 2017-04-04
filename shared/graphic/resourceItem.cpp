#include "graphic/resourceItem.h"

ResourceItem::ResourceItem(Resource *resource, int quantite, int num) : QLabel()
{
    m_image = resource->imagep();
    m_quantite = quantite;
    faitImage();
    m_num = num;
    setToolTip(resource->longue_description());
    if(m_num != -1)
        installEventFilter(this);
}

ResourceItem::ResourceItem(Outfit *equipement, int quantite, int num)
{
    m_image = equipement->getRessource()->imagep();
    m_quantite = quantite;
    faitImage();
    m_num = num;
    setToolTip(equipement->longue_description());
    if(m_num != -1)
        installEventFilter(this);
}

ResourceItem::ResourceItem(Weapon *arme, int quantite, int num)
{
    m_image = arme->getEquipement()->getRessource()->imagep();
    m_quantite = quantite;
    faitImage();
    m_num = num;
    setToolTip(arme->longue_description());
    if(m_num != -1)
        installEventFilter(this);
}

ResourceItem::ResourceItem(OutfitModel *equipement_base,int quantite, int num)
{
    m_image = equipement_base->getRessource()->imagep();
    m_quantite = quantite;
    faitImage();
    m_num = num;
    setToolTip(equipement_base->longue_description());
    if(m_num != -1)
        installEventFilter(this);
}

ResourceItem::ResourceItem(WeaponModel *arme_base,int quantite, int num)
{
    m_image = arme_base->getEquipement()->getRessource()->imagep();
    m_quantite = quantite;
    faitImage();
    m_num = num;
    setToolTip(arme_base->longue_description());
    if(m_num != -1)
        installEventFilter(this);
}

ResourceItem::ResourceItem(bool enable)
{
    setPixmap(QPixmap("../data/interface/vide.png").scaled(40,40));
    if(!enable)
        setEnabled(false);
}

void ResourceItem::faitImage()
{
    QPixmap image(m_image);
    if(m_quantite != 1)
    {
        QPainter p(&image);
        QFontMetrics taille(p.font());
        p.fillRect(0,0,taille.width(QString::number(m_quantite))+1, taille.ascent()+1, QColor(50,50,50));
        p.setPen(QColor(255,255,255));
        p.drawText(0,taille.ascent(),QString::number(m_quantite));
        p.end();
    }
    setPixmap(image);
}

void ResourceItem::enleve(int quantite)
{
    m_quantite -= quantite;
    if(m_quantite > 0)
        faitImage();
}

void ResourceItem::ajoute(int quantite)
{
    m_quantite += quantite;
    faitImage();
}

bool ResourceItem::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this && ev->type() == QEvent::MouseButtonPress)
    {
        emit clique(m_num);
        return true;
    }
    else if(obj == this && ev->type() == QEvent::MouseButtonDblClick)
    {
        emit dbclique(m_num);
        return true;
    }
    else
    {
        return QLabel::eventFilter(obj,ev);
    }
}
