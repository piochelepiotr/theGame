#ifndef INTERJOUEUR_H
#define INTERJOUEUR_H

#include <QDialog>

namespace Ui {
class InterJoueur;
}

enum Inter{Annuler,Echange,Defi};

class InterJoueur : public QDialog
{
    Q_OBJECT

public slots:

    void echange();
    void defi();
    
public:
    explicit InterJoueur(QWidget *parent, QString const& name, Inter *inter);
    ~InterJoueur();
    
private:
    Ui::InterJoueur *ui;
    Inter *m_inter;
};

#endif // INTERJOUEUR_H
