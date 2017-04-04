#ifndef EDITERRESSOURCES_H
#define EDITERRESSOURCES_H

#include <QDialog>
#include <QInputDialog>
#include "inventory/resources.h"
#include <QFileDialog>

namespace Ui {
class EditerRessources;
}

class EditerRessources : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerRessources(QWidget *parent, Resources *ressources);
    ~EditerRessources();
    void ajouteRessource(Resource *ressource);
    void ajouteEquipement(OutfitModel *equipement);
    void ajouteArme(WeaponModel *arme);
    void supprimeRessource(QString const& nom);
    void supprimeEquipement(QString const& nom);
    void supprimeArme(QString const& nom);
    void editeRessource(Resource *ressource);
    void editeEquipement(OutfitModel *equipement);
    void editeArme(WeaponModel *arme);
    void charge(const QString &nom);
    void clear();
    void enregistre(QString const& nom);

public slots:

    void nouvelle_selection(QString const& nom);
    void accepter();
    void ajoute();
    void supprime();
    void nouvelleImage();

private:
    QString m_ressourceActuelle;
    Ui::EditerRessources *ui;
    Resources *m_ressources;
};

#endif // EDITERRESSOURCES_H
