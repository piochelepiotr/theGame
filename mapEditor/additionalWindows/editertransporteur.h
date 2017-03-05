#ifndef EDITERTRANSPORTEUR_H
#define EDITERTRANSPORTEUR_H

#include <QDialog>
#include "elementsMonde/transporteur.h"

namespace Ui {
class EditerTransporteur;
}

class EditerTransporteur : public QDialog
{
    Q_OBJECT

public slots:

    void accepter();
    void refuser();
    void supprimer();

public:
    explicit EditerTransporteur(QWidget *parent, Transporteur *transpo,bool *ok, bool *supprimer);
    ~EditerTransporteur();
    void valeurs();
    
private:
    Ui::EditerTransporteur *ui;
    bool *m_ok;
    bool *m_supr;
    Transporteur *m_transpo;

};

#endif // EDITERTRANSPORTEUR_H
