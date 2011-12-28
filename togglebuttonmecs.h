#ifndef TOGGLEBUTTONMECS_H
#define TOGGLEBUTTONMECS_H

#include "buttonmecs.h"
#include "itemaction.h"

class ToggleButtonMECS : public ButtonMECS
{
public:
    ToggleButtonMECS(int , int );
    QString GetName();
    QGridLayout *GetPropertiesWidgets();
private:
    ItemAction *onUpAction;
    ItemAction *onDownAction;
};

#endif // TOGGLEBUTTONMECS_H
