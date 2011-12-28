#include "buttonmesc.h"
#include <QLabel>
#include <QHBoxLayout>

#include "project.h"

ButtonMESC::ButtonMESC(int x, int y):
    CommonItemMECS(x, y)

{
    this->color = QColor(255, 0, 0);
}

QString ButtonMESC::GetName()
{
    return "Button";
}

QString ButtonMESC::GetTextName()
{
    return "Caption";
}

QGridLayout *ButtonMESC::GetPropertiesWidgets()
{
    QLabel *lblLabelUpImage = new QLabel("Up Image:");
    m_cmbUpImage = new QComboBox;
    m_cmbUpImage->addItem("");
    m_cmbUpImage->addItems(Project::getImages());
    if (!getBackgroundImage().isEmpty())
        m_cmbUpImage->setCurrentIndex(m_cmbUpImage->findText(getBackgroundImage()));

    QLabel *lblLabelDownImage = new QLabel("Down Image:");
    m_cmbDownImage = new QComboBox;
    m_cmbDownImage->addItem("");
    m_cmbDownImage->addItems(Project::getImages());
    if (!m_downImage.isEmpty())
        m_cmbDownImage->setCurrentIndex(m_cmbDownImage->findText(m_downImage));

    QLabel *lblLabelHeldImage = new QLabel("Held Image:");
    m_cmbHeldImage = new QComboBox;
    m_cmbHeldImage->addItem("");
    m_cmbHeldImage->addItems(Project::getImages());
    if (!m_heldImage.isEmpty())
        m_cmbHeldImage->setCurrentIndex(m_cmbHeldImage->findText(m_heldImage));

    m_cmbTypeAction = new QComboBox;
    m_cmbTypeAction->addItem("Command");
    m_cmbTypeAction->addItem("Page");
    if (!m_typeAction.isEmpty())
        m_cmbTypeAction->setEditText(m_typeAction);

    m_cmbTargetAction = new QComboBox;
    m_cmbTargetAction->setEditable(true);
    if (!m_targetAction.isEmpty())
        m_cmbTargetAction->setEditText(m_targetAction);

    m_cmbAction = new QComboBox;
    m_cmbAction->setEditable(true);
    if (!m_action.isEmpty())
        m_cmbAction->setEditText(m_action);

    QHBoxLayout *actionLayout = new QHBoxLayout;
    actionLayout->addWidget(m_cmbTypeAction);
    actionLayout->addWidget(m_cmbTargetAction);
    actionLayout->addWidget(m_cmbAction);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lblLabelUpImage, 0, 0);
    layout->addWidget(m_cmbUpImage, 0, 1);
    layout->addWidget(lblLabelDownImage, 1, 0);
    layout->addWidget(m_cmbDownImage, 1, 1);
    layout->addWidget(lblLabelHeldImage, 2, 0);
    layout->addWidget(m_cmbHeldImage, 2, 1);
    layout->addLayout(actionLayout, 3, 0, 1, 2);

    return layout;
}

void ButtonMESC::AcceptWidgetsProperties()
{
    setBackgroundImage(m_cmbUpImage->currentText());
    m_downImage = m_cmbDownImage->currentText();
    m_heldImage = m_cmbHeldImage->currentText();

    m_targetAction = m_cmbTargetAction->currentText();
    m_typeAction = m_cmbTypeAction->currentText();
    m_action = m_cmbAction->currentText();
}

QString ButtonMESC::Save()
{

    return QString (
        "[Button]\n"\
        "Pages = Main\n" \

        "Caption = %1\n").arg(getText()) + CommonItemMECS::Save() +

    QString ("UpImage = Images/%0\n" \
        "DownImage = Images/%1\n" \
        "HeldImage = Images/%2\n" \

        "OnClick  = Command Mitsubishi poweron\n\n").arg(getBackgroundImage())
            .arg(m_downImage).arg(m_heldImage);
}
