#ifndef EDITERMONSTREDELAMAP_H
#define EDITERMONSTREDELAMAP_H

#include <QDialog>
#include <QMap>
#include <QString>
#include "graphic/numberButton.h"
#include <QComboBox>
#include <QDoubleSpinBox>

namespace Ui {
class EditerMonstreDeLaMap;
}

class EditerMonstreDeLaMap : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerMonstreDeLaMap(QWidget *parent, QMap<QString, double> *monstres, QStringList nameMonstres);
    ~EditerMonstreDeLaMap();

public slots:
    void addRow();
    void accepter();
    void supprimer(int num);
    
private:
    Ui::EditerMonstreDeLaMap *ui;
    int m_nbr;
    QMap<QString, double> *m_monstres;
    QStringList m_nameMonstres;
};

#endif // EDITERMONSTREDELAMAP_H
