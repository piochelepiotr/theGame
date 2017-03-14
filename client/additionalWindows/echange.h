#ifndef ECHANGE_H
#define ECHANGE_H

#include <QDialog>
#include "entities/character.h"
#include "inventory/inventory.h"
#include "network/reseau.h"

namespace Ui {
class Echange;
}

class Echange : public QDialog
{
    Q_OBJECT
    
public:
    explicit Echange(Personnage *personnage, QString const& nom_autre, Reseau *reseau);

    ~Echange();

public slots:


    
private:
    Ui::Echange *ui;
    bool m_accepte;
    QString m_nom_autre;
    Reseau *m_reseau;
    Personnage *m_personnage;
};

#endif // ECHANGE_H
