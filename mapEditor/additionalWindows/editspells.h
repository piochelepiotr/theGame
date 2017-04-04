#ifndef EDITERSORTS_H
#define EDITERSORTS_H

#include <QDialog>
#include "editjob.h"
#include "editspell.h"
#include "inventory/resources.h"

namespace Ui {
class EditerSpells;
}

class EditerSpells : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerSpells(QWidget *parent, Resources *resources);
    ~EditerSpells();

public slots:

    void chargeSpells();
    void ajouterNouveau(const QString &lenom = QString());
    void supprimeSpell(int i);
    void modifierSpell(int i);
    
private:
    Ui::EditerSpells *ui;
    QVector<NumberButton*>bouts_editer;
    QVector<NumberButton*>bouts_supprimer;
    Resources *m_resources;
};

#endif // EDITERSORTS_H
