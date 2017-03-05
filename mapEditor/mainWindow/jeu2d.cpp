#include "jeu2d.h"

Jeu2d::Jeu2d(QSize const& size, QLabel *texte,Donnees_editeur *donnees_editeur) : GameScene(size,texte,donnees_editeur)
{

}

bool Jeu2d::peutAjouterCasecbt(int x, int y)
{
    int nombreCasesCombat = 0;
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_dataMap->caseCombat(m_equipe,i).x() != -1)
            nombreCasesCombat++;
        if(m_dataMap->caseCombat(m_equipe,i).x() == x && m_dataMap->caseCombat(m_equipe,i).y() == y)
        {
            return false;
        }
    }
    return nombreCasesCombat < MAX_PAR_EQUIP;
}


