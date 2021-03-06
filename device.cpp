#include "device.h"

Device::Device(QString name) :
    QObject(0)
{
    name[0] = name.at(0).toUpper();
    m_name = name;
    m_caseSensitive = "false";
    m_queryPeriod = "10000";
    m_timeout = "1000";
}

QStringList Device::GetCommands()
{
    return QStringList(m_commands.keys());
}

void Device::addCommand(QString commandName, QString command)
{
    QString commandBody = QString("command %0\n" \
            "{\n" \
            "   send %1 (%2)\n" \
            "}\n\n").arg(commandName.toLower()).arg(m_name).arg(command);
    m_commands.insert(commandName, commandBody);
}

