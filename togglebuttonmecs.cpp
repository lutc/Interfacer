#include "togglebuttonmecs.h"

ToggleButtonMECS::ToggleButtonMECS(int x, int y):
    ButtonMECS(x, y, false)
{
    this->color = QColor(0, 255, 0);
}

QString ToggleButtonMECS::GetName()
{
    return "ToggleButton";
}

QGridLayout *ToggleButtonMECS::GetPropertiesWidgets()
{
    QGridLayout *layout = ButtonMECS::GetPropertiesWidgets();
    return layout;
}
