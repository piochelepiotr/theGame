#ifndef EDITERUNSORT_H
#define EDITERUNSORT_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "additionalActions/constantes.h"
#include "infoMonde/lesressources.h"

namespace Ui {
class EditerUnSort;
}

class EditerUnSort : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerUnSort(QWidget *parent, UnSort *sort, bool creation);
    ~EditerUnSort();
    void charge();
    void enregistre();
    static void supprimer(QString const& nom);

public slots:
    void accepter();

private:
    Ui::EditerUnSort *ui;
    UnSort *m_sort;
    bool m_creation;
};

#endif // EDITERUNSORT_H
