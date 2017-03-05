#ifndef EDITERSORTS_H
#define EDITERSORTS_H

#include <QDialog>
#include "editermetier.h"
#include "editerunsort.h"
#include "infoMonde/lesressources.h"

namespace Ui {
class EditerSorts;
}

class EditerSorts : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerSorts(QWidget *parent, LesRessources *ressources);
    ~EditerSorts();

public slots:

    void chargeSorts();
    void ajouterNouveau(const QString &lenom = QString());
    void supprimeSort(int i);
    void modifierSort(int i);
    
private:
    Ui::EditerSorts *ui;
    QVector<Bouton*>bouts_editer;
    QVector<Bouton*>bouts_supprimer;
    LesRessources *m_ressources;
};

#endif // EDITERSORTS_H
