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
    explicit SpellLayout(Spell *spell);

signals:

    void clique(QString const& name);

public slots:

protected:

    bool eventFilter(QObject *, QEvent *);

private:
    QString m_name;

};

#endif // LAYOUTUNSORT_H
