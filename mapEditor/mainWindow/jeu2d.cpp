#include "jeu2d.h"

Jeu2d::Jeu2d(QSize const& size, QLabel *texte,Data *donnees_editeur) : GameScene(size,texte,donnees_editeur)
{

}

bool Jeu2d::peutAjouterCasecbt(int x, int y)
{
    int nombreCasesFight = 0;
    for(int i = 0; i < MAX_PAR_EQUIP; i++)
    {
        if(m_dataMap->caseFight(m_equipe,i).x() != -1)
            nombreCasesFight++;
        if(m_dataMap->caseFight(m_equipe,i).x() == x && m_dataMap->caseFight(m_equipe,i).y() == y)
        {
            return false;
        }
    }
    return nombreCasesFight < MAX_PAR_EQUIP;
}


