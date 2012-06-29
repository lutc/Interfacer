#ifndef INDICATORMECS_H
#define INDICATORMECS_H

#include "commonitemmecs.h"

class IndicatorMECS : public CommonItemMECS
{
public:
    IndicatorMECS(int, int);


    QString GetName();
    QString GetTextName();

    QGridLayout *GetPropertiesWidgets();
    void AcceptWidgetsProperties();
    void Copy(CommonItemMECS *);

    virtual QString Save();
};

#endif // INDICATORMECS_H
