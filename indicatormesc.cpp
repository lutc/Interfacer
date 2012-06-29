#include "indicatormecs.h"

IndicatorMECS::IndicatorMECS(int x, int y)
    :CommonItemMECS(x, y)
{
}

QString IndicatorMECS::GetName()
{
    return "Indicator";
}

QString IndicatorMECS::GetTextName()
{
    return "";
}

QGridLayout *IndicatorMECS::GetPropertiesWidgets()
{
    QGridLayout *layout = new QGridLayout();

    return layout;
}

void IndicatorMECS::AcceptWidgetsProperties()
{

}

void IndicatorMECS::Copy(CommonItemMECS *from)
{
    CommonItemMECS::Copy(from);
}


QString IndicatorMECS::Save()
{
    return QString (
        "[Text]\n"\
        "Align = center\n") +
            CommonItemMECS::Save() +
        QString ("Width = %2\n" \
        "Height = %3\n" \
        "DefaultText = %4\n\n").
            arg(getWidth()).arg(getHeight()).arg(getText());
}
