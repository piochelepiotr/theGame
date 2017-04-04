#include "entities/entity.h"
#include "scenery/data.h"

Entity::Entity(const QString &nom, QString const& classe, Data *donnees_editeur)
{
    m_enFight = false;
    m_donnees_editeur = donnees_editeur;
    m_nom = nom;
    m_classe = classe;
    m_posX = 0;
    m_posY = 0;
    m_posZ = 0;
    m_base_vie = 50;
    m_base_force = 0;
    m_base_pc = 10;
    m_vie = m_base_vie;
    m_posmapx = 0;
    m_posmapy = 1;
    m_niveau = 1;
    QMap<QString,SpellModel*> sorts = m_donnees_editeur->ressources->getCreature(classe)->getSpells();
    for(QMap<QString,SpellModel*>::const_iterator it = sorts.begin(); it != sorts.end() ; it++)
    {
        m_sorts[it.value()->nom()] = it.value()->sortNiveau(1);
    }
}

Entity::~Entity()
{

}

void Entity::setPosMap(int x, int y)
{
    m_posmapx = x;
    m_posmapy = y;
}


int Entity::getBonusVie() const
{
    return 0;
}

int Entity::getBonusForce() const
{
    return 0;
}

int Entity::getBonusPC() const
{
    return 0;
}

QString Entity::caracteristiques() const
{
    QString caracteristiques;
    caracteristiques += QObject::trUtf8("vie : ")+QString::number(getTotalVie())+ " ("+QString::number(getBaseVie()) + "+" + QString::number(getBonusVie())+ "), ";
    caracteristiques += QObject::trUtf8("force : ") + QString::number(getTotalForce())+ " ("+QString::number(getBaseForce()) + "+" + QString::number(getBonusForce())+"), ";
    caracteristiques += QObject::trUtf8("PC : ") + QString::number(getTotalPC())+ " ("+QString::number(getBasePC()) + "+" + QString::number(getBonusPC())+")";
    return caracteristiques;
}

QString Entity::important()
{
    QString texte;
    texte += m_nom+'*';
    texte += m_classe+'*';
    texte += QString::number(m_posmapx)+'*';
    texte += QString::number(m_posmapy)+'*';
    texte += QString::number((int)isMonster());
    return texte;
}

void Entity::setEnFight(bool enFight)
{
    if(enFight)
    {
        m_vie = getTotalVie();
        m_posHorsFight = QPoint(m_posmapx,m_posmapy);
    }
    else
    {
        m_posmapx = m_posHorsFight.x();
        m_posmapy = m_posHorsFight.y();
    }
    m_enFight = enFight;
}

void Entity::perdVie(int degats)
{
    m_vie -= degats;
    if(m_vie < 0)
        m_vie = 0;
}

bool Entity::peutUtiliserSort(QString const& nom)
{
    return m_pc_fight >= getSort(nom)->points_fight();
}

Spell *Entity::getSort(QString const& nom)
{
    if(m_sorts.contains(nom))
    {
        return m_sorts[nom];
    }
    else
    {
        qDebug("SORT DEMANDE N'EXISTE PAS");
        return m_donnees_editeur->ressources->getSort("Coup de poing")->sortNiveau(1);
    }
}

QString Entity::gagneFinFight(int ,bool victoire)
{
    if(victoire)
    {
        return m_nom+"/0";//le gain est bien ?
    }
    else
    {
        return m_nom+"/"+"0";
    }
}


