#include "itemproperties.h"
#include <QDebug>

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include "project.h"

ItemProperties::ItemProperties(Chip &chip) :
    QDialog(0)
{
    this->chip = &chip;

    QLabel *lblLabelType = new QLabel("Type:");
    QLabel *lblType = new QLabel();
    switch (chip.getType())
    {
        case Chip::text: lblType->setText("Text");break;
        case Chip::toglebutton: lblType->setText("TogleButton");break;
        case Chip::button: lblType->setText("Button");break;
        case Chip::indicator: lblType->setText("Indicator");break;
    }

    QLabel *lblLabelWidth = new QLabel("Width:");
    txtWidth = new QLineEdit;
    txtWidth->setAlignment(Qt::AlignRight);
    txtWidth->setText(QString::number(chip.boundingRect().width()));

    QLabel *lblLabelHeight = new QLabel("Height:");
    txtHeight = new QLineEdit;
    txtHeight->setText(QString::number(chip.boundingRect().height()));
    txtHeight->setAlignment(Qt::AlignRight);

    QLabel *lblLabelText = new QLabel((chip.getType() == Chip::text)?"DefaultText:":"Caption:");
    txtText = new QLineEdit;
    txtText->setAlignment(Qt::AlignRight);
    txtText->setText(chip.getText());

    QLabel *lblLabelImage = new QLabel("Image:");
    cmbImage = new QComboBox;
    cmbImage->addItem("");
    cmbImage->addItems(Project::getImages());
    if (!chip.getBackgroundImage().isEmpty())
        cmbImage->setCurrentIndex(cmbImage->findText(chip.getBackgroundImage()));

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
    mainLayout->addWidget(lblLabelImage, 4, 0);
    mainLayout->addWidget(cmbImage, 4, 1);

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
    chip->setBackgroundImage(cmbImage->currentText());
    QDialog::accept();
}
