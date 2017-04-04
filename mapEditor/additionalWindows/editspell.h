#ifndef EDITERUNSORT_H
#define EDITERUNSORT_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "scenery/constants.h"
#include "inventory/resources.h"

namespace Ui {
class EditerUnSort;
}

class EditerUnSort : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerUnSort(QWidget *parent, SpellModel *editer, bool creation);
    ~EditerUnSort();
    void charge();
    void enregistre();
    static void supprimer(QString const& nom);

public slots:
    void accepter();

private:
    Ui::EditerUnSort *ui;
    SpellModel *m_editer;
    bool m_creation;
};

#endif // EDITERUNSORT_H
