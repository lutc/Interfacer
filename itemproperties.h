#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QDialog>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QDialogButtonBox>
#include "chip.h"

class ItemProperties : public QDialog
{
    Q_OBJECT
public:
    explicit ItemProperties(Chip &);

signals:

public slots:

    void accept();

private:
    Chip                *chip;

    QDialogButtonBox    *buttonBox;
    QLineEdit           *txtWidth;
    QLineEdit           *txtHeight;
    QLineEdit           *txtText;
    QComboBox           *cmbImage;

};

#endif // ITEMPROPERTIES_H
