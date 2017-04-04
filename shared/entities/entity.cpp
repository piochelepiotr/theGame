#include "entities/entity.h"
#include "scenery/data.h"

Entity::Entity(const QString &name, QString const& classe, Data *donnees_editeur)
{
    m_fightId = -1;
    m_donnees_editeur = donnees_editeur;
    m_name = name;
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
    QMap<QString,SpellModel*> spells = m_donnees_editeur->resources->getCreature(classe)->getSpells();
    for(QMap<QString,SpellModel*>::const_iterator it = spells.begin(); it != spells.end() ; it++)
    {
        m_spells[it.value()->name()] = it.value()->spellNiveau(1);
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
    texte += m_name+'*';
    texte += m_classe+'*';
    texte += QString::number(m_posmapx)+'*';
    texte += QString::number(m_posmapy)+'*';
    texte += QString::number((int)isMonster());
    return texte;
}

void Entity::setFightId(int fightId)
{
    if(fightId != -1)
    {
        m_vie = getTotalVie();
        m_posHorsFight = QPoint(m_posmapx,m_posmapy);
    }
    else
    {
        m_posmapx = m_posHorsFight.x();
        m_posmapy = m_posHorsFight.y();
    }
    m_fightId = fightId;
}

void Entity::perdVie(int degats)
{
    m_vie -= degats;
    if(m_vie < 0)
        m_vie = 0;
}

bool Entity::peutUtiliserSpell(QString const& name)
{
    return m_pc_fight >= getSpell(name)->points_fight();
}

Spell *Entity::getSpell(QString const& name)
{
    if(m_spells.contains(name))
    {
        return m_spells[name];
    }
    else
    {
        qDebug("SORT DEMANDE N'EXISTE PAS");
        return m_donnees_editeur->resources->getSpell("Coup de poing")->spellNiveau(1);
    }
}

QString Entity::gagneFinFight(int ,bool victoire)
{
    if(victoire)
    {
        return m_name+"/0";//le gain est bien ?
    }
    else
    {
        return m_name+"/"+"0";
    }
}


