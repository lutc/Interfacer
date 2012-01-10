#include "interfaceitemproperties.h"
#include <QDebug>

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include "project.h"

CommonItemMECS *InterfaceItemProperties::m_DefaultItem = NULL;
bool InterfaceItemProperties::isDefault = false;

InterfaceItemProperties::InterfaceItemProperties(CommonItemMECS &item) :
    QDialog(0)
{
    if (!item.isInitialized() && m_DefaultItem != NULL)
        item.Copy(m_DefaultItem);
    this->m_item = &item;

    QLabel *lblLabelType = new QLabel("Type:");
    QLabel *lblType = new QLabel();
    lblType->setText(item.GetName());
    lblType->setFixedHeight(25);

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
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    chkSaveAsDefault = new QCheckBox("Save as default");
    chkSaveAsDefault->setChecked(isDefault);
    bottomLayout->addWidget(chkSaveAsDefault);
    bottomLayout->addStretch();
    bottomLayout->addWidget(buttonBox);

    mainLayout->addLayout(bottomLayout, 6, 0, 1, 2);
    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    setMaximumHeight(350);
    setFixedHeight(350);
}

void InterfaceItemProperties::accept()
{
    m_item->setWidth(txtWidth->text().toInt());
    m_item->setHeight(txtHeight->text().toInt());
    m_item->setText(txtText->text());

    m_item->AcceptWidgetsProperties();
    m_item->setInitialized();
    if (chkSaveAsDefault->isChecked())
        m_DefaultItem = m_item;
    else
        m_DefaultItem = NULL;
    isDefault = chkSaveAsDefault->isChecked();
    QDialog::accept();
}
