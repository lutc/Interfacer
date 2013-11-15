#include "pageproperties.h"
#include <QLabel>
#include <QDialogButtonBox>
#include <QGridLayout>

#include "project.h"

PageProperties::PageProperties(Page *item) :
    QDialog(0)
{
    this->m_item = item;
    QLabel *lblLabelName = new QLabel("Name:");
    m_txtName = new QLineEdit;
    m_txtName->setAlignment(Qt::AlignRight);
    m_txtName->setText(m_item->GetName());

    QLabel *lblLabelBackgroundImage = new QLabel("Image:");
    m_cmbBackgroundImage = new QComboBox;
    m_cmbBackgroundImage->addItem("");
    m_cmbBackgroundImage->addItems(Project::GetImages());

    if (!item->GetBackground().isEmpty())
        m_cmbBackgroundImage->setCurrentIndex(
                    m_cmbBackgroundImage->findText(item->GetBackground()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(lblLabelName, 0, 0);
    mainLayout->addWidget(m_txtName, 0, 1);
    mainLayout->addWidget(lblLabelBackgroundImage, 1, 0);
    mainLayout->addWidget(m_cmbBackgroundImage, 1, 1);

    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void PageProperties::accept()
{
    m_item->SetBackground(Project::ImagesDirectory
                          + QString("/") + m_cmbBackgroundImage->currentText());	
    m_item->SetName(m_txtName->text());

    QDialog::accept();
}
