#include "graphic/fightWinnings.h"

GainUnPersoCombat::GainUnPersoCombat(QString const& text,Personnage *perso) :
    QHBoxLayout()
{
    qDebug() << "texte combattant" << text;
    QStringList liste = text.split('/');
    addWidget(new QLabel(liste[0]));
    addWidget(new QLabel("xp gagné: "+liste[1]));
    if(perso)
    {
        perso->gagneXp(liste[1].toInt());
    }
}
