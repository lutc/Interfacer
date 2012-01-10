#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QDialog>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QDialogButtonBox>
#include <QCheckBox>
#include "commonitemmecs.h"

class InterfaceItemProperties : public QDialog
{
    Q_OBJECT
public:
    explicit InterfaceItemProperties(CommonItemMECS &);

signals:

public slots:

    void accept();

private:
    CommonItemMECS      *m_item;
    static CommonItemMECS *m_DefaultItem;
    static bool isDefault;

    QDialogButtonBox    *buttonBox;
    QLineEdit           *txtWidth;
    QLineEdit           *txtHeight;
    QLineEdit           *txtText;
    QCheckBox           *chkSaveAsDefault;
};

#endif // ITEMPROPERTIES_H
