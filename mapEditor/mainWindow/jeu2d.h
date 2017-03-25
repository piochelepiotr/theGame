#ifndef JEU2D_H
#define JEU2D_H

#include "graphic/gamescene.h"



class Jeu2d : public GameScene
{
    Q_OBJECT

public slots:

public:
    Jeu2d(QSize const& size, QLabel *texte, Data *donnees_editeur);
    bool peutAjouterCasecbt(int x, int y);
private:

};

#endif // JEU2D_H
//stop
