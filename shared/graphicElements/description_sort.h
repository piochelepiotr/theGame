#ifndef DESCRIPTION_SORT_H
#define DESCRIPTION_SORT_H

#include <QFrame>
#include "infoMonde/lesressources.h"

namespace Ui {
class Description_sort;
}

class Description_sort : public QFrame
{
    Q_OBJECT
    
public:
    explicit Description_sort(UnSort *sort = 0);
    ~Description_sort();
    void setSort(UnSort *sort);
    
private:
    Ui::Description_sort *ui;
};

#endif // DESCRIPTION_SORT_H
