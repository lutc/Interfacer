#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QDialog>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QDialogButtonBox>
#include "commonitemmecs.h"

class ItemProperties : public QDialog
{
    Q_OBJECT
public:
    explicit ItemProperties(CommonItemMECS &);

signals:

public slots:

    void accept();

private:
    CommonItemMECS                *chip;

    QDialogButtonBox    *buttonBox;
    QLineEdit           *txtWidth;
    QLineEdit           *txtHeight;
    QLineEdit           *txtText;
};

#endif // ITEMPROPERTIES_H