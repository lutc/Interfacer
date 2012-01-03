#include "textmesc.h"

TextMESC::TextMESC(int x, int y):
    CommonItemMECS(x, y)
{
    this->color = QColor(0, 255, 0);
    m_itemFlags = Qt::AlignLeft;
    m_height = 50;
}

QString TextMESC::GetName()
{
    return "Text";
}

QString TextMESC::GetTextName()
{
    return "DefaultText";
}

QGridLayout *TextMESC::GetPropertiesWidgets()
{
    QGridLayout *layout = new QGridLayout();

    return layout;
}

void TextMESC::AcceptWidgetsProperties()
{

}


QString TextMESC::Save()
{
    return QString (
        "[Text]\n"\
        "Align = left\n") +
            CommonItemMECS::Save() +
        QString ("Width = %2\n" \
        "Height = %3\n" \
        "DefaultText = %4\n\n").
            arg(getWidth()).arg(getHeight()).arg(getText());
}
