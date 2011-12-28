#include "itemproperties.h"
#include <QDebug>

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include "project.h"

ItemProperties::ItemProperties(CommonItemMECS &item) :
    QDialog(0)
{
    this->chip = &item;

    QLabel *lblLabelType = new QLabel("Type:");
    QLabel *lblType = new QLabel();
    lblType->setText(item.GetName());

    QLabel *lblLabelWidth = new QLabel("Width:");
    txtWidth = new QLineEdit;
    txtWidth->setAlignment(Qt::AlignRight);
    txtWidth->setText(QString::number(item.boundingRect().width()));

    QLabel *lblLabelHeight = new QLabel("Height:");
    txtHeight = new QLineEdit;
    txtHeight->setText(QString::number(item.boundingRect().height()));
    txtHeight->setAlignment(Qt::AlignRight);

    QLabel *lblLabelText = new QLabel(item.GetTextName() + ":");
    txtText = new QLineEdit;
    txtText->setAlignment(Qt::AlignRight);
    txtText->setText(item.getText());

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(lblLabelType, 0, 0);
    mainLayout->addWidget(lblType, 0, 1);
    mainLayout->addWidget(lblLabelWidth, 1, 0);
    mainLayout->addWidget(txtWidth, 1, 1);
    mainLayout->addWidget(lblLabelHeight, 2, 0);
    mainLayout->addWidget(txtHeight, 2, 1);
    mainLayout->addWidget(lblLabelText, 3, 0);
    mainLayout->addWidget(txtText, 3, 1);

    mainLayout->addLayout(item.GetPropertiesWidgets(), 5, 0, 1, 2);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void ItemProperties::accept()
{
    chip->setWidth(txtWidth->text().toInt());
    chip->setHeight(txtHeight->text().toInt());
    chip->setText(txtText->text());

    chip->AcceptWidgetsProperties();
    QDialog::accept();
}
