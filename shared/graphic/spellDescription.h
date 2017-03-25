#ifndef DESCRIPTION_SORT_H
#define DESCRIPTION_SORT_H

#include <QFrame>
#include "inventory/resources.h"

namespace Ui {
class SpellDescription;
}

class SpellDescription : public QFrame
{
    Q_OBJECT
    
public:
    explicit SpellDescription(SpellModel *sort = 0);
    ~SpellDescription();
    void setSort(SpellModel *sort);
    
private:
    Ui::SpellDescription *ui;
};

#endif // DESCRIPTION_SORT_H
