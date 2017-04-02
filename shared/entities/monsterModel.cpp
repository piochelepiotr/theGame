#include "entities/monsterModel.h"
#include "entities/monster.h"
#include "scenery/data.h"

MonsterModel::MonsterModel(const QString &text, const QMap<QString, SpellModel *> &sorts)
{
    QStringList liste = text.split('/');
    liste.removeAll("");
    m_class = liste[0];
    liste.pop_front();
    m_propX = liste[0].toDouble();
    liste.pop_front();
    m_propY = liste[0].toDouble();
    liste.pop_front();
    while(liste[0] != "MONSTRE")
    {
        m_spells[liste[0]] = sorts[liste[0]];
        liste.pop_front();
    }
    liste.pop_front();
    m_lifeMin = liste[0].toInt();
    liste.pop_front();
    m_lifeMax = liste[0].toInt();
    liste.pop_front();
    m_levelMin = liste[0].toInt();
    liste.pop_front();
    m_levelMax = liste[0].toInt();
    liste.pop_front();
    while(liste.length()>1)
    {
        m_ressourcesDropables[liste[0]] = liste[1].toDouble();
        liste.pop_front();
        liste.pop_front();
    }
}

Monster *MonsterModel::generateMonster(int posX,int posY,int posZ,int posMapX,int posMapY,Data *donnees_editeur,QString const& name)
{
    int niveau = m_levelMin + qrand()%(m_levelMax-m_levelMin+1);
    //vie = a*niveau+b
    int vie = m_lifeMin;
    if(m_levelMin != m_levelMax && m_lifeMin != m_lifeMax)//donc niveaumax != 0
    {
        double a = ((double)(m_lifeMax-m_lifeMin))/((double)(m_levelMax-m_levelMin));
        double b = (((double)m_lifeMax)/((double)m_lifeMin))/a;
        vie = (int) (a*((double)(niveau))+b);
    }
    return new Monster(name,m_class,donnees_editeur,posX,posY,posZ,posMapX,posMapY,vie,niveau);
}
