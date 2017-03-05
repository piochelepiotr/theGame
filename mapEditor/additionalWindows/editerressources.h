#ifndef EDITERRESSOURCES_H
#define EDITERRESSOURCES_H

#include <QDialog>
#include <QInputDialog>
#include "infoMonde/lesressources.h"
#include <QFileDialog>

namespace Ui {
class EditerRessources;
}

class EditerRessources : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerRessources(QWidget *parent, LesRessources *ressources);
    ~EditerRessources();
    void ajouteRessource(Ressource *ressource);
    void ajouteEquipement(EquipementBase *equipement);
    void ajouteArme(ArmeBase *arme);
    void supprimeRessource(QString const& nom);
    void supprimeEquipement(QString const& nom);
    void supprimeArme(QString const& nom);
    void editeRessource(Ressource *ressource);
    void editeEquipement(EquipementBase *equipement);
    void editeArme(ArmeBase *arme);
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
    LesRessources *m_ressources;
};

#endif // EDITERRESSOURCES_H
