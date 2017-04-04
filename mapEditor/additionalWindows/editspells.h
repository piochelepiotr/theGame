#ifndef EDITERSORTS_H
#define EDITERSORTS_H

#include <QDialog>
#include "editjob.h"
#include "editspell.h"
#include "inventory/resources.h"

namespace Ui {
class EditerSorts;
}

class EditerSorts : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerSorts(QWidget *parent, Resources *ressources);
    ~EditerSorts();

public slots:

    void chargeSorts();
    void ajouterNouveau(const QString &lenom = QString());
    void supprimeSort(int i);
    void modifierSort(int i);
    
private:
    Ui::EditerSorts *ui;
    QVector<NumberButton*>bouts_editer;
    QVector<NumberButton*>bouts_supprimer;
    Resources *m_ressources;
};

#endif // EDITERSORTS_H
