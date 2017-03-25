#ifndef EDITERMETIER_H
#define EDITERMETIER_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QSpinBox>
#include "scenery/constants.h"
#include "scenery/scenery.h"
#include "inventory/resources.h"
#include "graphic/numberButton.h"

namespace Ui {
class EditerMetier;
}

class EditerMetier : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerMetier(QWidget *parent, Scenery *decors, Resources *ressources);
    ~EditerMetier();
    QString textMetier();
    QString textRecette();
    void enregistreMetier(int index);
    void chargeMetiers();
    void texte_to_metier(QString const& texte);

public slots:

    void changeMetier(int nouveau);
    void changeRecette(int nouveau);
    void ajouteMetier();
    void ajouteIngredient();
    void ajouteObjet();
    void ajouteRecette();
    void supprimerMetier();
    void supprimeRecette();
    void objetSupprime(int obj);
    void ingredientSupprimme(int ingred);
    void enregistreRecette(int index);
    void clearRecette();
    void clearMetier();
    void chargeMetier();
    void chargeRecette();
    void accepter();
    
private:
    Ui::EditerMetier *ui;
    int m_nbrRecettes;
    int m_nbrObjets;
    int m_nbrIngredients;
    int m_metierActuel;
    int m_recetteActuel;


    //infos objets dans l'ordre
    QVector<QComboBox*>m_comboRessources_obtenues;
    QVector<QComboBox*>m_comboObjets;
    QVector<QComboBox*>m_comboSouches;
    QVector<QSpinBox*>m_spinNiveaux;
    QVector<NumberButton*>m_boutonsObj;

    //infos ingrédients dans l'ordre
    QVector<QComboBox*>m_comboRessources;
    QVector<QSpinBox*>m_spinQuantite;
    QVector<NumberButton*>m_boutonsIngr;



    QMap<QString, QString>*m_recettes;
    Resources *m_ressources;
    Scenery *m_decors;
    QStringList m_lesobjets;
    QStringList m_lesressources;
    QMap<QString, Object*>m_objets;
    //bool m_supprimme;
};

#endif // EDITERMETIER_H
