#ifndef EDITERMONSTRES_H
#define EDITERMONSTRES_H

#include <QDialog>
#include "editentity.h"
#include "graphic/numberButton.h"
#include <QComboBox>
#include "inventory/resources.h"
#include <QDoubleSpinBox>

namespace Ui {
class EditerMonstres;
}

class EditerMonstres : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerMonstres(QWidget *parent, Resources *ressources);
    ~EditerMonstres();
    QString monstre_to_texte();
    void texte_to_monstre(QString const& text);
    void chargeMonstres();

public slots:

    void ajouterRessource();
    void ressourceSupprimme(int num);
    void enregistrerMonstre(QString nomAlternatif = "");
    void chargeMonstre(QString const& nom);
    void supprimeMonstre(QString const& nom);
    void accepter();
    void clear();
    void changeMonstre(QString const& ancien,QString const& nouveau);
    
private:
    Ui::EditerMonstres *ui;
    int m_nbrRessources;
    Resources *m_lesRessources;
    EditerCreature *m_creature;
};

#endif // EDITERMONSTRES_H
