#ifndef LAYOUTUNSORT_H
#define LAYOUTUNSORT_H

#include <QHBoxLayout>
#include "infoJoueur/sort.h"
#include "additionalActions/constantes.h"
#include <QLabel>
#include <QEvent>

class LayoutUnSort : public QWidget
{
    Q_OBJECT
public:
    explicit LayoutUnSort(Sort *sort);

signals:

    void clique(QString const& nom);

public slots:

protected:

    bool eventFilter(QObject *, QEvent *);

private:
    QString m_nom;

};

#endif // LAYOUTUNSORT_H
