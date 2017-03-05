#include "creature.h"
#include "elementsMonde/donnees_editeur.h"

Creature::Creature(const QString &nom, QString classe, Donnees_editeur *donnees_editeur)
{
    m_enCombat = false;
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
    QMap<QString,UnSort*> sorts = m_donnees_editeur->ressources->getClasse(classe)->sorts();
    for(QMap<QString,UnSort*>::const_iterator it = sorts.begin(); it != sorts.end() ; it++)
    {
        m_sorts[it.value()->nom()] = it.value()->sortNiveau(1);
    }
}

Creature::~Creature()
{

}

void Creature::setPosMap(int x, int y)
{
    m_posmapx = x;
    m_posmapy = y;
}


int Creature::getBonusVie() const
{
    return 0;
}

int Creature::getBonusForce() const
{
    return 0;
}

int Creature::getBonusPC() const
{
    return 0;
}

QString Creature::caracteristiques() const
{
    QString caracteristiques;
    caracteristiques += QObject::trUtf8("vie : ")+QString::number(getTotalVie())+ " ("+QString::number(getBaseVie()) + "+" + QString::number(getBonusVie())+ "), ";
    caracteristiques += QObject::trUtf8("force : ") + QString::number(getTotalForce())+ " ("+QString::number(getBaseForce()) + "+" + QString::number(getBonusForce())+"), ";
    caracteristiques += QObject::trUtf8("PC : ") + QString::number(getTotalPC())+ " ("+QString::number(getBasePC()) + "+" + QString::number(getBonusPC())+")";
    return caracteristiques;
}

QString Creature::important()
{
    QString texte;
    texte += m_nom+'*';
    texte += m_classe+'*';
    texte += QString::number(m_posmapx)+'*';
    texte += QString::number(m_posmapy)+'*';
    return texte;
}

void Creature::setEnCombat(bool enCombat)
{
    if(enCombat)
    {
        m_vie = getTotalVie();
        m_posHorsCombat = QPoint(m_posmapx,m_posmapy);
    }
    else
    {
        m_posmapx = m_posHorsCombat.x();
        m_posmapy = m_posHorsCombat.y();
    }
    m_enCombat = enCombat;
}

void Creature::perdVie(int degats)
{
    m_vie -= degats;
    if(m_vie < 0)
        m_vie = 0;
}

bool Creature::peutUtiliserSort(QString const& nom)
{
    return m_pc_combat >= getSort(nom)->points_combat();
}

Sort *Creature::getSort(QString const& nom)
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

QString Creature::gagneFinCombat(int ,bool victoire)
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


