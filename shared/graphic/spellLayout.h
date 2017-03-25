#ifndef LAYOUTUNSORT_H
#define LAYOUTUNSORT_H

#include <QHBoxLayout>
#include "entities/spell.h"
#include "scenery/constants.h"
#include <QLabel>
#include <QEvent>

class SpellLayout : public QWidget
{
    Q_OBJECT
public:
    explicit SpellLayout(Spell *sort);

signals:

    void clique(QString const& nom);

public slots:

protected:

    bool eventFilter(QObject *, QEvent *);

private:
    QString m_nom;

};

#endif // LAYOUTUNSORT_H
