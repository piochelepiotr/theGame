#ifndef EDITERCREATURE_H
#define EDITERCREATURE_H

#include <QWidget>
#include <QFile>
#include "graphic/numberButton.h"
#include <QInputDialog>
#include <QMessageBox>
#include "scenery/constants.h"
#include "inventory/resources.h"

namespace Ui {
class EditerCreature;
}

class EditerCreature : public QWidget
{
    Q_OBJECT

public:
    explicit EditerCreature(QWidget *parent, Resources *lesRessources);
    ~EditerCreature();
    QString classe_to_texte();
    void texte_to_classe(const QString &texte);
    void chargeClasses(QStringList classes);
    void clearClasse();
    bool classeOuverte() const { return m_classeActuelle >= 0; }

signals:

    void s_supprimeClasse(QString const& nom);
    void s_enregistrerClasse();
    void s_chargerClasse(QString const& nom);
    void s_clear();
    void s_changeClasse(QString const& acien,QString const& nouveau);

public slots:

    void ajouterClasse();
    void supprimerClasseActuelle();
    void ajouterSpell();
    void supprimerSpell(int num);
    void changeClasse(int nouvelle);

private:
    Ui::EditerCreature *ui;
    int m_classeActuelle;
    int m_nbrSpells;
    Resources *m_lesRessources;
};

#endif // EDITERCREATURE_H
