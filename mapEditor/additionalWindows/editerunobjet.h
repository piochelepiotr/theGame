#ifndef EDITERUNOBJET_H
#define EDITERUNOBJET_H

#include <QDialog>
#include "elementsMonde/decors.h"
#include "additionalActions/actionObjets.h"
#include <QFileDialog>


namespace Ui {
    class EditerUnObjet;
}

class EditerUnObjet : public QDialog
{
    Q_OBJECT

public:
    explicit EditerUnObjet(QWidget *parent,bool *ok,Objet *objet, bool creation,int lcase, int hcase, QString *chemin = 0, bool *supprimer = 0);
    ~EditerUnObjet();
    void valeurs();

private:
    Ui::EditerUnObjet *ui;
    bool *m_ok;
    bool *m_supprimer;
    Objet *m_objet;
    QString *m_chemin;
    int m_lcase;
    int m_hcase;

public slots:

    void accepter();
    void refuser();
    void supprimer();

};

#endif // EDITERUNOBJET_H
