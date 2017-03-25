#include "windowendfight.h"
#include "ui_windowendfight.h"

WindowEndFight::WindowEndFight(const QString &texte, QWidget *parent, Character *perso) :
    QDialog(parent),
    ui(new Ui::WindowEndFight)
{
    ui->setupUi(this);
    QStringList liste = texte.split('*');
    QStringList gagnants = liste[0].split("//");
    QStringList perdants = liste[1].split("//");
    Character *perso2 = 0;
    for(int i = 0; i < gagnants.size(); i++)
    {
        if(!gagnants[i].isEmpty())
        {
            if(gagnants[i].section('/',0,0) == perso->getNom())
                perso2 = perso;
            else
                perso2 = 0;
            ui->layout_gagnants->addLayout(new FightWinnings(gagnants[i],perso2));
        }
    }
    for(int i = 0; i < perdants.size(); i++)
    {
        if(!perdants[i].isEmpty())
        {
            if(perdants[i].section('/',0,0) == perso->getNom())
                perso2 = perso;
            else
                perso2 = 0;
            ui->layout_perdants->addLayout(new FightWinnings(perdants[i],perso2));
        }
    }
    this->exec();
}

WindowEndFight::~WindowEndFight()
{
    delete ui;
}
