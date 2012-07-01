#include "buttonmecs.h"
#include <QLabel>
#include <QDebug>
#include "project.h"

ButtonMECS::ButtonMECS(int x, int y, bool enableAction):
    CommonItemMECS(x, y),
    addOnClickAction(enableAction)

{
    this->color = QColor(255, 0, 0);
    m_onClickAction = new ItemAction();
}
void ButtonMECS::Copy(CommonItemMECS *from)
{
    ButtonMECS *temp = (ButtonMECS *)from;
    m_downImage = temp->m_downImage;
    m_heldImage = temp->m_heldImage;
    *m_onClickAction = *(temp->m_onClickAction);
    CommonItemMECS::Copy(from);
}

QString ButtonMECS::GetName()
{
    return "Button";
}

QString ButtonMECS::GetTextName()
{
    return "Caption";
}

QGridLayout *ButtonMECS::GetPropertiesWidgets()
{
    QLabel *lblLabelUpImage = new QLabel("Up Image:");
    lblLabelUpImage->setFixedWidth(120);
    m_cmbUpImage = new QComboBox;
    m_cmbUpImage->addItem("");
    m_cmbUpImage->addItems(Project::GetImages());
    if (!getBackgroundImage().isEmpty())
        m_cmbUpImage->setCurrentIndex(m_cmbUpImage->findText(getBackgroundImage().section()));

    QLabel *lblLabelDownImage = new QLabel("Down Image:");
    m_cmbDownImage = new QComboBox;
    m_cmbDownImage->addItem("");
    m_cmbDownImage->addItems(Project::GetImages());
    if (!m_downImage.isEmpty())
        m_cmbDownImage->setCurrentIndex(m_cmbDownImage->findText(m_downImage));

    QLabel *lblLabelHeldImage = new QLabel("Held Image:");
    m_cmbHeldImage = new QComboBox;
    m_cmbHeldImage->addItem("");
    m_cmbHeldImage->addItems(Project::GetImages());
    if (!m_heldImage.isEmpty())
        m_cmbHeldImage->setCurrentIndex(m_cmbHeldImage->findText(m_heldImage));


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lblLabelUpImage, 0, 0);
    layout->addWidget(m_cmbUpImage, 0, 1);
    layout->addWidget(lblLabelDownImage, 1, 0);
    layout->addWidget(m_cmbDownImage, 1, 1);
    layout->addWidget(lblLabelHeldImage, 2, 0);
    layout->addWidget(m_cmbHeldImage, 2, 1);
    if (addOnClickAction)
        layout->addLayout(m_onClickAction->GetLayout(), 3, 0, 1, 2);

    return layout;
}

void ButtonMECS::AcceptWidgetsProperties()
{
    setBackgroundImage(Project::ImagesDirectory
                       + QString("/") + m_cmbUpImage->currentText());
    m_downImage = m_cmbDownImage->currentText();
    m_heldImage = m_cmbHeldImage->currentText();
    if (addOnClickAction)
        m_onClickActionString = m_onClickAction->ToString();    
}

void ButtonMECS::SetDownImage(QString image)
{
    m_downImage = image;
}

void ButtonMECS::SetHeldImage(QString image)
{
    m_heldImage = image;
}

void ButtonMECS::SetOnClickAction(QString commandType, QString target, QString command)
{
    m_onClickActionString = " " + commandType + " " + target + " " + command;    
}

QString ButtonMECS::Save()
{
    QString onClickAction = QString("OnClick  = %0")
            .arg(m_onClickActionString);
    return QString (
        "[%0]\n"\
        "Caption = %1\n").arg(GetName()).arg(getText()) + CommonItemMECS::Save() +

    QString ("UpImage = Images/%0\n" \
        "DownImage = Images/%1\n" \
        "HeldImage = Images/%2\n").arg(getBackgroundImage())
            .arg(m_downImage).arg(m_heldImage) +
            ((addOnClickAction)?onClickAction:"")
            + "\n\n";
}
