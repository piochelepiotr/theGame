#ifndef EDITERUNSORT_H
#define EDITERUNSORT_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "scenery/constants.h"
#include "inventory/resources.h"

namespace Ui {
class EditerUnSpell;
}

class EditerUnSpell : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerUnSpell(QWidget *parent, SpellModel *editer, bool creation);
    ~EditerUnSpell();
    void charge();
    void enregistre();
    static void supprimer(QString const& name);

public slots:
    void accepter();

private:
    Ui::EditerUnSpell *ui;
    SpellModel *m_editer;
    bool m_creation;
};

#endif // EDITERUNSORT_H
