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
    explicit EditerRessources(QWidget *parent, Resources *resources);
    ~EditerRessources();
    void ajouteRessource(Resource *resource);
    void ajouteEquipement(OutfitModel *equipement);
    void ajouteArme(WeaponModel *arme);
    void supprimeRessource(QString const& name);
    void supprimeEquipement(QString const& name);
    void supprimeArme(QString const& name);
    void editeRessource(Resource *resource);
    void editeEquipement(OutfitModel *equipement);
    void editeArme(WeaponModel *arme);
    void charge(const QString &name);
    void clear();
    void enregistre(QString const& name);

public slots:

    void nouvelle_selection(QString const& name);
    void accepter();
    void ajoute();
    void supprime();
    void nouvelleImage();

private:
    QString m_resourceActuelle;
    Ui::EditerRessources *ui;
    Resources *m_resources;
};

#endif // EDITERRESSOURCES_H
