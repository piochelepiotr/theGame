#include "unmonstre.h"
#include "monstre.h"
#include "elementsMonde/donnees_editeur.h"

UnMonstre::UnMonstre(const QString &text, const QMap<QString, UnSort *> &sorts)
{
    QStringList liste = text.split('/');
    liste.removeAll("");
    m_classe = liste[0];
    liste.pop_front();
    m_propX = liste[0].toDouble();
    liste.pop_front();
    m_propY = liste[0].toDouble();
    liste.pop_front();
    while(liste[0] != "MONSTRE")
    {
        m_sorts[liste[0]] = sorts[liste[0]];
        liste.pop_front();
    }
    liste.pop_front();
    m_vieMin = liste[0].toInt();
    liste.pop_front();
    m_vieMax = liste[0].toInt();
    liste.pop_front();
    m_niveauMin = liste[0].toInt();
    liste.pop_front();
    m_niveauMax = liste[0].toInt();
    liste.pop_front();
    while(liste.length()>1)
    {
        m_ressourcesDropables[liste[0]] = liste[1].toDouble();
        liste.pop_front();
        liste.pop_front();
    }
}

Monstre *UnMonstre::genereMonstre(int posX,int posY,int posZ,int posMapX,int posMapY,Donnees_editeur *donnees_editeur,QString const& name)
{
    int niveau = m_niveauMin + qrand()%(m_niveauMax-m_niveauMin+1);
    //vie = a*niveau+b
    int vie = m_vieMin;
    if(m_niveauMin != m_niveauMax && m_vieMin != m_vieMax)//donc niveaumax != 0
    {
        double a = ((double)(m_vieMax-m_vieMin))/((double)(m_niveauMax-m_niveauMin));
        double b = (((double)m_vieMax)/((double)m_vieMin))/a;
        vie = (int) (a*((double)(niveau))+b);
    }
    return new Monstre(name,m_classe,donnees_editeur,posX,posY,posZ,posMapX,posMapY,vie,niveau);
}
