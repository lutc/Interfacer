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
    void AcceptWidgetsProperties();
    QString Save();

    void SetOnUpAction(QString commandType, QString target, QString command);
    void SetOnDownAction(QString commandType, QString target, QString command);
private:
    ItemAction *m_onUpAction;
    ItemAction *m_onDownAction;

    QString m_onUpActionString;
    QString m_onDownActionString;
};

#endif // TOGGLEBUTTONMECS_H
