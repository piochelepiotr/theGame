#ifndef BUTTONOBJECT_H
#define BUTTONOBJECT_H

#include <QAbstractButton>
#include "scenery/object.h"

/***
 * This class is used in the map editor to display the objects you can choose to put on the map
 */

class ButtonObject : public QAbstractButton
{
public:
    ButtonObject(Objet *object);
};

#endif // BUTTONOBJECT_H
