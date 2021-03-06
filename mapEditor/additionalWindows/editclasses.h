#ifndef EDITERCLASSES_H
#define EDITERCLASSES_H

#include <QDialog>
#include "editjob.h"

namespace Ui {
class EditerClasses;
}

class EditerClasses : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerClasses(QWidget *parent);
    ~EditerClasses();
    void enregistrerClasse(int classe);
    void chargeClasseActuelle();
    void clearClasse();
    QString classe_to_texte();
    void texte_to_classe(const QString &texte);
    void chargeClasses();

public slots:

    void ajouterClasse();
    void supprimerClasseActuelle();
    void ajouterSpell();
    void accepter();
    void supprimerSpell(int num);
    void changeClasse(int nouvelle);
    
private:
    Ui::EditerClasses *ui;
    int m_classeActuelle;
    int m_nbrSpells;
    QVector<NumberButton*>m_boutonsSpells;
};

#endif // EDITERCLASSES_H
