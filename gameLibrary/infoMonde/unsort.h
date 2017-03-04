#ifndef UNSORT_H
#define UNSORT_H

#include <QString>
#include <QVector>
#include "infoJoueur/sort.h"
#include "additionalActions/constantes.h"

class UnSort
{
public:
    UnSort(QString const& donnees);
    Sort *sortNiveau(int niveau) const { return m_niveaux[niveau]; }
    QString nom() const { return m_nom; }
    static UnSort *nouveau(QString const& nom);
    ~UnSort();
    void recharge(QString const& donnees);
private:
    QVector<Sort*>m_niveaux;
    QString m_nom;
    int m_niveau;
};

#endif // UNSORT_H
