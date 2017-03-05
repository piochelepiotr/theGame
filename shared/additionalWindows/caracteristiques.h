#ifndef CARACTERISTIQUES_H
#define CARACTERISTIQUES_H

#include <QDialog>
#include "infoJoueur/personnage.h"
#include "graphicElements/items.h"
#include "network/reseau.h"
#include "infoJoueur/inventaire.h"
#include "elementsMonde/decors.h"
#include <QTableWidgetItem>
#include <QCursor>
#include <QtTest/QTest>
#include <QMessageBox>
#include "infoMonde/recettes.h"
#include "description_sort.h"
#include "graphicElements/layoutdescriptionsort.h"

namespace Ui {
class Caracteristiques;
}

class Caracteristiques : public QDialog
{
    Q_OBJECT

public slots:

    void cotedclique(int num);
    void cotegclique(int num);
    void coteddbclique(int num);
    void cotegdbclique(int num);

    void decriRess(Ressource *ress);
    void decriObj(Equipement *obj);
    void decriArme(Arme *arme);

    void metEquip(int num);
    void metArme(int num);

    
public:
    Caracteristiques(QWidget *parent, Personnage *perso, Reseau *reseau, Donnees_editeur *donnees_editeur);
    ~Caracteristiques();
    void caracteristiques();
    void competences();
    
private:
    Ui::Caracteristiques *ui;
    Inventaire *m_inventaire;
    Items *m_equipementsD;
    Items *m_equipementsG;
    Personnage *m_perso;
    Reseau *m_reseau;
    Donnees_editeur *m_donnees_editeur;
    QMap<QString,QLabel*>m_textes_metiers;
    Description_sort *m_description_sort;
};

#endif // CARACTERISTIQUES_H
