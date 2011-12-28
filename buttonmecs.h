#ifndef BUTTONMESC_H
#define BUTTONMESC_H

#include "commonitemmecs.h"
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

#include "itemaction.h"

class ButtonMECS : public CommonItemMECS
{
public:
    ButtonMECS(int, int, bool enableAction = true);

    QString GetName();
    QString GetTextName();
    virtual QGridLayout *GetPropertiesWidgets();
    void AcceptWidgetsProperties();

    virtual QString Save();

protected:
    bool addOnClickAction;

private:
    QComboBox *m_cmbUpImage;
    QComboBox *m_cmbDownImage;
    QComboBox *m_cmbHeldImage;

    QString m_downImage;
    QString m_heldImage;

    ItemAction *m_onClickAction;

    QString m_onClickActionString;
};

#endif // BUTTONMESC_H
