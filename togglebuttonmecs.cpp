#include "togglebuttonmecs.h"

ToggleButtonMECS::ToggleButtonMECS(int x, int y):
    ButtonMECS(x, y, false)
{
    this->color = QColor(0, 0, 255);
    m_onUpAction = new ItemAction();
    m_onDownAction = new ItemAction();
}

QString ToggleButtonMECS::GetName()
{
    return "ToggleButton";
}

QGridLayout *ToggleButtonMECS::GetPropertiesWidgets()
{
    QGridLayout *layout = ButtonMECS::GetPropertiesWidgets();    
    layout->addWidget(new QLabel("On up action"), 3, 0, 1, 2);
    layout->addLayout(m_onUpAction->GetLayout(), 4, 0, 1, 2);

    layout->addWidget(new QLabel("On down action"), 5, 0, 1, 2);
    layout->addLayout(m_onDownAction->GetLayout(), 6, 0, 1, 2);
    return layout;
}


void ToggleButtonMECS::AcceptWidgetsProperties()
{
    ButtonMECS::AcceptWidgetsProperties();
    m_onUpActionString = m_onUpAction->ToString();
    m_onDownActionString = m_onDownAction->ToString();
}

QString ToggleButtonMECS::Save()
{
    return ButtonMECS::Save() +
        QString("OnDown = %0\n" \
            "OnUp = %1\n\n").arg(m_onDownActionString).arg(m_onUpActionString);
}

void ToggleButtonMECS::SetOnUpAction(QString commandType, QString target, QString command)
{
    m_onUpAction->Init(commandType, target, command);
    m_onUpActionString = commandType + " " + target + " " + command;
}

void ToggleButtonMECS::SetOnDownAction(QString commandType, QString target, QString command)
{
    m_onDownAction->Init(commandType, target, command);
    m_onDownActionString = commandType + " " + target + " " + command;
}
