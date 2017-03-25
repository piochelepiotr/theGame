#ifndef CARACTERISTIQUES_H
#define CARACTERISTIQUES_H

#include <QDialog>
#include "entities/character.h"
#include "graphic/resourceItems.h"
#include "network/reseau.h"
#include "inventory/inventory.h"
#include "scenery/scenery.h"
#include <QTableWidgetItem>
#include <QCursor>
#include <QtTest/QTest>
#include <QMessageBox>
#include "jobs/recipes.h"
#include "graphic/spellDescription.h"
#include "graphic/spellDescriptionLayout.h"

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

    void decriRess(Resource *ress);
    void decriObj(Outfit *obj);
    void decriArme(Weapon *arme);

    void metEquip(int num);
    void metArme(int num);

    
public:
    Caracteristiques(QWidget *parent, Character *perso, Reseau *reseau, Data *donnees_editeur);
    ~Caracteristiques();
    void caracteristiques();
    void competences();
    
private:
    Ui::Caracteristiques *ui;
    Inventory *m_inventaire;
    ResourceItems *m_equipementsD;
    ResourceItems *m_equipementsG;
    Character *m_perso;
    Reseau *m_reseau;
    Data *m_donnees_editeur;
    QMap<QString,QLabel*>m_textes_metiers;
    SpellDescription *m_description_sort;
};

#endif // CARACTERISTIQUES_H
