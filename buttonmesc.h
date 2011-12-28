#ifndef BUTTONMESC_H
#define BUTTONMESC_H

#include "commonitemmecs.h"
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

class ButtonMESC : public CommonItemMECS
{
public:
    ButtonMESC(int , int );

    QString GetName();
    QString GetTextName();
    QGridLayout *GetPropertiesWidgets();
    void AcceptWidgetsProperties();

    virtual QString Save();

private:
    QComboBox *m_cmbUpImage;
    QComboBox *m_cmbDownImage;
    QComboBox *m_cmbHeldImage;
    QComboBox *m_cmbTypeAction;
    QComboBox *m_cmbTargetAction;
    QComboBox *m_cmbAction;

    QString m_downImage;
    QString m_heldImage;

    QString m_typeAction;
    QString m_targetAction;
    QString m_action;
};

#endif // BUTTONMESC_H
