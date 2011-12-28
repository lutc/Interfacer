#include "itemaction.h"

ItemAction::ItemAction(QObject *parent) :
    QObject(parent)
{
}

QHBoxLayout *ItemAction::GetLayout()
{
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
