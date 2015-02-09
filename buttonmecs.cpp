#include "buttonmecs.h"
#include <QLabel>
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
    {
        QStringList list = getBackgroundImage().split('/');
        if (list.count() > 1)
            m_cmbUpImage->setCurrentIndex(m_cmbUpImage->findText(list[1]));
        else
            m_cmbUpImage->setCurrentIndex(m_cmbUpImage->findText(getBackgroundImage()));
    }

    QLabel *lblLabelDownImage = new QLabel("Down Image:");
    m_cmbDownImage = new QComboBox;
    m_cmbDownImage->addItem("");
    m_cmbDownImage->addItems(Project::GetImages());
    if (!m_downImage.isEmpty())
    {
        QStringList list = m_downImage.split('/');

        if (list.count() > 1)
            m_cmbDownImage->setCurrentIndex(m_cmbDownImage->findText(list[1]));
        else
            m_cmbDownImage->setCurrentIndex(m_cmbDownImage->findText(m_downImage));
    }

    QLabel *lblLabelHeldImage = new QLabel("Held Image:");
    m_cmbHeldImage = new QComboBox;
    m_cmbHeldImage->addItem("");
    m_cmbHeldImage->addItems(Project::GetImages());
    if (!m_heldImage.isEmpty())
    {
		QStringList list = m_heldImage.split('/');
        m_cmbHeldImage->setCurrentIndex(m_cmbHeldImage->findText(list[1]));

        if (list.count() > 1)
            m_cmbHeldImage->setCurrentIndex(m_cmbHeldImage->findText(list[1]));
        else
            m_cmbHeldImage->setCurrentIndex(m_cmbHeldImage->findText(m_heldImage));
    }

    QLabel *lblCurrentAction = new QLabel(m_onClickActionString);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lblLabelUpImage, 0, 0);
    layout->addWidget(m_cmbUpImage, 0, 1);
    layout->addWidget(lblLabelDownImage, 1, 0);
    layout->addWidget(m_cmbDownImage, 1, 1);
    layout->addWidget(lblLabelHeldImage, 2, 0);
    layout->addWidget(m_cmbHeldImage, 2, 1);
    layout->addWidget(lblCurrentAction, 3, 0, 1, 2);
    if (addOnClickAction)
    {
        layout->addLayout(m_onClickAction->GetLayout(), 4, 0, 1, 2);
    }
//    QObject::connect(m_onClickAction, SIGNAL(OnChangeCommand(QString)), SLOT(onChangeCommand(QString)));
    return layout;
}

void ButtonMECS::AcceptWidgetsProperties()
{
    setBackgroundImage(Project::ImagesDirectory
                       + QString("/") + m_cmbUpImage->currentText());
    m_downImage = Project::ImagesDirectory
            + QString("/") +m_cmbDownImage->currentText();
    m_heldImage = Project::ImagesDirectory
            + QString("/") +m_cmbHeldImage->currentText();
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
    m_onClickAction->Init(commandType, target, command);
    m_onClickActionString = " " + commandType + " " + target + " " + command;        
}

QString ButtonMECS::Save()
{
    QString onClickAction = QString("OnClick  = %0")
            .arg(m_onClickActionString.trimmed());
    return QString (
        "[%0]\n"\
        "Caption = %1\n").arg(GetName()).arg(getText()) + CommonItemMECS::Save() +

    QString ("UpImage = %0\n" \
        "DownImage = %1\n" \
        "HeldImage = %2\n").arg(getBackgroundImage())
            .arg(m_downImage).arg(m_heldImage) +
			((addOnClickAction)?onClickAction:"")
            + "\n\n";
}
