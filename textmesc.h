#ifndef TEXTMESC_H
#define TEXTMESC_H

#include "commonitemmecs.h"
class TextMESC : public CommonItemMECS
{
public:
    TextMESC(int , int );

    QString GetName();
    QString GetTextName();

    QGridLayout *GetPropertiesWidgets();
    void AcceptWidgetsProperties();

    virtual QString Save();
};

#endif // TEXTMESC_H
