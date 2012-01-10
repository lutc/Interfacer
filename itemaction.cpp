#include "itemaction.h"
#include "itemmanager.h"

#include "project.h"

#include <QDebug>
ItemAction::ItemAction(QObject *parent) :
    QObject(parent)
{
}

void ItemAction::operator =(ItemAction &from)
{
    m_typeAction = from.m_typeAction;
    m_targetAction = from.m_targetAction;
    m_action = from.m_action;
}

QHBoxLayout *ItemAction::GetLayout()
{
    m_pagesList = ItemManager::Instance()->GetPages();
    m_cmbTypeAction = new QComboBox;
    m_cmbTypeAction->addItem("Command");
    m_cmbTypeAction->addItem("Page");
    m_cmbTypeAction->setFixedWidth(105);
    if (!m_typeAction.isEmpty())
        m_cmbTypeAction->setCurrentIndex(m_cmbTypeAction->findText(m_typeAction));


    m_cmbTargetAction = new QComboBox;
    m_cmbTargetAction->setEditable(true);
    m_cmbTargetAction->addItem("");
    m_cmbTargetAction->addItems(Project::GetDevices());

    if (!m_targetAction.isEmpty())
        m_cmbTargetAction->setEditText(m_targetAction);

    m_cmbAction = new QComboBox;
    m_cmbAction->setEditable(true);
    if (!m_action.isEmpty())
        m_cmbAction->setEditText(m_action);
    connect(m_cmbTypeAction, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onTypeActionChange(int)));
    connect(m_cmbTargetAction, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onTargetActionChange(QString)));

    QHBoxLayout *actionLayout = new QHBoxLayout;
    actionLayout->addWidget(m_cmbTypeAction);
    actionLayout->addWidget(m_cmbTargetAction);
    actionLayout->addWidget(m_cmbAction);

    onTypeActionChange(m_cmbTypeAction->currentIndex());
    onTargetActionChange(m_targetAction);
    return actionLayout;
}

QString ItemAction::ToString()
{
    m_typeAction = m_cmbTypeAction->currentText();
    m_targetAction = m_cmbTargetAction->currentText();
    m_action = m_cmbAction->currentText();

    return m_cmbTypeAction->currentText()
            + " " + m_cmbTargetAction->currentText()
            + " " + m_cmbAction->currentText();
}

void ItemAction::onTypeActionChange(int cmbValue)
{
    switch (cmbValue)
    {
    case 0: //Command
        m_cmbAction->clear();
        m_cmbTargetAction->show();
        break;

    case 1: //Page
        m_cmbAction->addItems(m_pagesList);
        m_cmbTargetAction->hide();
        break;

    default:
        break;
    }
}

void ItemAction::onTargetActionChange(QString deviceName)
{
    m_cmbAction->clear();
    m_cmbAction->addItems(Project::GetDeviceCommands(deviceName));
}
