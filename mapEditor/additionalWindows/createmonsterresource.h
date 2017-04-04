#ifndef NOUVELLERESSOURCEMONSTRE_H
#define NOUVELLERESSOURCEMONSTRE_H

#include <QDialog>

namespace Ui {
class NouvelleRessourceMonstre;
}

class NouvelleRessourceMonstre : public QDialog
{
    Q_OBJECT

public:
    explicit NouvelleRessourceMonstre(QWidget *parent = 0);
    ~NouvelleRessourceMonstre();

private:
    Ui::NouvelleRessourceMonstre *ui;
    double m_proba;
    QString m_name;
};

#endif // NOUVELLERESSOURCEMONSTRE_H
